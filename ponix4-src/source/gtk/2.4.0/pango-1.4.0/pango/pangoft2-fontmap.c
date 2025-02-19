/* Pango
 * pangoft2-fontmap.c:
 *
 * Copyright (C) 2000 Red Hat Software
 * Copyright (C) 2000 Tor Lillqvist
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

#include "config.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#ifdef HAVE_DIRENT_H
#include <dirent.h>
#endif

#include <fontconfig/fontconfig.h>

#include "pango-utils.h"
#include "pangoft2-private.h"
#include "pangofc-fontmap.h"

#ifdef G_OS_WIN32
#define STRICT
#include <windows.h>
#endif

typedef struct _PangoFT2Family       PangoFT2Family;
typedef struct _PangoFT2FontMapClass PangoFT2FontMapClass;

struct _PangoFT2FontMap
{
  PangoFcFontMap parent_instance;

  FT_Library library;

  double dpi_x;
  double dpi_y;

  /* Function to call on prepared patterns to do final
   * config tweaking.
   */
  PangoFT2SubstituteFunc substitute_func;
  gpointer substitute_data;
  GDestroyNotify substitute_destroy;
};

struct _PangoFT2FontMapClass
{
  PangoFcFontMapClass parent_class;
};

static void          pango_ft2_font_map_class_init          (PangoFT2FontMapClass *class);
static void          pango_ft2_font_map_init                (PangoFT2FontMap      *fontmap);
static void          pango_ft2_font_map_finalize            (GObject              *object);
static void          pango_ft2_font_map_default_substitute  (PangoFcFontMap       *fcfontmap,
							     FcPattern            *pattern);
static PangoFcFont * pango_ft2_font_map_new_font            (PangoFcFontMap       *fcfontmap,
							     FcPattern            *pattern);

static PangoFT2FontMap *pango_ft2_global_fontmap = NULL;

static GObjectClass *parent_class;

GType
pango_ft2_font_map_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (PangoFT2FontMapClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) pango_ft2_font_map_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (PangoFT2FontMap),
        0,              /* n_preallocs */
        (GInstanceInitFunc) pango_ft2_font_map_init,
      };

      object_type = g_type_register_static (PANGO_TYPE_FC_FONT_MAP,
                                            "PangoFT2FontMap",
                                            &object_info, 0);
    }
  
  return object_type;
}

static void
pango_ft2_font_map_class_init (PangoFT2FontMapClass *class)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (class);
  PangoFcFontMapClass *fcfontmap_class = PANGO_FC_FONT_MAP_CLASS (class);
  
  parent_class = g_type_class_peek_parent (class);

  gobject_class->finalize = pango_ft2_font_map_finalize;
  fcfontmap_class->default_substitute = pango_ft2_font_map_default_substitute;
  fcfontmap_class->new_font = pango_ft2_font_map_new_font;
}

static void
pango_ft2_font_map_init (PangoFT2FontMap *fontmap)
{
  fontmap->library = NULL;
  fontmap->dpi_x   = 72.0;
  fontmap->dpi_y   = 72.0;
}

static void
pango_ft2_font_map_finalize (GObject *object)
{
  PangoFT2FontMap *ft2fontmap = PANGO_FT2_FONT_MAP (object);
  
  if (ft2fontmap->substitute_destroy)
    ft2fontmap->substitute_destroy (ft2fontmap->substitute_data);

  FT_Done_FreeType (ft2fontmap->library);

  parent_class->finalize (object);
}

/**
 * pango_ft2_font_map_new:
 * 
 * Create a new #PangoFT2FontMap object; a fontmap is used
 * to cache information about available fonts, and holds
 * certain global parameters such as the resolution and
 * the default substitute function (see
 * pango_ft2_font_map_set_default_substitute()).
 * 
 * Return value: the newly created fontmap object. Unref
 * with g_object_unref() when you are finished with it.
 *
 * Since: 1.2
 **/
PangoFontMap *
pango_ft2_font_map_new (void)
{
  PangoFT2FontMap *ft2fontmap;
  FT_Error error;
  
  /* Make sure that the type system is initialized */
  g_type_init ();
  
  ft2fontmap = g_object_new (PANGO_TYPE_FT2_FONT_MAP, NULL);
  
  error = FT_Init_FreeType (&ft2fontmap->library);
  if (error != FT_Err_Ok)
    {
      g_warning ("Error from FT_Init_FreeType: %s",
		 _pango_ft2_ft_strerror (error));
      return NULL;
    }

  return (PangoFontMap *)ft2fontmap;
}

/**
 * pango_ft2_font_map_set_default_substitute:
 * @fontmap: a #PangoFT2FontMap
 * @func: function to call to to do final config tweaking
 *        on #FcPattern objects.
 * @data: data to pass to @func
 * @notify: function to call when @data is no longer used.
 * 
 * Sets a function that will be called to do final configuration
 * substitution on a #FcPattern before it is used to load
 * the font. This function can be used to do things like set
 * hinting and antialiasing options.
 *
 * Since: 1.2
 **/
void
pango_ft2_font_map_set_default_substitute (PangoFT2FontMap        *fontmap,
					   PangoFT2SubstituteFunc  func,
					   gpointer                data,
					   GDestroyNotify          notify)
{
  if (fontmap->substitute_destroy)
    fontmap->substitute_destroy (fontmap->substitute_data);

  fontmap->substitute_func = func;
  fontmap->substitute_data = data;
  fontmap->substitute_destroy = notify;
  
  pango_fc_font_map_cache_clear (PANGO_FC_FONT_MAP (fontmap));
}

