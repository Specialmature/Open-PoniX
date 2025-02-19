/* Pango
 * pango-markup.c: Parse markup into attributed text
 *
 * Copyright (C) 2000 Red Hat Software
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <pango/pango-attributes.h>
#include <pango/pango-font.h>
#include <pango/pango-utils.h>

/* FIXME */
#define _(x) x

/* CSS size levels */
typedef enum
{
  XXSmall = -3,
  XSmall = -2,
  Small = -1,
  Medium = 0,
  Large = 1,
  XLarge = 2,
  XXLarge = 3
} SizeLevel;

typedef struct _MarkupData MarkupData;

struct _MarkupData
{
  PangoAttrList *attr_list;
  GString *text;
  GSList *tag_stack;
  gsize index;
  GSList *to_apply;
  gunichar accel_marker;
  gunichar accel_char;
};

typedef struct _OpenTag OpenTag;

struct _OpenTag
{
  GSList *attrs;
  gsize start_index;
  /* Current total scale level; reset whenever
   * an absolute size is set.
   * Each "larger" ups it 1, each "smaller" decrements it 1
   */
  gint scale_level;
  /* Our impact on scale_level, so we know whether we
   * need to create an attribute ourselves on close
   */
  gint scale_level_delta;
  /* Base scale factor currently in effect
   * or size that this tag
   * forces, or parent's scale factor or size.
   */
  double base_scale_factor;
  int base_font_size;
  guint has_base_font_size : 1;
};

typedef gboolean (*TagParseFunc) (MarkupData            *md,
                                  OpenTag               *tag,
                                  const gchar          **names,
                                  const gchar          **values,
                                  GMarkupParseContext   *context,
                                  GError               **error);

static gboolean b_parse_func        (MarkupData           *md,
                                     OpenTag              *tag,
                                     const gchar         **names,
                                     const gchar         **values,
                                     GMarkupParseContext  *context,
                                     GError              **error);
static gboolean big_parse_func      (MarkupData           *md,
                                     OpenTag              *tag,
                                     const gchar         **names,
                                     const gchar         **values,
                                     GMarkupParseContext  *context,
                                     GError              **error);
static gboolean span_parse_func     (MarkupData           *md,
                                     OpenTag              *tag,
                                     const gchar         **names,
                                     const gchar         **values,
                                     GMarkupParseContext  *context,
                                     GError              **error);
static gboolean i_parse_func        (MarkupData           *md,
                                     OpenTag              *tag,
                                     const gchar         **names,
                                     const gchar         **values,
                                     GMarkupParseContext  *context,
                                     GError              **error);
static gboolean markup_parse_func   (MarkupData           *md,
                                     OpenTag              *tag,
                                     const gchar         **names,
                                     const gchar         **values,
                                     GMarkupParseContext  *context,
                                     GError              **error);
static gboolean s_parse_func        (MarkupData           *md,
                                     OpenTag              *tag,
                                     const gchar         **names,
                                     const gchar         **values,
                                     GMarkupParseContext  *context,
                                     GError              **error);
static gboolean sub_parse_func      (MarkupData           *md,
                                     OpenTag              *tag,
                                     const gchar         **names,
                                     const gchar         **values,
                                     GMarkupParseContext  *context,
                                     GError              **error);
static gboolean sup_parse_func      (MarkupData           *md,
                                     OpenTag              *tag,
                                     const gchar         **names,
                                     const gchar         **values,
                                     GMarkupParseContext  *context,
                                     GError              **error);
static gboolean small_parse_func    (MarkupData           *md,
                                     OpenTag              *tag,
                                     const gchar         **names,
                                     const gchar         **values,
                                     GMarkupParseContext  *context,
                                     GError              **error);
static gboolean tt_parse_func       (MarkupData           *md,
                                     OpenTag              *tag,
                                     const gchar         **names,
                                     const gchar         **values,
                                     GMarkupParseContext  *context,
                                     GError              **error);
static gboolean u_parse_func        (MarkupData           *md,
                                     OpenTag              *tag,
                                     const gchar         **names,
                                     const gchar         **values,
                                     GMarkupParseContext  *context,
                                     GError              **error);

static double
scale_factor (int scale_level, double base)
{
  double factor = base;
  int i;

  /* 1.2 is the CSS scale factor between sizes */
  
  if (scale_level > 0)
    {
      i = 0;
      while (i < scale_level)
        {
          factor *= 1.2;

          ++i;
        }
    }
  else if (scale_level < 0)
    {
      i = scale_level;
      while (i < 0)
        {
          factor /= 1.2;
                  
          ++i;
        }
    }

  return factor;
}

