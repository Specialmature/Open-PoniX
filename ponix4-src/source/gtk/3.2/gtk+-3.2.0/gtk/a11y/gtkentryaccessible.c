/* GAIL - The GNOME Accessibility Implementation Library
 * Copyright 2001, 2002, 2003 Sun Microsystems Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "config.h"

#include <gtk/gtk.h>
#include "gtkpango.h"
#include "gtkentryaccessible.h"
#include "gtkcomboboxaccessible.h"

/* Callbacks */

static void     insert_text_cb             (GtkEditable        *editable,
                                            gchar              *new_text,
                                            gint                new_text_length,
                                            gint               *position);
static void     delete_text_cb             (GtkEditable        *editable,
                                            gint                start,
                                            gint                end);
static void     changed_cb                 (GtkEditable        *editable);

static gboolean check_for_selection_change (GtkEntryAccessible *entry,
                                            GtkEntry           *gtk_entry);


static void atk_editable_text_interface_init (AtkEditableTextIface *iface);
static void atk_text_interface_init          (AtkTextIface         *iface);
static void atk_action_interface_init        (AtkActionIface       *iface);


G_DEFINE_TYPE_WITH_CODE (GtkEntryAccessible, _gtk_entry_accessible, GTK_TYPE_WIDGET_ACCESSIBLE,
                         G_IMPLEMENT_INTERFACE (ATK_TYPE_EDITABLE_TEXT, atk_editable_text_interface_init)
                         G_IMPLEMENT_INTERFACE (ATK_TYPE_TEXT, atk_text_interface_init)
                         G_IMPLEMENT_INTERFACE (ATK_TYPE_ACTION, atk_action_interface_init))


static AtkStateSet *
gtk_entry_accessible_ref_state_set (AtkObject *accessible)
{
  AtkStateSet *state_set;
  gboolean value;
  GtkWidget *widget;

  widget = gtk_accessible_get_widget (GTK_ACCESSIBLE (accessible));
  if (widget == NULL)
    return NULL;

  state_set = ATK_OBJECT_CLASS (_gtk_entry_accessible_parent_class)->ref_state_set (accessible);

  g_object_get (G_OBJECT (widget), "editable", &value, NULL);
  if (value)
    atk_state_set_add_state (state_set, ATK_STATE_EDITABLE);
  atk_state_set_add_state (state_set, ATK_STATE_SINGLE_LINE);

  return state_set;
}

static AtkAttributeSet *
gtk_entry_accessible_get_attributes (AtkObject *accessible)
{
  GtkWidget *widget;
  AtkAttributeSet *attributes;
  AtkAttribute *placeholder_text;
  const gchar *text;

  attributes = ATK_OBJECT_CLASS (_gtk_entry_accessible_parent_class)->get_attributes (accessible);

  widget = gtk_accessible_get_widget (GTK_ACCESSIBLE (accessible));
  if (widget == NULL)
    return attributes;

  text = gtk_entry_get_placeholder_text (GTK_ENTRY (widget));
  if (text == NULL)
    return attributes;

  placeholder_text = g_malloc (sizeof (AtkAttribute));
  placeholder_text->name = g_strdup ("placeholder-text");
  placeholder_text->value = g_strdup (text);

  attributes = g_slist_append (attributes, placeholder_text);

  return attributes;
}

static void
gtk_entry_accessible_initialize (AtkObject *obj,
                                 gpointer   data)
{
  GtkEntry *entry;
  GtkEntryAccessible *gtk_entry_accessible;
  gint start_pos, end_pos;

  ATK_OBJECT_CLASS (_gtk_entry_accessible_parent_class)->initialize (obj, data);

  gtk_entry_accessible = GTK_ENTRY_ACCESSIBLE (obj);

  entry = GTK_ENTRY (data);
  gtk_editable_get_selection_bounds (GTK_EDITABLE (entry),
                                     &start_pos, &end_pos);
  gtk_entry_accessible->cursor_position = end_pos;
  gtk_entry_accessible->selection_bound = start_pos;

  /* Set up signal callbacks */
  g_signal_connect (entry, "insert-text", G_CALLBACK (insert_text_cb), NULL);
  g_signal_connect (entry, "delete-text", G_CALLBACK (delete_text_cb), NULL);
  g_signal_connect (entry, "changed", G_CALLBACK (changed_cb), NULL);

  if (gtk_entry_get_visibility (entry))
    obj->role = ATK_ROLE_TEXT;
  else
    obj->role = ATK_ROLE_PASSWORD_TEXT;
}