/**
 * pango_ft2_font_map_substitute_changed:
 * @fontmap: a #PangoFT2Fontmap
 * 
 * Call this function any time the results of the
 * default substitution function set with
 * pango_ft2_font_map_set_default_substitute() change.
 * That is, if your subsitution function will return different
 * results for the same input pattern, you must call this function.
 *
 * Since: 1.2
 **/
void
pango_ft2_font_map_substitute_changed (PangoFT2FontMap *fontmap)
{
  pango_fc_font_map_cache_clear (PANGO_FC_FONT_MAP (fontmap));
}

/**
 * pango_ft2_font_map_set_resolution:
 * @fontmap: a #PangoFT2Fontmap 
 * @dpi_x: dots per inch in the X direction
 * @dpi_y: dots per inch in the Y direction
 * 
 * Sets the horizontal and vertical resolutions for the fontmap.
 **/
void
pango_ft2_font_map_set_resolution (PangoFT2FontMap *fontmap,
				   double           dpi_x,
				   double           dpi_y)
{
  g_return_if_fail (PANGO_FT2_IS_FONT_MAP (fontmap));
  
  fontmap->dpi_x = dpi_x;
  fontmap->dpi_y = dpi_y;

  pango_ft2_font_map_substitute_changed (fontmap);
}

/**
 * pango_ft2_font_map_create_context:
 * @fontmap: a #PangoFT2Fontmap
 * 
 * Create a #PangoContext for the given fontmap.
 * 
 * Return value: the newly created context; free with g_object_unref().
 *
 * Since: 1.2
 **/
PangoContext *
pango_ft2_font_map_create_context (PangoFT2FontMap *fontmap)
{
  g_return_val_if_fail (PANGO_FT2_IS_FONT_MAP (fontmap), NULL);
  
  return pango_fc_font_map_create_context (PANGO_FC_FONT_MAP (fontmap));
}

/**
 * pango_ft2_get_context:
 * @dpi_x:  the horizontal dpi of the target device
 * @dpi_y:  the vertical dpi of the target device
 * 
 * Retrieves a #PangoContext for the default PangoFT2 fontmap
 * (see pango_ft2_fontmap_get_for_display()) and sets the resolution
 * for the default fontmap to @dpi_x by @dpi_y.
 *
 * Use of this function is deprecated; see pango_ft2_fontmap_create_context()
 * instead.
 * 
 * Return value: the new #PangoContext
 **/
PangoContext *
pango_ft2_get_context (double dpi_x, double dpi_y)
{
  PangoFontMap *fontmap;
  
  fontmap = pango_ft2_font_map_for_display ();
  pango_ft2_font_map_set_resolution (PANGO_FT2_FONT_MAP (fontmap), dpi_x, dpi_y);

  return pango_ft2_font_map_create_context (PANGO_FT2_FONT_MAP (fontmap));
}

/**
 * pango_ft2_font_map_for_display:
 *
 * Returns a #PangoFT2FontMap. This font map is cached and should
 * not be freed. If the font map is no longer needed, it can
 * be released with pango_ft2_shutdown_display(). Use of the 
 * global PangoFT2 fontmap is deprecated; use pango_ft2_font_map_new()
 * instead.
 *
 * Returns: a #PangoFT2FontMap.
 **/
PangoFontMap *
pango_ft2_font_map_for_display (void)
{
  if (pango_ft2_global_fontmap != NULL)
    return PANGO_FONT_MAP (pango_ft2_global_fontmap);

  pango_ft2_global_fontmap = (PangoFT2FontMap *)pango_ft2_font_map_new ();

  return PANGO_FONT_MAP (pango_ft2_global_fontmap);
}

/**
 * pango_ft2_shutdown_display:
 * 
 * Free the global fontmap. (See pango_ft2_font_map_for_display())
 * Use of the global PangoFT2 fontmap is deprecated.
 **/
void
pango_ft2_shutdown_display (void)
{
  if (pango_ft2_global_fontmap)
    {
      pango_fc_font_map_cache_clear (PANGO_FC_FONT_MAP (pango_ft2_global_fontmap));
      
      g_object_unref (pango_ft2_global_fontmap);
      
      pango_ft2_global_fontmap = NULL;
    }
}

FT_Library
_pango_ft2_font_map_get_library (PangoFontMap *fontmap)
{
  PangoFT2FontMap *ft2fontmap = (PangoFT2FontMap *)fontmap;
  
  return ft2fontmap->library;
}

static void
pango_ft2_font_map_default_substitute (PangoFcFontMap *fcfontmap,
				       FcPattern      *pattern)
{
  PangoFT2FontMap *ft2fontmap = PANGO_FT2_FONT_MAP (fcfontmap);
  FcValue v;

  FcConfigSubstitute (NULL, pattern, FcMatchPattern);

  if (ft2fontmap->substitute_func)
    ft2fontmap->substitute_func (pattern, ft2fontmap->substitute_data);

  if (FcPatternGet (pattern, FC_DPI, 0, &v) == FcResultNoMatch)
    FcPatternAddDouble (pattern, FC_DPI, ft2fontmap->dpi_y);
  FcDefaultSubstitute (pattern);
}

static PangoFcFont *
pango_ft2_font_map_new_font (PangoFcFontMap  *fcfontmap,
			     FcPattern       *pattern)
{
  return (PangoFcFont *)_pango_ft2_font_new (PANGO_FT2_FONT_MAP (fcfontmap), pattern);
}