static void
open_tag_free (OpenTag *ot)
{
  g_slist_foreach (ot->attrs, (GFunc) pango_attribute_destroy, NULL);
  g_slist_free (ot->attrs);
  g_free (ot);
}

static void
open_tag_set_absolute_font_size (OpenTag *ot,
                                 int      font_size)
{
  ot->base_font_size = font_size;
  ot->has_base_font_size = TRUE;
  ot->scale_level = 0;
  ot->scale_level_delta = 0;
}

static void
open_tag_set_absolute_font_scale (OpenTag *ot,
                                  double   scale)
{
  ot->base_scale_factor = scale;
  ot->has_base_font_size = FALSE;
  ot->scale_level = 0;
  ot->scale_level_delta = 0;
}
     
static OpenTag*
markup_data_open_tag (MarkupData   *md)
{
  OpenTag *ot;
  OpenTag *parent = NULL;
  
  if (md->attr_list == NULL)
    return NULL;

  if (md->tag_stack)
    parent = md->tag_stack->data;
  
  ot = g_new (OpenTag, 1);
  ot->attrs = NULL;
  ot->start_index = md->index;
  ot->scale_level_delta = 0;
  
  if (parent == NULL)
    {
      ot->base_scale_factor = 1.0;
      ot->base_font_size = 0;
      ot->has_base_font_size = FALSE;
      ot->scale_level = 0;
    }
  else
    {
      ot->base_scale_factor = parent->base_scale_factor;
      ot->base_font_size = parent->base_font_size;
      ot->has_base_font_size = parent->has_base_font_size;
      ot->scale_level = parent->scale_level;
    }
  
  md->tag_stack = g_slist_prepend (md->tag_stack, ot);

  return ot;
}

static void
markup_data_close_tag (MarkupData *md)
{
  OpenTag *ot;
  GSList *tmp_list;

  if (md->attr_list == NULL)
    return;

  /* pop the stack */
  ot = md->tag_stack->data;
  md->tag_stack = g_slist_delete_link (md->tag_stack,
                                       md->tag_stack);

  /* Adjust end indexes, and push each attr onto the front of the
   * to_apply list. This means that outermost tags are on the front of
   * that list; if we apply the list in order, then the innermost
   * tags will "win" which is correct.
   */
  tmp_list = ot->attrs;
  while (tmp_list != NULL)
    {
      PangoAttribute *a = tmp_list->data;

      a->start_index = ot->start_index;
      a->end_index = md->index;
      
      md->to_apply = g_slist_prepend (md->to_apply, a);

      tmp_list = g_slist_next (tmp_list);
    }

  if (ot->scale_level_delta != 0)
    {
      /* We affected relative font size; create an appropriate
       * attribute and reverse our effects on the current level
       */
      PangoAttribute *a;

      if (ot->has_base_font_size)
        {
          /* Create a font using the absolute point size
           * as the base size to be scaled from
           */
          a = pango_attr_size_new (scale_factor (ot->scale_level,
                                                 1.0) *
                                   ot->base_font_size);
        }
      else
        {
          /* Create a font using the current scale factor
           * as the base size to be scaled from
           */
          a = pango_attr_scale_new (scale_factor (ot->scale_level,
                                                  ot->base_scale_factor));
        }

      a->start_index = ot->start_index;
      a->end_index = md->index;
          
      md->to_apply = g_slist_prepend (md->to_apply, a);
    }
  
  g_slist_free (ot->attrs);
  g_free (ot);  
}