static void
gtk_entry_accessible_notify_gtk (GObject    *obj,
                                 GParamSpec *pspec)
{
  GtkWidget *widget;
  AtkObject* atk_obj;
  GtkEntry* gtk_entry;
  GtkEntryAccessible* entry;

  widget = GTK_WIDGET (obj);
  atk_obj = gtk_widget_get_accessible (widget);
  gtk_entry = GTK_ENTRY (widget);
  entry = GTK_ENTRY_ACCESSIBLE (atk_obj);

  if (g_strcmp0 (pspec->name, "cursor-position") == 0)
    {
      if (check_for_selection_change (entry, gtk_entry))
        g_signal_emit_by_name (atk_obj, "text-selection-changed");
      /*
       * The entry cursor position has moved so generate the signal.
       */
      g_signal_emit_by_name (atk_obj, "text-caret-moved",
                             entry->cursor_position);
    }
  else if (g_strcmp0 (pspec->name, "selection-bound") == 0)
    {
      if (check_for_selection_change (entry, gtk_entry))
        g_signal_emit_by_name (atk_obj, "text-selection-changed");
    }
  else if (g_strcmp0 (pspec->name, "editable") == 0)
    {
      gboolean value;

      g_object_get (obj, "editable", &value, NULL);
      atk_object_notify_state_change (atk_obj, ATK_STATE_EDITABLE, value);
    }
  else if (g_strcmp0 (pspec->name, "visibility") == 0)
    {
      gboolean visibility;
      AtkRole new_role;

      visibility = gtk_entry_get_visibility (gtk_entry);
      new_role = visibility ? ATK_ROLE_TEXT : ATK_ROLE_PASSWORD_TEXT;
      atk_object_set_role (atk_obj, new_role);
    }
  else
    GTK_WIDGET_ACCESSIBLE_CLASS (_gtk_entry_accessible_parent_class)->notify_gtk (obj, pspec);
}

static gint
gtk_entry_accessible_get_index_in_parent (AtkObject *accessible)
{
  /*
   * If the parent widget is a combo box then the index is 1
   * otherwise do the normal thing.
   */
  if (accessible->accessible_parent)
    if (GTK_IS_COMBO_BOX_ACCESSIBLE (accessible->accessible_parent))
      return 1;

  return ATK_OBJECT_CLASS (_gtk_entry_accessible_parent_class)->get_index_in_parent (accessible);
}

static void
_gtk_entry_accessible_class_init (GtkEntryAccessibleClass *klass)
{
  AtkObjectClass  *class = ATK_OBJECT_CLASS (klass);
  GtkWidgetAccessibleClass *widget_class = (GtkWidgetAccessibleClass*)klass;

  class->ref_state_set = gtk_entry_accessible_ref_state_set;
  class->get_index_in_parent = gtk_entry_accessible_get_index_in_parent;
  class->initialize = gtk_entry_accessible_initialize;
  class->get_attributes = gtk_entry_accessible_get_attributes;

  widget_class->notify_gtk = gtk_entry_accessible_notify_gtk;
}

static void
_gtk_entry_accessible_init (GtkEntryAccessible *entry)
{
  entry->length_insert = 0;
  entry->length_delete = 0;
  entry->cursor_position = 0;
  entry->selection_bound = 0;
}