static void
start_element_handler  (GMarkupParseContext *context,
                        const gchar         *element_name,
                        const gchar        **attribute_names,
                        const gchar        **attribute_values,
                        gpointer             user_data,
                        GError             **error)
{
  TagParseFunc parse_func = NULL;
  OpenTag *ot;

  switch (*element_name)
    {
    case 'b':
      if (strcmp ("b", element_name) == 0)
        parse_func = b_parse_func;
      else if (strcmp ("big", element_name) == 0)
        parse_func = big_parse_func;
      break;

    case 'i':
      if (strcmp ("i", element_name) == 0)
        parse_func = i_parse_func;
      break;

    case 'm':
      if (strcmp ("markup", element_name) == 0)
        parse_func = markup_parse_func;
      break;

    case 's':
      if (strcmp ("span", element_name) == 0)
        parse_func = span_parse_func;
      else if (strcmp ("s", element_name) == 0)
        parse_func = s_parse_func;
      else if (strcmp ("sub", element_name) == 0)
        parse_func = sub_parse_func;
      else if (strcmp ("sup", element_name) == 0)
        parse_func = sup_parse_func;
      else if (strcmp ("small", element_name) == 0)
        parse_func = small_parse_func;
      break;

    case 't':
      if (strcmp ("tt", element_name) == 0)
        parse_func = tt_parse_func;
      break;

    case 'u':
      if (strcmp ("u", element_name) == 0)
        parse_func = u_parse_func;
      break;
    }

  if (parse_func == NULL)
    {
      gint line_number, char_number;

      g_markup_parse_context_get_position (context,
                                           &line_number, &char_number);

      g_set_error (error,
                   G_MARKUP_ERROR,
                   G_MARKUP_ERROR_UNKNOWN_ELEMENT,
                   _("Unknown tag '%s' on line %d char %d"),
                   element_name,
                   line_number, char_number);

      return;
    }

  ot = markup_data_open_tag (user_data);

  /* note ot may be NULL if the user didn't want the attribute list */

  if (!(*parse_func) (user_data, ot,
                      attribute_names, attribute_values,
                      context, error))
    {
      /* there's nothing to do; we return an error, and end up
       * freeing ot off the tag stack later.
       */
    }
}

static void
end_element_handler    (GMarkupParseContext *context,
                        const gchar         *element_name,
                        gpointer             user_data,
                        GError             **error)
{
  markup_data_close_tag (user_data);
}

static void
text_handler           (GMarkupParseContext *context,
                        const gchar         *text,
                        gsize                text_len,
                        gpointer             user_data,
                        GError             **error)
{
  MarkupData *md = user_data;

  if (md->accel_marker == 0)
    {
      /* Just append all the text */
      
      md->index += text_len;
      
      g_string_append_len (md->text, text, text_len);
    }
  else
    {
      /* Parse the accelerator */
      const gchar *p;
      const gchar *end;
      const gchar *range_start;
      const gchar *range_end;
      gboolean just_saw_marker;
      gssize uline_index = -1;
      gsize uline_len = 0;	/* Quiet GCC */
      
      range_end = NULL;
      range_start = text;
      p = text;
      end = text + text_len;
      just_saw_marker = FALSE;
      
      while (p != end)
        {
          gunichar c;
          
          c = g_utf8_get_char (p);

          if (range_end)
            {
              if (c == md->accel_marker)
                {
                  /* escaped accel marker; move range_end
                   * past the accel marker that came before,
                   * append the whole thing
                   */
                  range_end = g_utf8_next_char (range_end);
                  g_string_append_len (md->text,
                                       range_start,
                                       range_end - range_start);
                  md->index += range_end - range_start;

                  /* set next range_start, skipping accel marker */
                  range_start = g_utf8_next_char (p);
                }
              else
                {
                  /* Don't append the accel marker (leave range_end
                   * alone); set the accel char to c; record location for
                   * underline attribute
                   */
                  if (md->accel_char == 0)
                    md->accel_char = c;

                  g_string_append_len (md->text,
                                       range_start,
                                       range_end - range_start);
                  md->index += range_end - range_start;

                  /* The underline should go underneath the char
                   * we're setting as the next range_start
                   */
                  uline_index = md->index;
                  uline_len = g_utf8_next_char (p) - p;
                  
                  /* set next range_start to include this char */
                  range_start = p;
                }

              /* reset range_end */
              range_end = NULL;
            }          
          else if (c == md->accel_marker)
            {
              range_end = p;
            }
          
          p = g_utf8_next_char (p);
        }

      if (range_end)
        {
          g_string_append_len (md->text,
                               range_start,
                               range_end - range_start);
          md->index += range_end - range_start;
        }
      else
        {
          g_string_append_len (md->text,
                               range_start,
                               end - range_start);
          md->index += end - range_start;
        }
      
      if (md->attr_list != NULL && uline_index >= 0)
        {
          /* Add the underline indicating the accelerator */          
          PangoAttribute *attr;

          attr = pango_attr_underline_new (PANGO_UNDERLINE_LOW);

          attr->start_index = uline_index;
          attr->end_index = uline_index + uline_len;
          
          pango_attr_list_change (md->attr_list, attr);
        }
    }
}