static gchar *
gtk_entry_accessible_get_text (AtkText *atk_text,
                               gint     start_pos,
                               gint     end_pos)
{
  GtkWidget *widget;
  const gchar *text;

  widget = gtk_accessible_get_widget (GTK_ACCESSIBLE (atk_text));
  if (widget == NULL)
    return NULL;

  /* FIXME: is this acceptable ? */
  if (!gtk_entry_get_visibility (GTK_ENTRY (widget)))
    return g_strdup ("");

  text = gtk_entry_get_text (GTK_ENTRY (widget));

  if (text)
    return g_utf8_substring (text, start_pos, end_pos > -1 ? end_pos : g_utf8_strlen (text, -1));

  return NULL;
}

static gchar *
gtk_entry_accessible_get_text_before_offset (AtkText         *text,
                                             gint             offset,
                                             AtkTextBoundary  boundary_type,
                                             gint            *start_offset,
                                             gint            *end_offset)
{
  GtkWidget *widget;

  widget = gtk_accessible_get_widget (GTK_ACCESSIBLE (text));
  if (widget == NULL)
    return NULL;

  /* FIXME: is this acceptable ? */
  if (!gtk_entry_get_visibility (GTK_ENTRY (widget)))
    return g_strdup ("");

  return _gtk_pango_get_text_before (gtk_entry_get_layout (GTK_ENTRY (widget)),
                                     boundary_type, offset,
                                     start_offset, end_offset);
}

static gchar *
gtk_entry_accessible_get_text_at_offset (AtkText         *text,
                                         gint             offset,
                                         AtkTextBoundary  boundary_type,
                                         gint            *start_offset,
                                         gint            *end_offset)
{
  GtkWidget *widget;

  widget = gtk_accessible_get_widget (GTK_ACCESSIBLE (text));
  if (widget == NULL)
    return NULL;

  /* FIXME: is this acceptable ? */
  if (!gtk_entry_get_visibility (GTK_ENTRY (widget)))
    return g_strdup ("");

  return _gtk_pango_get_text_at (gtk_entry_get_layout (GTK_ENTRY (widget)),
                                 boundary_type, offset,
                                 start_offset, end_offset);
}

static gchar *
gtk_entry_accessible_get_text_after_offset (AtkText         *text,
                                            gint             offset,
                                            AtkTextBoundary  boundary_type,
                                            gint            *start_offset,
                                            gint            *end_offset)
{
  GtkWidget *widget;

  widget = gtk_accessible_get_widget (GTK_ACCESSIBLE (text));
  if (widget == NULL)
    return NULL;

  /* FIXME: is this acceptable ? */
  if (!gtk_entry_get_visibility (GTK_ENTRY (widget)))
    return g_strdup ("");

  return _gtk_pango_get_text_after (gtk_entry_get_layout (GTK_ENTRY (widget)),
                                    boundary_type, offset,
                                    start_offset, end_offset);
}

static gint
gtk_entry_accessible_get_character_count (AtkText *atk_text)
{
  GtkWidget *widget;
  const gchar *text;

  widget = gtk_accessible_get_widget (GTK_ACCESSIBLE (atk_text));
  if (widget == NULL)
    return 0;

  text = gtk_entry_get_text (GTK_ENTRY (widget));

  if (text)
    return g_utf8_strlen (text, -1);

  return 0;
}

static gint
gtk_entry_accessible_get_caret_offset (AtkText *text)
{
  GtkWidget *widget;

  widget = gtk_accessible_get_widget (GTK_ACCESSIBLE (text));
  if (widget == NULL)
    return 0;

  return gtk_editable_get_position (GTK_EDITABLE (widget));
}

static gboolean
gtk_entry_accessible_set_caret_offset (AtkText *text,
                                       gint     offset)
{
  GtkWidget *widget;

  widget = gtk_accessible_get_widget (GTK_ACCESSIBLE (text));
  if (widget == NULL)
    return FALSE;

  gtk_editable_set_position (GTK_EDITABLE (widget), offset);

  return TRUE;
}

static AtkAttributeSet *
add_text_attribute (AtkAttributeSet  *attributes,
                    AtkTextAttribute  attr,
                    gint              i)
{
  AtkAttribute *at;

  at = g_new (AtkAttribute, 1);
  at->name = g_strdup (atk_text_attribute_get_name (attr));
  at->value = g_strdup (atk_text_attribute_get_value (attr, i));

  return g_slist_prepend (attributes, at);
}

static AtkAttributeSet *
gtk_entry_accessible_get_run_attributes (AtkText *text,
                                         gint     offset,
                                         gint    *start_offset,
                                         gint    *end_offset)
{
  GtkWidget *widget;
  AtkAttributeSet *attributes;

  widget = gtk_accessible_get_widget (GTK_ACCESSIBLE (text));
  if (widget == NULL)
    return NULL;

  attributes = NULL;
  attributes = add_text_attribute (attributes, ATK_TEXT_ATTR_DIRECTION,
                                   gtk_widget_get_direction (widget));
  attributes = _gtk_pango_get_run_attributes (attributes,
                                              gtk_entry_get_layout (GTK_ENTRY (widget)),
                                              offset,
                                              start_offset,
                                              end_offset);

  return attributes;
}

static AtkAttributeSet *
gtk_entry_accessible_get_default_attributes (AtkText *text)
{
  GtkWidget *widget;
  AtkAttributeSet *attributes;

  widget = gtk_accessible_get_widget (GTK_ACCESSIBLE (text));
  if (widget == NULL)
    return NULL;

  attributes = NULL;
  attributes = add_text_attribute (attributes, ATK_TEXT_ATTR_DIRECTION,
                                   gtk_widget_get_direction (widget));
  attributes = _gtk_pango_get_default_attributes (attributes,
                                                  gtk_entry_get_layout (GTK_ENTRY (widget)));
  attributes = _gtk_style_context_get_attributes (attributes,
                                                  gtk_widget_get_style_context (widget),
                                                  gtk_widget_get_state_flags (widget));

  return attributes;
}

static void
gtk_entry_accessible_get_character_extents (AtkText      *text,
                                            gint          offset,
                                            gint         *x,
                                            gint         *y,
                                            gint         *width,
                                            gint         *height,
                                            AtkCoordType  coords)
{
  GtkWidget *widget;
  GtkEntry *entry;
  PangoRectangle char_rect;
  const gchar *entry_text;
  gint index, x_layout, y_layout;
  GdkWindow *window;
  gint x_window, y_window;

  widget = gtk_accessible_get_widget (GTK_ACCESSIBLE (text));
  if (widget == NULL)
    return;

  entry = GTK_ENTRY (widget);

  gtk_entry_get_layout_offsets (entry, &x_layout, &y_layout);
  entry_text = gtk_entry_get_text (entry);
  index = g_utf8_offset_to_pointer (entry_text, offset) - entry_text;
  pango_layout_index_to_pos (gtk_entry_get_layout (entry), index, &char_rect);
  pango_extents_to_pixels (&char_rect, NULL);

  window = gtk_widget_get_window (widget);
  gdk_window_get_origin (window, &x_window, &y_window);

  *x = x_window + x_layout + char_rect.x;
  *y = y_window + y_layout + char_rect.y;
  *width = char_rect.width;
  *height = char_rect.height;

  if (coords == ATK_XY_WINDOW)
    {
      window = gdk_window_get_toplevel (window);
      gdk_window_get_origin (window, &x_window, &y_window);

      *x -= x_window;
      *y -= y_window;
    }
}

static gint
gtk_entry_accessible_get_offset_at_point (AtkText      *atk_text,
                                          gint          x,
                                          gint          y,
                                          AtkCoordType  coords)
{
  GtkWidget *widget;
  GtkEntry *entry;
  const gchar *text;
  gint index, x_layout, y_layout;
  gint x_window, y_window;
  gint x_local, y_local;
  GdkWindow *window;

  widget = gtk_accessible_get_widget (GTK_ACCESSIBLE (atk_text));
  if (widget == NULL)
    return -1;

  entry = GTK_ENTRY (widget);

  gtk_entry_get_layout_offsets (entry, &x_layout, &y_layout);

  window = gtk_widget_get_window (widget);
  gdk_window_get_origin (window, &x_window, &y_window);

  x_local = x - x_layout - x_window;
  y_local = y - y_layout - y_window;

  if (coords == ATK_XY_WINDOW)
    {
      window = gdk_window_get_toplevel (window);
      gdk_window_get_origin (window, &x_window, &y_window);

      x_local += x_window;
      y_local += y_window;
    }
  if (!pango_layout_xy_to_index (gtk_entry_get_layout (entry),
                                 x_local * PANGO_SCALE,
                                 y_local * PANGO_SCALE,
                                 &index, NULL))
    {
      if (x_local < 0 || y_local < 0)
        index = 0;
      else
        index = -1;
    }

  if (index != -1)
    {
      text = gtk_entry_get_text (entry);
      return g_utf8_pointer_to_offset (text, text + index);
    }

  return -1;
}