static gboolean
xml_isspace (char c)
{
  return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

static GMarkupParser pango_markup_parser = {
  start_element_handler,
  end_element_handler,
  text_handler,
  NULL,
  NULL
};

/**
 * pango_parse_markup:
 * @markup_text: markup to parse (see <link linkend="PangoMarkupFormat">markup format</link>)
 * @length: length of @markup_text, or -1 if nul-terminated
 * @accel_marker: character that precedes an accelerator, or 0 for none
 * @attr_list: address of return location for a #PangoAttrList, or NULL
 * @text: address of return location for text with tags stripped, or NULL
 * @accel_char: address of return location for accelerator char, or NULL
 * @error: address of return location for errors, or NULL
 * 
 *
 * Parses marked-up text (see
 * <link linkend="PangoMarkupFormat">markup format</link>) to create
 * a plaintext string and an attribute list.
 *
 * If @accel_marker is nonzero, the given character will mark the
 * character following it as an accelerator. For example, the accel
 * marker might be an ampersand or underscore. All characters marked
 * as an accelerator will receive a %PANGO_UNDERLINE_LOW attribute,
 * and the first character so marked will be returned in @accel_char.
 * Two @accel_marker characters following each other produce a single
 * literal @accel_marker character.
 * 
 * Return value: FALSE if @error is set, otherwise TRUE
 **/
gboolean
pango_parse_markup (const char                 *markup_text,
                    int                         length,
                    gunichar                    accel_marker,
                    PangoAttrList             **attr_list,
                    char                      **text,
                    gunichar                   *accel_char,
                    GError                    **error)
{
  GMarkupParseContext *context = NULL;
  MarkupData *md = NULL;
  gboolean needs_root = TRUE;
  GSList *tmp_list;
  const char *p;
  const char *end;
  
  g_return_val_if_fail (markup_text != NULL, FALSE);
  
  md = g_new (MarkupData, 1);

  /* Don't bother creating these if they weren't requested;
   * might be useful e.g. if you just want to validate
   * some markup.
   */
  if (attr_list)
    md->attr_list = pango_attr_list_new ();
  else
    md->attr_list = NULL;

  md->text = g_string_new ("");
  
  if (accel_char)
    *accel_char = 0;

  md->accel_marker = accel_marker;
  md->accel_char = 0;
  
  md->index = 0;
  md->tag_stack = NULL;
  md->to_apply = NULL;
  
  context = g_markup_parse_context_new (&pango_markup_parser,
                                        0, md, NULL);

  if (length < 0)
    length = strlen (markup_text);  

  p = markup_text;
  end = markup_text + length;
  while (p != end && xml_isspace (*p))
    ++p;

  if (end - p >= 8 && strncmp (p, "<markup>", 8) == 0)
     needs_root = FALSE;

  if (needs_root)
    if (!g_markup_parse_context_parse (context,
                                       "<markup>",
                                       -1,
                                       error))
      goto error;


  if (!g_markup_parse_context_parse (context,
                                     markup_text,
                                     length,
                                     error))
    goto error;

  if (needs_root)
    if (!g_markup_parse_context_parse (context,
                                       "</markup>",
                                       -1,
                                       error))
      goto error;

  if (!g_markup_parse_context_end_parse (context, error))
    goto error;

  g_markup_parse_context_free (context);

  if (md->attr_list)
    {
      /* The apply list has the most-recently-closed tags first;
       * we want to apply the least-recently-closed tag last.
       */
      tmp_list = md->to_apply;
      while (tmp_list != NULL)
        {
          PangoAttribute *attr = tmp_list->data;
          
          /* Innermost tags before outermost */
          pango_attr_list_change (md->attr_list, attr);

          tmp_list = g_slist_next (tmp_list);
        }
      g_slist_free (md->to_apply);
      md->to_apply = NULL;
    }
  
  if (attr_list)
    *attr_list = md->attr_list;

  if (text)
    *text = g_string_free (md->text, FALSE);
  else
    g_string_free (md->text, TRUE);
  
  if (accel_char)
    *accel_char = md->accel_char;
  
  g_assert (md->tag_stack == NULL);
  
  g_free (md);

  return TRUE;

 error:
  g_slist_foreach (md->tag_stack, (GFunc) open_tag_free, NULL);
  g_slist_free (md->tag_stack);
  g_slist_foreach (md->to_apply, (GFunc) pango_attribute_destroy, NULL);
  g_slist_free (md->to_apply);
  g_string_free (md->text, TRUE);
  
  if (md->attr_list)
    pango_attr_list_unref (md->attr_list);

  g_free (md);

  if (context)
    g_markup_parse_context_free (context);

  return FALSE;
}

static void
set_bad_attribute (GError             **error,
                   GMarkupParseContext *context,
                   const char          *element_name,
                   const char          *attribute_name)
{
  gint line_number, char_number;

  g_markup_parse_context_get_position (context,
                                       &line_number, &char_number);

  g_set_error (error,
               G_MARKUP_ERROR,
               G_MARKUP_ERROR_UNKNOWN_ATTRIBUTE,
               _("Tag '%s' does not support attribute '%s' on line %d char %d"),
               element_name,
               attribute_name,
               line_number, char_number);
}

static void
add_attribute (OpenTag        *ot,
               PangoAttribute *attr)
{
  if (ot == NULL)
    pango_attribute_destroy (attr);
  else
    ot->attrs = g_slist_prepend (ot->attrs, attr);
}

#define CHECK_NO_ATTRS(elem) G_STMT_START {                    \
         if (*names != NULL) {                                 \
           set_bad_attribute (error, context, (elem), *names); \
           return FALSE;                                       \
         } }G_STMT_END

static gboolean
b_parse_func        (MarkupData            *md,
                     OpenTag               *tag,
                     const gchar          **names,
                     const gchar          **values,
                     GMarkupParseContext   *context,
                     GError               **error)
{
  CHECK_NO_ATTRS("b");
  add_attribute (tag, pango_attr_weight_new (PANGO_WEIGHT_BOLD));
  return TRUE;
}

static gboolean
big_parse_func      (MarkupData            *md,
                     OpenTag               *tag,
                     const gchar          **names,
                     const gchar          **values,
                     GMarkupParseContext   *context,
                     GError               **error)
{
  CHECK_NO_ATTRS("big");

  /* Grow text one level */
  if (tag)
    {
      tag->scale_level_delta += 1;
      tag->scale_level += 1;
    }

  return TRUE;
}

static gboolean
parse_absolute_size (OpenTag               *tag,
                     const char            *size)
{
  SizeLevel level = Medium;
  double factor;
  
  if (strcmp (size, "xx-small") == 0)
    {
      level = XXSmall;
    }
  else if (strcmp (size, "x-small") == 0)
    {
      level = XSmall;
    }
  else if (strcmp (size, "small") == 0)
    {
      level = Small;
    }
  else if (strcmp (size, "medium") == 0)
    {
      level = Medium;
    }
  else if (strcmp (size, "large") == 0)
    {
      level = Large;
    }
  else if (strcmp (size, "x-large") == 0)
    {
      level = XLarge;
    }
  else if (strcmp (size, "xx-large") == 0)
    {
      level = XXLarge;
    }
  else
    return FALSE;

  /* This is "absolute" in that it's relative to the base font,
   * but not to sizes created by any other tags
   */
  factor = scale_factor (level, 1.0);
  add_attribute (tag, pango_attr_scale_new (factor));
  if (tag)
    open_tag_set_absolute_font_scale (tag, factor);
  
  return TRUE;
}

#define CHECK_DUPLICATE(var) G_STMT_START{                              \
          if ((var) != NULL) {                                          \
            g_set_error (error, G_MARKUP_ERROR,                         \
                         G_MARKUP_ERROR_INVALID_CONTENT,                \
                         _("Attribute '%s' occurs twice on <span> tag " \
                           "on line %d char %d, may only occur once"),  \
                         names[i], line_number, char_number);           \
            return FALSE;                                               \
          }}G_STMT_END