static gint
gtk_entry_accessible_get_n_selections (AtkText *text)
{
  GtkWidget *widget;
  gint start, end;

  widget = gtk_accessible_get_widget (GTK_ACCESSIBLE (text));
  if (widget == NULL)
    return 0;

  if (gtk_editable_get_selection_bounds (GTK_EDITABLE (widget), &start, &end))
    return 1;

  return 0;
}

static gchar *
gtk_entry_accessible_get_selection (AtkText *text,
                                    gint     selection_num,
                                    gint    *start_pos,
                                    gint    *end_pos)
{
  GtkWidget *widget;

  widget = gtk_accessible_get_widget (GTK_ACCESSIBLE (text));
  if (widget == NULL)
    return NULL;

  if (selection_num != 0)
     return NULL;

  if (gtk_editable_get_selection_bounds (GTK_EDITABLE (widget), start_pos, end_pos))
    return gtk_editable_get_chars (GTK_EDITABLE (widget), *start_pos, *end_pos);

  return NULL;
}

static gboolean
gtk_entry_accessible_add_selection (AtkText *text,
                                    gint     start_pos,
                                    gint     end_pos)
{
  GtkEntry *entry;
  GtkWidget *widget;
  gint start, end;

  widget = gtk_accessible_get_widget (GTK_ACCESSIBLE (text));
  if (widget == NULL)
    return FALSE;

  entry = GTK_ENTRY (widget);

  if (!gtk_editable_get_selection_bounds (GTK_EDITABLE (entry), &start, &end))
    {
      gtk_editable_select_region (GTK_EDITABLE (entry), start_pos, end_pos);
      return TRUE;
    }
  else
    return FALSE;
}

static gboolean
gtk_entry_accessible_remove_selection (AtkText *text,
                                       gint     selection_num)
{
  GtkWidget *widget;
  gint start, end;

  widget = gtk_accessible_get_widget (GTK_ACCESSIBLE (text));
  if (widget == NULL)
    return FALSE;

  if (selection_num != 0)
     return FALSE;

  if (gtk_editable_get_selection_bounds (GTK_EDITABLE (widget), &start, &end))
    {
      gtk_editable_select_region (GTK_EDITABLE (widget), end, end);
      return TRUE;
    }
  else
    return FALSE;
}

static gboolean
gtk_entry_accessible_set_selection (AtkText *text,
                                    gint     selection_num,
                                    gint     start_pos,
                                    gint     end_pos)
{
  GtkWidget *widget;
  gint start, end;

  widget = gtk_accessible_get_widget (GTK_ACCESSIBLE (text));
  if (widget == NULL)
    return FALSE;

  if (selection_num != 0)
     return FALSE;

  if (gtk_editable_get_selection_bounds (GTK_EDITABLE (widget), &start, &end))
    {
      gtk_editable_select_region (GTK_EDITABLE (widget), start_pos, end_pos);
      return TRUE;
    }
  else
    return FALSE;
}

static gunichar
gtk_entry_accessible_get_character_at_offset (AtkText *atk_text,
                                              gint     offset)
{
  GtkWidget *widget;
  const gchar *text;
  gchar *index;

  widget = gtk_accessible_get_widget (GTK_ACCESSIBLE (atk_text));
  if (widget == NULL)
    return '\0';

  if (!gtk_entry_get_visibility (GTK_ENTRY (widget)))
    return '\0';

  text = gtk_entry_get_text (GTK_ENTRY (widget));
  if (offset >= g_utf8_strlen (text, -1))
    return '\0';

  index = g_utf8_offset_to_pointer (text, offset);

  return g_utf8_get_char (index);
}