static gboolean
span_parse_func     (MarkupData            *md,
                     OpenTag               *tag,
                     const gchar          **names,
                     const gchar          **values,
                     GMarkupParseContext   *context,
                     GError               **error)
{
  int line_number, char_number;
  int i;
  const char *family = NULL;
  const char *size = NULL;
  const char *style = NULL;
  const char *weight = NULL;
  const char *variant = NULL;
  const char *stretch = NULL;
  const char *desc = NULL;
  const char *foreground = NULL;
  const char *background = NULL;
  const char *underline = NULL;
  const char *strikethrough = NULL;
  const char *rise = NULL;
  const char *lang = NULL;
  const char *fallback = NULL;
  
  g_markup_parse_context_get_position (context,
                                       &line_number, &char_number);

  i = 0;
  while (names[i])
    {
      if (strcmp (names[i], "font_family") == 0 ||
          strcmp (names[i], "face") == 0)
        {
          CHECK_DUPLICATE (family);
          family = values[i];
        }
      else if (strcmp (names[i], "size") == 0)
        {
          CHECK_DUPLICATE (size);
          size = values[i];
        }
      else if (strcmp (names[i], "style") == 0)
        {
          CHECK_DUPLICATE (style);
          style = values[i];
        }
      else if (strcmp (names[i], "weight") == 0)
        {
          CHECK_DUPLICATE (weight);
          weight = values[i];
        }
      else if (strcmp (names[i], "variant") == 0)
        {
          CHECK_DUPLICATE (variant);
          variant = values[i];
        }
      else if (strcmp (names[i], "stretch") == 0)
        {
          CHECK_DUPLICATE (stretch);
          stretch = values[i];
        }
      else if (strcmp (names[i], "font_desc") == 0)
        {
          CHECK_DUPLICATE (desc);
          desc = values[i];
        }
      else if (strcmp (names[i], "foreground") == 0 ||
               strcmp (names[i], "color") == 0)
        {
          CHECK_DUPLICATE (foreground);
          foreground = values[i];
        }
      else if (strcmp (names[i], "background") == 0)
        {
          CHECK_DUPLICATE (background);
          background = values[i];
        }
      else if (strcmp (names[i], "underline") == 0)
        {
          CHECK_DUPLICATE (underline);
          underline = values[i];
        }
      else if (strcmp (names[i], "strikethrough") == 0)
        {
          CHECK_DUPLICATE (strikethrough);
          strikethrough = values[i];
        }
      else if (strcmp (names[i], "rise") == 0)
        {
          CHECK_DUPLICATE (rise);
          rise = values[i];
        }
      else if (strcmp (names[i], "lang") == 0)
        {
          CHECK_DUPLICATE (lang);
          lang = values[i];
        }
      else if (strcmp (names[i], "fallback") == 0)
        {
          CHECK_DUPLICATE (fallback);
          fallback = values[i];
        }
      else
        {
          g_set_error (error, G_MARKUP_ERROR,
                       G_MARKUP_ERROR_UNKNOWN_ATTRIBUTE,
                       _("Attribute '%s' is not allowed on the <span> tag "
                         "on line %d char %d"),
                       names[i], line_number, char_number);
          return FALSE;
        }

      ++i;
    }

  /* Parse desc first, then modify it with other font-related attributes. */
  if (desc)
    {
      PangoFontDescription *parsed;

      parsed = pango_font_description_from_string (desc);
      if (parsed)
        {
          add_attribute (tag, pango_attr_font_desc_new (parsed));
	  if (tag)
	    open_tag_set_absolute_font_size (tag, pango_font_description_get_size (parsed));
          pango_font_description_free (parsed);
        }
    }

  if (family)
    {
      add_attribute (tag, pango_attr_family_new (family));
    }

  if (size)
    {
      if (g_ascii_isdigit (*size))
        {
          char *end = NULL;
          gulong n;

          n = strtoul (size, &end, 10);

          if (*end != '\0')
            {
              g_set_error (error,
                           G_MARKUP_ERROR,
                           G_MARKUP_ERROR_INVALID_CONTENT,
                           _("Value of 'size' attribute on <span> tag on line %d"
                             "could not be parsed; should be an integer, or a "
                             "string such as 'small', not '%s'"),
                           line_number, size);
              goto error;
            }

          add_attribute (tag, pango_attr_size_new (n));
	  if (tag)
	    open_tag_set_absolute_font_size (tag, n);
        }
      else if (strcmp (size, "smaller") == 0)
        {
	  if (tag)
	    {
	      tag->scale_level_delta -= 1;
	      tag->scale_level -= 1;
	    }
        }
      else if (strcmp (size, "larger") == 0)
        {
	  if (tag)
	    {
	      tag->scale_level_delta += 1;
	      tag->scale_level += 1;
	    }
        }
      else if (parse_absolute_size (tag, size))
        ; /* nothing */
      else
        {
          g_set_error (error,
                       G_MARKUP_ERROR,
                       G_MARKUP_ERROR_INVALID_CONTENT,
                       _("Value of 'size' attribute on <span> tag on line %d"
                         "could not be parsed; should be an integer, or a "
                         "string such as 'small', not '%s'"),
                       line_number, size);
          goto error;
        }
    }

  if (style)
    {
      PangoStyle pango_style;
      
      if (pango_parse_style (style, &pango_style, FALSE))
        add_attribute (tag, pango_attr_style_new (pango_style));
      else
        {
          g_set_error (error,
                       G_MARKUP_ERROR,
                       G_MARKUP_ERROR_INVALID_CONTENT,
                       _("'%s' is not a valid value for the 'style' attribute "
                         "on <span> tag, line %d; valid values are "
                         "'normal', 'oblique', 'italic'"),
                       style, line_number);
          goto error;
        }
    }

  if (weight)
    {
      PangoWeight pango_weight;
      
      if (pango_parse_weight (weight, &pango_weight, FALSE))
        add_attribute (tag,
                       pango_attr_weight_new (pango_weight));
      else
        {
          g_set_error (error,
                       G_MARKUP_ERROR,
                       G_MARKUP_ERROR_INVALID_CONTENT,
                       _("'%s' is not a valid value for the 'weight' "
                         "attribute on <span> tag, line %d; valid "
                         "values are for example 'light', 'ultrabold' or a number"),
                       weight, line_number);
          goto error;
        }
    }

  if (variant)
    {
      PangoVariant pango_variant;
      
      if (pango_parse_variant (variant, &pango_variant, FALSE))
        add_attribute (tag, pango_attr_variant_new (pango_variant));
      else
        {
          g_set_error (error,
                       G_MARKUP_ERROR,
                       G_MARKUP_ERROR_INVALID_CONTENT,
                       _("'%s' is not a valid value for the 'variant' "
                         "attribute on <span> tag, line %d; valid values are "
                         "'normal', 'smallcaps'"),
                       variant, line_number);
          goto error;
        }
    }

  if (stretch)
    {
      PangoStretch pango_stretch;
      
      if (pango_parse_stretch (stretch, &pango_stretch, FALSE))
        add_attribute (tag, pango_attr_stretch_new (pango_stretch));
      else
        {
          g_set_error (error,
                       G_MARKUP_ERROR,
                       G_MARKUP_ERROR_INVALID_CONTENT,
                       _("'%s' is not a valid value for the 'stretch' "
                         "attribute on <span> tag, line %d; valid "
                         "values are for example 'condensed', "
                         "'ultraexpanded', 'normal'"),
                       stretch, line_number);
          goto error;
        }
    }

  if (foreground)
    {
      PangoColor color;

      if (!pango_color_parse (&color, foreground))
        {
          g_set_error (error,
                       G_MARKUP_ERROR,
                       G_MARKUP_ERROR_INVALID_CONTENT,
                       _("Could not parse foreground color specification "
                         "'%s' on line %d"),
                       foreground, line_number);
          goto error;
        }

      add_attribute (tag, pango_attr_foreground_new (color.red, color.green, color.blue));
    }

  if (background)
    {
      PangoColor color;
      
      if (!pango_color_parse (&color, background))
        {
          g_set_error (error,
                       G_MARKUP_ERROR,
                       G_MARKUP_ERROR_INVALID_CONTENT,
                       _("Could not parse background color specification "
                         "'%s' on line %d"),
                       background, line_number);
          goto error;
        }

      add_attribute (tag, pango_attr_background_new (color.red, color.green, color.blue));
    }

  if (underline)
    {
      PangoUnderline ul = PANGO_UNDERLINE_NONE;

      if (strcmp (underline, "single") == 0)
        ul = PANGO_UNDERLINE_SINGLE;
      else if (strcmp (underline, "double") == 0)
        ul = PANGO_UNDERLINE_DOUBLE;
      else if (strcmp (underline, "low") == 0)
        ul = PANGO_UNDERLINE_LOW;
      else if (strcmp (underline, "error") == 0)
        ul = PANGO_UNDERLINE_ERROR;
      else if (strcmp (underline, "none") == 0)
        ul = PANGO_UNDERLINE_NONE;
      else
        {
          g_set_error (error,
                       G_MARKUP_ERROR,
                       G_MARKUP_ERROR_INVALID_CONTENT,
                       _("'%s' is not a valid value for the 'underline' "
                         "attribute on <span> tag, line %d; valid "
                         "values are for example 'single', "
                         "'double', 'low', 'none'"),
                       underline, line_number);
          goto error;
        }

      add_attribute (tag, pango_attr_underline_new (ul));
    }

  if (strikethrough)
    {
      if (strcmp (strikethrough, "true") == 0)
        add_attribute (tag, pango_attr_strikethrough_new (TRUE));
      else if (strcmp (strikethrough, "false") == 0)
        add_attribute (tag, pango_attr_strikethrough_new (FALSE));
      else
        {
          g_set_error (error,
                       G_MARKUP_ERROR,
                       G_MARKUP_ERROR_INVALID_CONTENT,
                       _("'strikethrough' attribute on <span> tag "
                         "line %d should have one of the values "
                         "'true' or 'false': '%s' is not valid"),
                       line_number, strikethrough);
          goto error;
        }
    }

  if (fallback)
    {
      if (strcmp (fallback, "true") == 0)
        add_attribute (tag, pango_attr_fallback_new (TRUE));
      else if (strcmp (fallback, "false") == 0)
        add_attribute (tag, pango_attr_fallback_new (FALSE));
      else
        {
          g_set_error (error,
                       G_MARKUP_ERROR,
                       G_MARKUP_ERROR_INVALID_CONTENT,
                       _("'fallback' attribute on <span> tag "
                         "line %d should have one of the values "
                         "'true' or 'false': '%s' is not valid"),
                       line_number, fallback);
          goto error;
        }
    }

  if (rise)
    {
      char *end = NULL;
      glong n;
      
      n = strtol (rise, &end, 10);

      if (*end != '\0')
        {
          g_set_error (error,
                       G_MARKUP_ERROR,
                       G_MARKUP_ERROR_INVALID_CONTENT,
                       _("Value of 'rise' attribute on <span> tag "
                         "on line %d could not be parsed; "
                         "should be an integer, not '%s'"),
                       line_number, rise);
          goto error;
        }

      add_attribute (tag, pango_attr_rise_new (n));
    }

  if (lang)
    {
      add_attribute (tag,
		     pango_attr_language_new (pango_language_from_string (lang)));
    }
  
  return TRUE;

 error:

  return FALSE;
}