static void
atk_text_interface_init (AtkTextIface *iface)
{
  iface->get_text = gtk_entry_accessible_get_text;
  iface->get_character_at_offset = gtk_entry_accessible_get_character_at_offset;
  iface->get_text_before_offset = gtk_entry_accessible_get_text_before_offset;
  iface->get_text_at_offset = gtk_entry_accessible_get_text_at_offset;
  iface->get_text_after_offset = gtk_entry_accessible_get_text_after_offset;
  iface->get_caret_offset = gtk_entry_accessible_get_caret_offset;
  iface->set_caret_offset = gtk_entry_accessible_set_caret_offset;
  iface->get_character_count = gtk_entry_accessible_get_character_count;
  iface->get_n_selections = gtk_entry_accessible_get_n_selections;
  iface->get_selection = gtk_entry_accessible_get_selection;
  iface->add_selection = gtk_entry_accessible_add_selection;
  iface->remove_selection = gtk_entry_accessible_remove_selection;
  iface->set_selection = gtk_entry_accessible_set_selection;
  iface->get_run_attributes = gtk_entry_accessible_get_run_attributes;
  iface->get_default_attributes = gtk_entry_accessible_get_default_attributes;
  iface->get_character_extents = gtk_entry_accessible_get_character_extents;
  iface->get_offset_at_point = gtk_entry_accessible_get_offset_at_point;
}

static void
gtk_entry_accessible_set_text_contents (AtkEditableText *text,
                                        const gchar     *string)
{
  GtkWidget *widget;

  widget = gtk_accessible_get_widget (GTK_ACCESSIBLE (text));
  if (widget == NULL)
    return;

  if (!gtk_editable_get_editable (GTK_EDITABLE (widget)))
    return;

  gtk_entry_set_text (GTK_ENTRY (widget), string);
}

static void
gtk_entry_accessible_insert_text (AtkEditableText *text,
                                  const gchar     *string,
                                  gint             length,
                                  gint            *position)
{
  GtkWidget *widget;
  GtkEditable *editable;

  widget = gtk_accessible_get_widget (GTK_ACCESSIBLE (text));
  if (widget == NULL)
    return;

  editable = GTK_EDITABLE (widget);
  if (!gtk_editable_get_editable (editable))
    return;

  gtk_editable_insert_text (editable, string, length, position);
  gtk_editable_set_position (editable, *position);
}

static void
gtk_entry_accessible_copy_text (AtkEditableText *text,
                                gint             start_pos,
                                gint             end_pos)
{
  GtkWidget *widget;
  GtkEditable *editable;
  gchar *str;
  GtkClipboard *clipboard;

  widget = gtk_accessible_get_widget (GTK_ACCESSIBLE (text));
  if (widget == NULL)
    return;

  if (!gtk_widget_has_screen (widget))
    return;

  editable = GTK_EDITABLE (widget);
  str = gtk_editable_get_chars (editable, start_pos, end_pos);
  clipboard = gtk_widget_get_clipboard (widget, GDK_SELECTION_CLIPBOARD);
  gtk_clipboard_set_text (clipboard, str, -1);
  g_free (str);
}

static void
gtk_entry_accessible_cut_text (AtkEditableText *text,
                               gint             start_pos,
                               gint             end_pos)
{
  GtkWidget *widget;
  GtkEditable *editable;
  gchar *str;
  GtkClipboard *clipboard;

  widget = gtk_accessible_get_widget (GTK_ACCESSIBLE (text));
  if (widget == NULL)
    return;

  if (!gtk_widget_has_screen (widget))
    return;

  editable = GTK_EDITABLE (widget);
  if (!gtk_editable_get_editable (editable))
    return;

  str = gtk_editable_get_chars (editable, start_pos, end_pos);
  clipboard = gtk_widget_get_clipboard (widget, GDK_SELECTION_CLIPBOARD);
  gtk_clipboard_set_text (clipboard, str, -1);
  gtk_editable_delete_text (editable, start_pos, end_pos);
}

static void
gtk_entry_accessible_delete_text (AtkEditableText *text,
                                  gint             start_pos,
                                  gint             end_pos)
{
  GtkWidget *widget;
  GtkEditable *editable;

  widget = gtk_accessible_get_widget (GTK_ACCESSIBLE (text));
  if (widget == NULL)
    return;

  editable = GTK_EDITABLE (widget);
  if (!gtk_editable_get_editable (editable))
    return;

  gtk_editable_delete_text (editable, start_pos, end_pos);
}

typedef struct
{
  GtkEntry* entry;
  gint position;
} PasteData;

static void
paste_received_cb (GtkClipboard *clipboard,
                   const gchar  *text,
                   gpointer      data)
{
  PasteData *paste = data;

  if (text)
    gtk_editable_insert_text (GTK_EDITABLE (paste->entry), text, -1,
                              &paste->position);

  g_object_unref (paste->entry);
  g_free (paste);
}

static void
gtk_entry_accessible_paste_text (AtkEditableText *text,
                                 gint             position)
{
  GtkWidget *widget;
  GtkEditable *editable;
  PasteData *paste;
  GtkClipboard *clipboard;

  widget = gtk_accessible_get_widget (GTK_ACCESSIBLE (text));
  if (widget == NULL)
    return;

  if (!gtk_widget_has_screen (widget))
    return;

  editable = GTK_EDITABLE (widget);
  if (!gtk_editable_get_editable (editable))
    return;

  paste = g_new0 (PasteData, 1);
  paste->entry = GTK_ENTRY (widget);
  paste->position = position;

  g_object_ref (paste->entry);
  clipboard = gtk_widget_get_clipboard (widget, GDK_SELECTION_CLIPBOARD);
  gtk_clipboard_request_text (clipboard, paste_received_cb, paste);
}

static void
atk_editable_text_interface_init (AtkEditableTextIface *iface)
{
  iface->set_text_contents = gtk_entry_accessible_set_text_contents;
  iface->insert_text = gtk_entry_accessible_insert_text;
  iface->copy_text = gtk_entry_accessible_copy_text;
  iface->cut_text = gtk_entry_accessible_cut_text;
  iface->delete_text = gtk_entry_accessible_delete_text;
  iface->paste_text = gtk_entry_accessible_paste_text;
  iface->set_run_attributes = NULL;
}

/* We connect to GtkEditable::insert-text, since it carries
 * the information we need. But we delay emitting our own
 * text_changed::insert signal until the entry has update
 * all its internal state and emits GtkEntry::changed.
 */
static void
insert_text_cb (GtkEditable *editable,
                gchar       *new_text,
                gint         new_text_length,
                gint        *position)
{
  GtkEntryAccessible *accessible;

  if (new_text_length == 0)
    return;

  accessible = GTK_ENTRY_ACCESSIBLE (gtk_widget_get_accessible (GTK_WIDGET (editable)));
  if (accessible->length_insert == 0)
    {
      accessible->position_insert = *position;
      accessible->length_insert = g_utf8_strlen (new_text, new_text_length);
    }
}

/* We connect to GtkEditable::delete-text, since it carries
 * the information we need. But we delay emitting our own
 * text_changed::delete signal until the entry has update
 * all its internal state and emits GtkEntry::changed.
 */
static void
delete_text_cb (GtkEditable *editable,
                gint         start,
                gint         end)
{
  GtkEntryAccessible *accessible;

  if (end < 0)
    {
      const gchar *text;

      text = gtk_entry_get_text (GTK_ENTRY (editable));
      end = g_utf8_strlen (text, -1);
    }

  if (end == start)
    return;

  accessible = GTK_ENTRY_ACCESSIBLE (gtk_widget_get_accessible (GTK_WIDGET (editable)));
  if (accessible->length_delete == 0)
    {
      accessible->position_delete = start;
      accessible->length_delete = end - start;
    }
}