static gboolean
i_parse_func        (MarkupData            *md,
                     OpenTag               *tag,
                     const gchar          **names,
                     const gchar          **values,
                     GMarkupParseContext   *context,
                     GError               **error)
{
  CHECK_NO_ATTRS("i");
  add_attribute (tag, pango_attr_style_new (PANGO_STYLE_ITALIC));

  return TRUE;
}

static gboolean
markup_parse_func (MarkupData            *md,
                   OpenTag               *tag,
                   const gchar          **names,
                   const gchar          **values,
                   GMarkupParseContext   *context,
                   GError               **error)
{
  /* We don't do anything with this tag at the moment. */
  
  return TRUE;
}

static gboolean
s_parse_func        (MarkupData            *md,
                     OpenTag               *tag,
                     const gchar          **names,
                     const gchar          **values,
                     GMarkupParseContext   *context,
                     GError               **error)
{
  CHECK_NO_ATTRS("s");
  add_attribute (tag, pango_attr_strikethrough_new (TRUE));

  return TRUE;
}

#define SUPERSUB_RISE 5000

static gboolean
sub_parse_func      (MarkupData            *md,
                     OpenTag               *tag,
                     const gchar          **names,
                     const gchar          **values,
                     GMarkupParseContext   *context,
                     GError               **error)
{
  CHECK_NO_ATTRS("sub");

  /* Shrink font, and set a negative rise */
  if (tag)
    {
      tag->scale_level_delta -= 1;
      tag->scale_level -= 1;
    }

  add_attribute (tag, pango_attr_rise_new (-SUPERSUB_RISE));

  return TRUE;
}