/* Note the assumption here: A single ::changed emission
 * will only collect a single deletion/insertion, and there
 * won't be multiple insertions or deletions in a single
 * change.
 */
static void
changed_cb (GtkEditable *editable)
{
  GtkEntryAccessible *accessible;

  accessible = GTK_ENTRY_ACCESSIBLE (gtk_widget_get_accessible (GTK_WIDGET (editable)));

  if (accessible->length_delete > 0)
    {
      g_signal_emit_by_name (accessible,
                             "text-changed::delete",
                             accessible->position_delete,
                             accessible->length_delete);
      accessible->length_delete = 0;
    }
  if (accessible->length_insert > 0)
    {
      g_signal_emit_by_name (accessible,
                             "text-changed::insert",
                             accessible->position_insert,
                             accessible->length_insert);
      accessible->length_insert = 0;
    }
}

static gboolean
check_for_selection_change (GtkEntryAccessible *accessible,
                            GtkEntry           *entry)
{
  gboolean ret_val = FALSE;
  gint start, end;

  if (gtk_editable_get_selection_bounds (GTK_EDITABLE (entry), &start, &end))
    {
      if (end != accessible->cursor_position ||
          start != accessible->selection_bound)
        /*
         * This check is here as this function can be called
         * for notification of selection_bound and current_pos.
         * The values of current_pos and selection_bound may be the same
         * for both notifications and we only want to generate one
         * text_selection_changed signal.
         */
        ret_val = TRUE;
    }
  else
    {
      /* We had a selection */
      ret_val = (accessible->cursor_position != accessible->selection_bound);
    }

  accessible->cursor_position = end;
  accessible->selection_bound = start;

  return ret_val;
}

static gboolean
gtk_entry_accessible_do_action (AtkAction *action,
                                gint       i)
{
  GtkWidget *widget;

  widget = gtk_accessible_get_widget (GTK_ACCESSIBLE (action));
  if (widget == NULL)
    return FALSE;

  if (!gtk_widget_get_sensitive (widget) || !gtk_widget_get_visible (widget))
    return FALSE;

  if (i != 0)
    return FALSE;

  gtk_widget_activate (widget);

  return TRUE;
}

static gint
gtk_entry_accessible_get_n_actions (AtkAction *action)
{
  return 1;
}

static const gchar *
gtk_entry_accessible_get_keybinding (AtkAction *action,
                                     gint       i)
{
  GtkWidget *widget;
  GtkWidget *label;
  AtkRelationSet *set;
  AtkRelation *relation;
  GPtrArray *target;
  gpointer target_object;
  guint key_val;

  if (i != 0)
    return NULL;

  widget = gtk_accessible_get_widget (GTK_ACCESSIBLE (action));
  if (widget == NULL)
    return NULL;

  set = atk_object_ref_relation_set (ATK_OBJECT (action));
  if (!set)
    return NULL;

  label = NULL;
  relation = atk_relation_set_get_relation_by_type (set, ATK_RELATION_LABELLED_BY);
  if (relation)
    {
      target = atk_relation_get_target (relation);

      target_object = g_ptr_array_index (target, 0);
      label = gtk_accessible_get_widget (GTK_ACCESSIBLE (target_object));
    }

  g_object_unref (set);

  if (GTK_IS_LABEL (label))
    {
      key_val = gtk_label_get_mnemonic_keyval (GTK_LABEL (label));
      if (key_val != GDK_KEY_VoidSymbol)
        return gtk_accelerator_name (key_val, GDK_MOD1_MASK);
    }

  return NULL;
}

static const gchar*
gtk_entry_accessible_action_get_name (AtkAction *action,
                                      gint       i)
{
  if (i != 0)
    return NULL;

  return "activate";
}

static void
atk_action_interface_init (AtkActionIface *iface)
{
  iface->do_action = gtk_entry_accessible_do_action;
  iface->get_n_actions = gtk_entry_accessible_get_n_actions;
  iface->get_keybinding = gtk_entry_accessible_get_keybinding;
  iface->get_name = gtk_entry_accessible_action_get_name;
}