static gboolean
sup_parse_func      (MarkupData            *md,
                     OpenTag               *tag,
                     const gchar          **names,
                     const gchar          **values,
                     GMarkupParseContext   *context,
                     GError               **error)
{
  CHECK_NO_ATTRS("sup");

  /* Shrink font, and set a positive rise */
  if (tag)
    {
      tag->scale_level_delta -= 1;
      tag->scale_level -= 1;
    }

  add_attribute (tag, pango_attr_rise_new (SUPERSUB_RISE));

  return TRUE;
}

static gboolean
small_parse_func    (MarkupData            *md,
                     OpenTag               *tag,
                     const gchar          **names,
                     const gchar          **values,
                     GMarkupParseContext   *context,
                     GError               **error)
{
  CHECK_NO_ATTRS("small");

  /* Shrink text one level */
  if (tag)
    {
      tag->scale_level_delta -= 1;
      tag->scale_level -= 1;
    }

  return TRUE;
}

static gboolean
tt_parse_func       (MarkupData            *md,
                     OpenTag               *tag,
                     const gchar          **names,
                     const gchar          **values,
                     GMarkupParseContext   *context,
                     GError               **error)
{
  CHECK_NO_ATTRS("tt");

  add_attribute (tag, pango_attr_family_new ("Monospace"));

  return TRUE;
}

static gboolean
u_parse_func        (MarkupData            *md,
                     OpenTag               *tag,
                     const gchar          **names,
                     const gchar          **values,
                     GMarkupParseContext   *context,
                     GError               **error)
{
  CHECK_NO_ATTRS("u");
  add_attribute (tag, pango_attr_underline_new (PANGO_UNDERLINE_SINGLE));

  return TRUE;
}
