/* GDK - The GIMP Drawing Kit
 * Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald
 * Copyright (C) 1998-2002 Tor Lillqvist
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

/*
 * Modified by the GTK+ Team and others 1997-2000.  See the AUTHORS
 * file for a list of people on the GTK+ Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * GTK+ at ftp://ftp.gtk.org/pub/gtk/. 
 */

#include <config.h>
#include <stdlib.h>

#include "gdk.h" /* gdk_rectangle_intersect */
#include "gdkevents.h"
#include "gdkpixmap.h"
#include "gdkwindow.h"
#include "gdkdisplay.h"
#include "gdkprivate-win32.h"
#include "gdkinput-win32.h"

#if defined __MINGW32__ || (WINVER < 0x0500)
typedef struct { 
  DWORD        bV5Size; 
  LONG         bV5Width; 
  LONG         bV5Height; 
  WORD         bV5Planes; 
  WORD         bV5BitCount; 
  DWORD        bV5Compression; 
  DWORD        bV5SizeImage; 
  LONG         bV5XPelsPerMeter; 
  LONG         bV5YPelsPerMeter; 
  DWORD        bV5ClrUsed; 
  DWORD        bV5ClrImportant; 
  DWORD        bV5RedMask; 
  DWORD        bV5GreenMask; 
  DWORD        bV5BlueMask; 
  DWORD        bV5AlphaMask; 
  DWORD        bV5CSType; 
  CIEXYZTRIPLE bV5Endpoints; 
  DWORD        bV5GammaRed; 
  DWORD        bV5GammaGreen; 
  DWORD        bV5GammaBlue; 
  DWORD        bV5Intent; 
  DWORD        bV5ProfileData; 
  DWORD        bV5ProfileSize; 
  DWORD        bV5Reserved; 
} BITMAPV5HEADER;

#endif

#if 0
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <stdio.h>
#endif

static GdkColormap* gdk_window_impl_win32_get_colormap (GdkDrawable *drawable);
static void         gdk_window_impl_win32_set_colormap (GdkDrawable *drawable,
							GdkColormap *cmap);
static void         gdk_window_impl_win32_get_size     (GdkDrawable *drawable,
							gint *width,
							gint *height);
static GdkRegion*   gdk_window_impl_win32_get_visible_region (GdkDrawable *drawable);
static void gdk_window_impl_win32_init       (GdkWindowImplWin32      *window);
static void gdk_window_impl_win32_class_init (GdkWindowImplWin32Class *klass);
static void gdk_window_impl_win32_finalize   (GObject                 *object);

static gpointer parent_class = NULL;

GType
_gdk_window_impl_win32_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (GdkWindowImplWin32Class),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) gdk_window_impl_win32_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (GdkWindowImplWin32),
        0,              /* n_preallocs */
        (GInstanceInitFunc) gdk_window_impl_win32_init,
      };
      
      object_type = g_type_register_static (GDK_TYPE_DRAWABLE_IMPL_WIN32,
                                            "GdkWindowImplWin32",
                                            &object_info, 0);
    }
  
  return object_type;
}

GType
_gdk_window_impl_get_type (void)
{
  return _gdk_window_impl_win32_get_type ();
}

static void
gdk_window_impl_win32_init (GdkWindowImplWin32 *impl)
{
  impl->width = 1;
  impl->height = 1;

  impl->hcursor = NULL;
  impl->hicon_big = NULL;
  impl->hicon_small = NULL;
  impl->hint_flags = 0;
  impl->extension_events_selected = FALSE;
}

static void
gdk_window_impl_win32_class_init (GdkWindowImplWin32Class *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GdkDrawableClass *drawable_class = GDK_DRAWABLE_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = gdk_window_impl_win32_finalize;

  drawable_class->set_colormap = gdk_window_impl_win32_set_colormap;
  drawable_class->get_colormap = gdk_window_impl_win32_get_colormap;
  drawable_class->get_size = gdk_window_impl_win32_get_size;

  /* Visible and clip regions are the same */
  drawable_class->get_clip_region = gdk_window_impl_win32_get_visible_region;
  drawable_class->get_visible_region = gdk_window_impl_win32_get_visible_region;
}

static void
gdk_window_impl_win32_finalize (GObject *object)
{
  GdkWindowObject *wrapper;
  GdkDrawableImplWin32 *draw_impl;
  GdkWindowImplWin32 *window_impl;
  
  g_return_if_fail (GDK_IS_WINDOW_IMPL_WIN32 (object));

  draw_impl = GDK_DRAWABLE_IMPL_WIN32 (object);
  window_impl = GDK_WINDOW_IMPL_WIN32 (object);
  
  wrapper = (GdkWindowObject*) draw_impl->wrapper;

  if (!GDK_WINDOW_DESTROYED (wrapper))
    {
      gdk_win32_handle_table_remove (draw_impl->handle);
    }

  if (window_impl->hcursor != NULL)
    {
      if (GetCursor () == window_impl->hcursor)
	SetCursor (NULL);
      GDI_CALL (DestroyCursor, (window_impl->hcursor));
      window_impl->hcursor = NULL;
    }
  if (window_impl->hicon_big != NULL)
    {
      GDI_CALL (DestroyIcon, (window_impl->hicon_big));
      window_impl->hicon_big = NULL;
    }
  if (window_impl->hicon_small != NULL)
    {
      GDI_CALL (DestroyIcon, (window_impl->hicon_small));
      window_impl->hicon_small = NULL;
    }

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

void
_gdk_win32_adjust_client_rect (GdkWindow *window,
			       RECT      *rect)
{
  LONG style, exstyle;

  style = GetWindowLong (GDK_WINDOW_HWND (window), GWL_STYLE);
  exstyle = GetWindowLong (GDK_WINDOW_HWND (window), GWL_EXSTYLE);
  API_CALL (AdjustWindowRectEx, (rect, style, FALSE, exstyle));
}

void
_gdk_win32_get_adjusted_client_rect (GdkWindow *window,
				     RECT      *rect)
{
  GetClientRect (GDK_WINDOW_HWND (window), rect);
  _gdk_win32_adjust_client_rect (window, rect);
}

static GdkColormap*
gdk_window_impl_win32_get_colormap (GdkDrawable *drawable)
{
  GdkDrawableImplWin32 *drawable_impl;
  
  g_return_val_if_fail (GDK_IS_WINDOW_IMPL_WIN32 (drawable), NULL);

  drawable_impl = GDK_DRAWABLE_IMPL_WIN32 (drawable);

  if (!((GdkWindowObject *) drawable_impl->wrapper)->input_only && 
      drawable_impl->colormap == NULL)
    {
      drawable_impl->colormap = gdk_colormap_get_system ();
      g_object_ref (drawable_impl->colormap);
    }
  
  return drawable_impl->colormap;
}

static void
gdk_window_impl_win32_set_colormap (GdkDrawable *drawable,
				    GdkColormap *cmap)
{
  GdkWindowImplWin32 *impl;
  GdkDrawableImplWin32 *draw_impl;
  
  g_return_if_fail (GDK_IS_WINDOW_IMPL_WIN32 (drawable));

  impl = GDK_WINDOW_IMPL_WIN32 (drawable);
  draw_impl = GDK_DRAWABLE_IMPL_WIN32 (drawable);

  /* chain up */
  GDK_DRAWABLE_CLASS (parent_class)->set_colormap (drawable, cmap);
  
  if (cmap)
    {
      /* XXX */
      g_print("gdk_window_impl_win32_set_colormap: XXX\n");
    }
}

static void
gdk_window_impl_win32_get_size (GdkDrawable *drawable,
				gint        *width,
				gint        *height)
{
  g_return_if_fail (GDK_IS_WINDOW_IMPL_WIN32 (drawable));

  if (width)
    *width = GDK_WINDOW_IMPL_WIN32 (drawable)->width;
  if (height)
    *height = GDK_WINDOW_IMPL_WIN32 (drawable)->height;
}

static GdkRegion*
gdk_window_impl_win32_get_visible_region (GdkDrawable *drawable)
{
  GdkWindowImplWin32 *impl = GDK_WINDOW_IMPL_WIN32 (drawable);
  GdkRectangle result_rect;

  result_rect.x = 0;
  result_rect.y = 0;
  result_rect.width = impl->width;
  result_rect.height = impl->height;

  gdk_rectangle_intersect (&result_rect, &impl->position_info.clip_rect, &result_rect);

  return gdk_region_rectangle (&result_rect);
}

void
_gdk_windowing_window_init (void)
{
  GdkWindowObject *private;
  GdkWindowImplWin32 *impl;
  GdkDrawableImplWin32 *draw_impl;
  GdkRectangle rect;
  gint i;

  g_assert (_gdk_parent_root == NULL);
  
  _gdk_parent_root = g_object_new (GDK_TYPE_WINDOW, NULL);
  private = (GdkWindowObject *)_gdk_parent_root;
  impl = GDK_WINDOW_IMPL_WIN32 (private->impl);
  draw_impl = GDK_DRAWABLE_IMPL_WIN32 (private->impl);
  
  draw_impl->handle = _gdk_root_window;
  draw_impl->wrapper = GDK_DRAWABLE (private);
  draw_impl->colormap = gdk_colormap_get_system ();
  g_object_ref (draw_impl->colormap);
  
  private->window_type = GDK_WINDOW_ROOT;
  private->depth = gdk_visual_get_system ()->depth;

  rect = _gdk_monitors[0];
  for (i = 1; i < _gdk_num_monitors; i++)
    gdk_rectangle_union (&rect, _gdk_monitors+i, &rect);

  impl->width = rect.width;
  impl->height = rect.height;

  _gdk_window_init_position (GDK_WINDOW (private));

  gdk_win32_handle_table_insert (&_gdk_root_window, _gdk_parent_root);

  GDK_NOTE (MISC, g_print ("_gdk_parent_root=%p\n", GDK_WINDOW_HWND (_gdk_parent_root)));
}

static const gchar *
get_default_title (void)
{
  const char *title;
  title = g_get_application_name ();
  if (!title)
    title = g_get_prgname ();

  return title;
}

/* RegisterGdkClass
 *   is a wrapper function for RegisterWindowClassEx.
 *   It creates at least one unique class for every 
 *   GdkWindowType. If support for single window-specific icons
 *   is ever needed (e.g Dialog specific), every such window should
 *   get its own class
 */
static ATOM
RegisterGdkClass (GdkWindowType wtype)
{
  static ATOM klassTOPLEVEL = 0;
  static ATOM klassDIALOG   = 0;
  static ATOM klassCHILD    = 0;
  static ATOM klassTEMP     = 0;
  static HICON hAppIcon = NULL;
  static WNDCLASSEX wcl; 
  ATOM klass = 0;

  wcl.cbSize = sizeof (WNDCLASSEX);
  wcl.style = 0; /* DON'T set CS_<H,V>REDRAW. It causes total redraw
                  * on WM_SIZE and WM_MOVE. Flicker, Performance!
                  */
  wcl.lpfnWndProc = _gdk_win32_window_procedure;
  wcl.cbClsExtra = 0;
  wcl.cbWndExtra = 0;
  wcl.hInstance = _gdk_app_hmodule;
  wcl.hIcon = 0;
  /* initialize once! */
  if (0 == hAppIcon)
    {
      gchar sLoc [MAX_PATH+1];

      if (0 != GetModuleFileName (_gdk_app_hmodule, sLoc, MAX_PATH))
	{
	  hAppIcon = ExtractIcon (_gdk_app_hmodule, sLoc, 0);
	  if (0 == hAppIcon)
	    {
	      if (0 != GetModuleFileName (_gdk_dll_hinstance, sLoc, MAX_PATH))
		hAppIcon = ExtractIcon (_gdk_dll_hinstance, sLoc, 0);
	    }
	}
      if (0 == hAppIcon) 
	hAppIcon = LoadIcon (NULL, IDI_APPLICATION);
    }

  wcl.lpszMenuName = NULL;
  wcl.hIconSm = 0;

  /* initialize once per class */
  /*
   * HB: Setting the background brush leads to flicker, because we
   * don't get asked how to clear the background. This is not what
   * we want, at least not for input_only windows ...
   */
#define ONCE_PER_CLASS() \
  wcl.hIcon = CopyIcon (hAppIcon); \
  wcl.hIconSm = CopyIcon (hAppIcon); \
  wcl.hbrBackground = NULL; \
  wcl.hCursor = LoadCursor (NULL, IDC_ARROW); 
  
  switch (wtype)
    {
    case GDK_WINDOW_TOPLEVEL:
      if (0 == klassTOPLEVEL)
	{
	  wcl.lpszClassName = "gdkWindowToplevel";
	  
	  ONCE_PER_CLASS();
	  klassTOPLEVEL = RegisterClassEx (&wcl);
	}
      klass = klassTOPLEVEL;
      break;
      
    case GDK_WINDOW_CHILD:
      if (0 == klassCHILD)
	{
	  wcl.lpszClassName = "gdkWindowChild";
	  
	  wcl.style |= CS_PARENTDC; /* MSDN: ... enhances system performance. */
	  ONCE_PER_CLASS();
	  klassCHILD = RegisterClassEx (&wcl);
	}
      klass = klassCHILD;
      break;
      
    case GDK_WINDOW_DIALOG:
      if (0 == klassDIALOG)
	{
	  wcl.lpszClassName = "gdkWindowDialog";
	  wcl.style |= CS_SAVEBITS;
	  ONCE_PER_CLASS();
	  klassDIALOG = RegisterClassEx (&wcl);
	}
      klass = klassDIALOG;
      break;
      
    case GDK_WINDOW_TEMP:
      if (0 == klassTEMP)
	{
	  wcl.lpszClassName = "gdkWindowTemp";
	  wcl.style |= CS_SAVEBITS;
	  ONCE_PER_CLASS();
	  klassTEMP = RegisterClassEx (&wcl);
	}
      klass = klassTEMP;
      break;
      
    default:
      g_assert_not_reached ();
      break;
    }
  
  if (klass == 0)
    {
      WIN32_API_FAILED ("RegisterClassEx");
      g_error ("That is a fatal error");
    }
  return klass;
}

GdkWindow*
gdk_window_new (GdkWindow     *parent,
		GdkWindowAttr *attributes,
		gint           attributes_mask)
{
  HANDLE hparent;
  ATOM klass = 0;
  DWORD dwStyle = 0, dwExStyle;
  RECT rect;
  GdkWindow *window;
  GdkWindowObject *private;
  GdkWindowImplWin32 *impl;
  GdkDrawableImplWin32 *draw_impl;
  GdkScreen *screen;
  GdkVisual *visual;
  const gchar *title;
  char *mbtitle;
  gint window_width, window_height;
  gint offset_x = 0, offset_y = 0;

  g_return_val_if_fail (attributes != NULL, NULL);

  if (!parent)
    {
      screen = gdk_screen_get_default ();
      parent = gdk_screen_get_root_window (screen);
    }
  else
    screen = gdk_drawable_get_screen (parent);

  g_return_val_if_fail (GDK_IS_WINDOW (parent), NULL);
  
  GDK_NOTE (MISC,
	    g_print ("gdk_window_new: %s\n",
		     (attributes->window_type == GDK_WINDOW_TOPLEVEL ? "TOPLEVEL" :
		      (attributes->window_type == GDK_WINDOW_CHILD ? "CHILD" :
		       (attributes->window_type == GDK_WINDOW_DIALOG ? "DIALOG" :
			(attributes->window_type == GDK_WINDOW_TEMP ? "TEMP" :
			 "???"))))));

  if (GDK_WINDOW_DESTROYED (parent))
    return NULL;
  
  hparent = GDK_WINDOW_HWND (parent);

  window = g_object_new (GDK_TYPE_WINDOW, NULL);
  private = (GdkWindowObject *)window;
  impl = GDK_WINDOW_IMPL_WIN32 (private->impl);
  draw_impl = GDK_DRAWABLE_IMPL_WIN32 (private->impl);
  draw_impl->wrapper = GDK_DRAWABLE (window);

  /* Windows with a foreign parent are treated as if they are children
   * of the root window, except for actual creation.
   */
  if (GDK_WINDOW_TYPE (parent) == GDK_WINDOW_FOREIGN)
    parent = _gdk_parent_root;
  
  private->parent = (GdkWindowObject *)parent;

  private->accept_focus = TRUE;

  if (attributes_mask & GDK_WA_X)
    private->x = attributes->x;
  else
    private->x = 0;
  
  if (attributes_mask & GDK_WA_Y)
    private->y = attributes->y;
  else if (attributes_mask & GDK_WA_X)
    private->y = 100;		/* ??? We must put it somewhere... */
  else
    private->y = 0;
  
  if (attributes_mask & GDK_WA_VISUAL)
    visual = attributes->visual;
  else
    visual = gdk_visual_get_system ();

  impl->width = (attributes->width > 1) ? (attributes->width) : (1);
  impl->height = (attributes->height > 1) ? (attributes->height) : (1);
  impl->extension_events_selected = FALSE;
  private->window_type = attributes->window_type;

  if (attributes->wclass == GDK_INPUT_OUTPUT)
    {
      dwExStyle = 0;

      private->input_only = FALSE;
      private->depth = visual->depth;
      
      if (attributes_mask & GDK_WA_COLORMAP)
	{
	  draw_impl->colormap = attributes->colormap;
          g_object_ref (attributes->colormap);
        }
      else
	{
	  draw_impl->colormap = gdk_screen_get_system_colormap (screen);
	  g_object_ref (draw_impl->colormap);
	}
    }
  else
    {
      dwExStyle = WS_EX_TRANSPARENT;
      private->depth = 0;
      private->input_only = TRUE;
      draw_impl->colormap = gdk_colormap_get_system ();
      g_object_ref (draw_impl->colormap);
      GDK_NOTE (MISC, g_print ("...GDK_INPUT_ONLY, system colormap"));
    }

  switch (private->window_type)
    {
    case GDK_WINDOW_TOPLEVEL:
      dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;
      hparent = _gdk_root_window;
      offset_x = _gdk_offset_x;
      offset_y = _gdk_offset_y;
      break;

    case GDK_WINDOW_CHILD:
      dwStyle = WS_CHILDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
      break;

    case GDK_WINDOW_DIALOG:
      dwStyle = WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU | WS_CAPTION | WS_THICKFRAME | WS_CLIPCHILDREN;
#if 0
      dwExStyle |= WS_EX_TOPMOST; /* //HB: want this? */
#endif
      hparent = _gdk_root_window;
      offset_x = _gdk_offset_x;
      offset_y = _gdk_offset_y;
      break;

    case GDK_WINDOW_TEMP:
      dwStyle = WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
      /* a temp window is not necessarily a top level window */
      dwStyle |= (_gdk_parent_root == parent ? WS_POPUP : WS_CHILDWINDOW);
      dwExStyle |= WS_EX_TOOLWINDOW;
      offset_x = _gdk_offset_x;
      offset_y = _gdk_offset_y;
      break;

    case GDK_WINDOW_ROOT:
      g_error ("cannot make windows of type GDK_WINDOW_ROOT");
      break;

    default:
      g_assert_not_reached ();
    }

  _gdk_window_init_position (GDK_WINDOW (private));

  if (private->window_type != GDK_WINDOW_CHILD)
    {
      rect.left = rect.top = 0;
      rect.right = impl->position_info.width;
      rect.bottom = impl->position_info.height;

      AdjustWindowRectEx (&rect, dwStyle, FALSE, dwExStyle);

      window_width = rect.right - rect.left;
      window_height = rect.bottom - rect.top;
    }
  else
    {
      window_width = impl->position_info.width;
      window_height = impl->position_info.height;
    }

  if (impl->position_info.big)
    private->guffaw_gravity = TRUE;

  if (attributes_mask & GDK_WA_TITLE)
    title = attributes->title;
  else
    title = get_default_title ();
  if (!title || !*title)
    title = "GDK client window";

  private->event_mask = GDK_STRUCTURE_MASK | attributes->event_mask;
      
  if (private->parent && private->parent->guffaw_gravity)
    {
      /* XXX ??? */
    }

  if (private->parent)
    private->parent->children = g_list_prepend (private->parent->children, window);

  klass = RegisterGdkClass (private->window_type);

  mbtitle = g_locale_from_utf8 (title, -1, NULL, NULL, NULL);
  
#ifdef WITHOUT_WM_CREATE
  draw_impl->handle =
    CreateWindowEx (dwExStyle,
		    MAKEINTRESOURCE(klass),
		    mbtitle,
		    dwStyle,
		    ((attributes_mask & GDK_WA_X) ?
		     impl->position_info.x - offset_x : CW_USEDEFAULT),
		    impl->position_info.y - offset_y, 
		    window_width, window_height,
		    hparent,
		    NULL,
		    _gdk_app_hmodule,
		    NULL);
#else
  {
  HWND hwndNew =
    CreateWindowEx (dwExStyle,
		    MAKEINTRESOURCE(klass),
		    mbtitle,
		    dwStyle,
		    ((attributes_mask & GDK_WA_X) ?
		     impl->position_info.x - offset_x: CW_USEDEFAULT),
		    impl->position_info.y - offset_y, 
		    window_width, window_height,
		    hparent,
		    NULL,
		    _gdk_app_hmodule,
		    window);
  if (GDK_WINDOW_HWND (window) != hwndNew)
    {
      g_warning("gdk_window_new: gdk_event_translate::WM_CREATE (%p, %p) HWND mismatch.",
		GDK_WINDOW_HWND (window),
		hwndNew);

      /* HB: IHMO due to a race condition the handle was increased by
       * one, which causes much trouble. Because I can't find the 
       * real bug, try to workaround it ...
       * To reproduce: compile with MSVC 5, DEBUG=1
       */
# if 0
      gdk_win32_handle_table_remove (GDK_WINDOW_HWND (window));
      GDK_WINDOW_HWND (window) = hwndNew;
      gdk_win32_handle_table_insert (&GDK_WINDOW_HWND (window), window);
# else
      /* the old behaviour, but with warning */
      draw_impl->handle = hwndNew;
# endif

    }
  }
  g_object_ref (window);
  gdk_win32_handle_table_insert (&GDK_WINDOW_HWND (window), window);
#endif

  GDK_NOTE (MISC, g_print ("... \"%s\" %dx%d@+%d+%d %p = %p\n",
			   mbtitle,
			   window_width, window_height,
			   ((attributes_mask & GDK_WA_X) ?
			    impl->position_info.x - offset_x: CW_USEDEFAULT),
			   impl->position_info.y - offset_y, 
			   hparent,
			   GDK_WINDOW_HWND (window)));

  g_free (mbtitle);

  if (draw_impl->handle == NULL)
    {
      WIN32_API_FAILED ("CreateWindowEx");
      g_object_unref (window);
      return NULL;
    }

#ifdef WITHOUT_WM_CREATE
  g_object_ref (window);
  gdk_win32_handle_table_insert (&GDK_WINDOW_HWND (window), window);
#endif

  gdk_window_set_cursor (window, ((attributes_mask & GDK_WA_CURSOR) ?
				  (attributes->cursor) :
				  NULL));

  return window;
}

GdkWindow *
gdk_window_foreign_new_for_display (GdkDisplay      *display,
                                    GdkNativeWindow  anid)
{
  GdkWindow *window;
  GdkWindowObject *private;
  GdkWindowImplWin32 *impl;
  GdkDrawableImplWin32 *draw_impl;

  HANDLE parent;
  RECT rect;
  POINT point;

  g_return_val_if_fail (display == gdk_display_get_default (), NULL);

  window = g_object_new (GDK_TYPE_WINDOW, NULL);
  private = (GdkWindowObject *)window;
  impl = GDK_WINDOW_IMPL_WIN32 (private->impl);
  draw_impl = GDK_DRAWABLE_IMPL_WIN32 (private->impl);
  draw_impl->wrapper = GDK_DRAWABLE (window);
  parent = GetParent ((HWND)anid);
  
  private->parent = gdk_win32_handle_table_lookup ((GdkNativeWindow) parent);
  if (!private->parent || GDK_WINDOW_TYPE (private->parent) == GDK_WINDOW_FOREIGN)
    private->parent = (GdkWindowObject *)_gdk_parent_root;
  
  private->parent->children = g_list_prepend (private->parent->children, window);

  draw_impl->handle = (HWND) anid;
  GetClientRect ((HWND) anid, &rect);
  point.x = rect.left;
  point.y = rect.right;
  ClientToScreen ((HWND) anid, &point);
  if (parent != _gdk_root_window)
    ScreenToClient (parent, &point);
  private->x = point.x;
  private->y = point.y;
  impl->width = rect.right - rect.left;
  impl->height = rect.bottom - rect.top;
  private->window_type = GDK_WINDOW_FOREIGN;
  private->destroyed = FALSE;
  private->event_mask = GDK_ALL_EVENTS_MASK; /* XXX */
  if (IsWindowVisible ((HWND) anid))
    private->state &= (~GDK_WINDOW_STATE_WITHDRAWN);
  else
    private->state |= GDK_WINDOW_STATE_WITHDRAWN;
  if (GetWindowLong ((HWND)anid, GWL_EXSTYLE) & WS_EX_TOPMOST)
    private->state |= GDK_WINDOW_STATE_ABOVE;
  else
    private->state &= (~GDK_WINDOW_STATE_ABOVE);
  private->state &= (~GDK_WINDOW_STATE_BELOW);

  private->depth = gdk_visual_get_system ()->depth;

  _gdk_window_init_position (GDK_WINDOW (private));

  g_object_ref (window);
  gdk_win32_handle_table_insert (&GDK_WINDOW_HWND (window), window);

  return window;
}

GdkWindow*
gdk_window_lookup (GdkNativeWindow hwnd)
{
  return (GdkWindow*) gdk_win32_handle_table_lookup (hwnd); 
}

void
_gdk_windowing_window_destroy (GdkWindow *window,
			       gboolean   recursing,
			       gboolean   foreign_destroy)
{
  GdkWindowObject *private = (GdkWindowObject *)window;

  g_return_if_fail (GDK_IS_WINDOW (window));
  
  GDK_NOTE (MISC, g_print ("_gdk_windowing_window_destroy: %p\n",
			   GDK_WINDOW_HWND (window)));

  if (private->extension_events != 0)
    _gdk_input_window_destroy (window);


  if (!recursing && !foreign_destroy)
    {
      private->destroyed = TRUE;
      DestroyWindow (GDK_WINDOW_HWND (window));
    }
}

void
_gdk_windowing_window_destroy_foreign (GdkWindow *window)
{
  /* It's somebody else's window, but in our hierarchy,
   * so reparent it to the root window, and then call
   * DestroyWindow() on it.
   */
  gdk_window_hide (window);
  gdk_window_reparent (window, NULL, 0, 0);
  
  /* Is this too drastic? Many (most?) applications
   * quit if any window receives WM_QUIT I think.
   * OTOH, I don't think foreign windows are much
   * used, so the question is maybe academic.
   */
  PostMessage (GDK_WINDOW_HWND (window), WM_QUIT, 0, 0);
}

/* This function is called when the window really gone.
 */
void
gdk_window_destroy_notify (GdkWindow *window)
{
  g_return_if_fail (window != NULL);
  g_return_if_fail (GDK_IS_WINDOW (window));

  GDK_NOTE (EVENTS,
	    g_print ("gdk_window_destroy_notify: %p%s\n",
		     GDK_WINDOW_HWND (window),
		     (GDK_WINDOW_DESTROYED (window) ? " (destroyed)" : "")));

  if (!GDK_WINDOW_DESTROYED (window))
    {
      if (GDK_WINDOW_TYPE(window) != GDK_WINDOW_FOREIGN)
	g_warning ("window %p unexpectedly destroyed",
		   GDK_WINDOW_HWND (window));

      _gdk_window_destroy (window, TRUE);
    }
  
  gdk_win32_handle_table_remove (GDK_WINDOW_HWND (window));
  g_object_unref (window);
}

static void
get_outer_rect (GdkWindow *window,
		gint       width,
		gint       height,
		RECT      *rect)
{
  LONG style, exstyle;
      
  style = GetWindowLong (GDK_WINDOW_HWND (window), GWL_STYLE);
  exstyle = GetWindowLong (GDK_WINDOW_HWND (window), GWL_EXSTYLE);
      
  rect->left = rect->top = 0;
  rect->right = width;
  rect->bottom = height;
      
  API_CALL (AdjustWindowRectEx, (rect, style, FALSE, exstyle));
}

static void
adjust_for_gravity_hints (GdkWindowImplWin32 *impl,
			  RECT               *outer_rect,
			  gint		     *x,
			  gint		     *y)
{
  if (impl->hint_flags & GDK_HINT_WIN_GRAVITY)
    {
      gint orig_x = *x, orig_y = *y;

      switch (impl->hints.win_gravity)
	{
	case GDK_GRAVITY_NORTH:
	case GDK_GRAVITY_CENTER:
	case GDK_GRAVITY_SOUTH:
	  *x -= (outer_rect->right - outer_rect->left) / 2;
	  *x += impl->width / 2;
	  break;
	      
	case GDK_GRAVITY_SOUTH_EAST:
	case GDK_GRAVITY_EAST:
	case GDK_GRAVITY_NORTH_EAST:
	  *x -= outer_rect->right - outer_rect->left;
	  *x += impl->width;
	  break;

	case GDK_GRAVITY_STATIC:
	  *x += outer_rect->left;
	  break;

	default:
	  break;
	}

      switch (impl->hints.win_gravity)
	{
	case GDK_GRAVITY_WEST:
	case GDK_GRAVITY_CENTER:
	case GDK_GRAVITY_EAST:
	  *y -= (outer_rect->bottom - outer_rect->top) / 2;
	  *y += impl->height / 2;
	  break;

	case GDK_GRAVITY_SOUTH_WEST:
	case GDK_GRAVITY_SOUTH:
	case GDK_GRAVITY_SOUTH_EAST:
	  *y -= outer_rect->bottom - outer_rect->top;
	  *y += impl->height;
	  break;

	case GDK_GRAVITY_STATIC:
	  *y += outer_rect->top;
	  break;

	default:
	  break;
	}
      GDK_NOTE (MISC,
		(orig_x != *x || orig_y != *y) ?
		g_print ("adjust_for_gravity_hints: x: %d->%d, y: %d->%d\n",
			 orig_x, *x, orig_y, *y)
		  : (void) 0);
    }
}

static void
show_window_internal (GdkWindow *window,
                      gboolean   raise,
		      gboolean   deiconify)
{
  GdkWindowObject *private;
  HWND old_active_window;
  
  private = (GdkWindowObject *) window;

  if (private->destroyed)
    return;

  GDK_NOTE (MISC, g_print ("show_window_internal: %p: %s%s%s\n",
			   GDK_WINDOW_HWND (window),
			   _gdk_win32_window_state_to_string (private->state),
			   (raise ? " raise" : ""),
			   (deiconify ? " deiconify" : "")));
  
  /* If asked to show (not deiconify) an withdrawn and iconified
   * window, do that.
   */
  if (!deiconify &&
      !GDK_WINDOW_IS_MAPPED (window) &&
      (private->state & GDK_WINDOW_STATE_ICONIFIED))
    {	
      ShowWindow (GDK_WINDOW_HWND (window), SW_MINIMIZE);
      return;
    }
  
  /* If asked to just show an iconified window, do nothing. */
  if (!deiconify && (private->state & GDK_WINDOW_STATE_ICONIFIED))
    return;
  
  /* If asked to deiconify an already noniconified window, do
   * nothing. (Especially, don't cause the window to rise and
   * activate. There are different calls for that.)
   */
  if (deiconify && !(private->state & GDK_WINDOW_STATE_ICONIFIED))
    return;
  
  /* If asked to show (but not raise) a window that is already
   * visible, do nothing.
   */
  if (!deiconify && !raise && IsWindowVisible (GDK_WINDOW_HWND (window)))
    return;

  /* Other cases */
  
  if (!GDK_WINDOW_IS_MAPPED (window))
    gdk_synthesize_window_state (window,
				 GDK_WINDOW_STATE_WITHDRAWN,
				 0);

  /* Use SetWindowPos to show transparent windows so automatic redraws
   * in other windows can be suppressed.
   */
  if (GetWindowLong (GDK_WINDOW_HWND (window), GWL_EXSTYLE) & WS_EX_TRANSPARENT)
    {
      UINT flags = SWP_SHOWWINDOW | SWP_NOREDRAW | SWP_NOMOVE | SWP_NOSIZE;
      if (!raise)
	flags |= SWP_NOZORDER;
      if (!raise || GDK_WINDOW_TYPE (window) == GDK_WINDOW_TEMP)
	flags |= SWP_NOACTIVATE;

      SetWindowPos (GDK_WINDOW_HWND (window), HWND_TOP, 0, 0, 0, 0, flags);
      return;
    }

  old_active_window = GetActiveWindow ();

  if (private->state & (GDK_WINDOW_STATE_BELOW | GDK_WINDOW_STATE_ABOVE))
    {
      DWORD exstyle = GetWindowLong (GDK_WINDOW_HWND (window), GWL_EXSTYLE);

      if (private->state & GDK_WINDOW_STATE_BELOW)
        exstyle &= (~WS_EX_TOPMOST);
      if (private->state & GDK_WINDOW_STATE_ABOVE)
        exstyle |= WS_EX_TOPMOST;

      if (!SetWindowLong (GDK_WINDOW_HWND (window), GWL_EXSTYLE, exstyle))
        WIN32_API_FAILED ("SetWindowLong");
    }

  if (private->state & GDK_WINDOW_STATE_FULLSCREEN)
    gdk_window_fullscreen (window);
  else if (private->state & GDK_WINDOW_STATE_MAXIMIZED)
    ShowWindow (GDK_WINDOW_HWND (window), SW_MAXIMIZE);
  else if (private->state & GDK_WINDOW_STATE_ICONIFIED)
    ShowWindow (GDK_WINDOW_HWND (window), SW_RESTORE);
  else if (GDK_WINDOW_TYPE (window) == GDK_WINDOW_TEMP)
    ShowWindow (GDK_WINDOW_HWND (window), SW_SHOWNOACTIVATE);
  else
    ShowWindow (GDK_WINDOW_HWND (window), SW_SHOWNORMAL);

  if (raise)
    if (GDK_WINDOW_TYPE (window) == GDK_WINDOW_TEMP)
      SetWindowPos (GDK_WINDOW_HWND (window), HWND_TOPMOST, 0, 0, 0, 0,
		    SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
    else
      BringWindowToTop (GDK_WINDOW_HWND (window));
  else if (old_active_window != GDK_WINDOW_HWND (window))
    SetActiveWindow (old_active_window);
}

void
gdk_window_show_unraised (GdkWindow *window)
{
  g_return_if_fail (GDK_IS_WINDOW (window));
  
  show_window_internal (window, FALSE, FALSE);
}

void
gdk_window_show (GdkWindow *window)
{
  g_return_if_fail (GDK_IS_WINDOW (window));

  show_window_internal (window, TRUE, FALSE);
}

void
gdk_window_hide (GdkWindow *window)
{
  GdkWindowObject *private;
  
  g_return_if_fail (window != NULL);

  private = (GdkWindowObject*) window;
  if (private->destroyed)
    return;

  GDK_NOTE (MISC, g_print ("gdk_window_hide: %p: %s\n",
			   GDK_WINDOW_HWND (window),
			   _gdk_win32_window_state_to_string (private->state)));
  
  if (GDK_WINDOW_IS_MAPPED (window))
    gdk_synthesize_window_state (window,
				 0,
				 GDK_WINDOW_STATE_WITHDRAWN);
  
  _gdk_window_clear_update_area (window);
  
  if (GDK_WINDOW_TYPE (window) == GDK_WINDOW_TOPLEVEL)
    ShowOwnedPopups (GDK_WINDOW_HWND (window), FALSE);
  
  if (GetWindowLong (GDK_WINDOW_HWND (window), GWL_EXSTYLE) & WS_EX_TRANSPARENT)
    {
      SetWindowPos (GDK_WINDOW_HWND (window), HWND_BOTTOM, 0, 0, 0, 0,
		    SWP_HIDEWINDOW | SWP_NOREDRAW | SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE);
    }
  else
    {
      ShowWindow (GDK_WINDOW_HWND (window), SW_HIDE);
    }
}

void
gdk_window_withdraw (GdkWindow *window)
{
  GdkWindowObject *private;
  
  g_return_if_fail (window != NULL);
  
  private = (GdkWindowObject*) window;
  if (private->destroyed)
    return;

  GDK_NOTE (MISC, g_print ("gdk_window_withdraw: %p: %s\n",
			   GDK_WINDOW_HWND (window),
			   _gdk_win32_window_state_to_string (private->state)));
  
  gdk_window_hide (window);	/* ??? */
}

void
gdk_window_move (GdkWindow *window,
		 gint       x,
		 gint       y)
{
  GdkWindowObject *private = (GdkWindowObject *)window;
  GdkWindowImplWin32 *impl;

  g_return_if_fail (window != NULL);
  g_return_if_fail (GDK_IS_WINDOW (window));

  if (GDK_WINDOW_DESTROYED (window))
    return;

  GDK_NOTE (MISC, g_print ("gdk_window_move: %p: +%d+%d\n",
			   GDK_WINDOW_HWND (window), x, y));
      
  impl = GDK_WINDOW_IMPL_WIN32 (private->impl);

  if (private->state & GDK_WINDOW_STATE_FULLSCREEN)
    return;

  if (GDK_WINDOW_TYPE (private) == GDK_WINDOW_CHILD)
    _gdk_window_move_resize_child (window, x, y, impl->width, impl->height);
  else
    {
      RECT outer_rect;

      get_outer_rect (window, impl->width, impl->height, &outer_rect);
      
      adjust_for_gravity_hints (impl, &outer_rect, &x, &y);

      API_CALL (SetWindowPos, (GDK_WINDOW_HWND (window), NULL,
			       x - _gdk_offset_x, y - _gdk_offset_y, 0, 0,
			       SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER));
    }
}

void
gdk_window_resize (GdkWindow *window,
		   gint       width,
		   gint       height)
{
  GdkWindowObject *private = (GdkWindowObject*) window;
  GdkWindowImplWin32 *impl;

  g_return_if_fail (window != NULL);
  g_return_if_fail (GDK_IS_WINDOW (window));

  if (GDK_WINDOW_DESTROYED (window))
    return;

  if (width < 1)
    width = 1;
  if (height < 1)
    height = 1;

  GDK_NOTE (MISC, g_print ("gdk_window_resize: %p: %dx%d\n",
			   GDK_WINDOW_HWND (window), width, height));

  impl = GDK_WINDOW_IMPL_WIN32 (private->impl);
  
  if (private->state & GDK_WINDOW_STATE_FULLSCREEN)
    return;

  if (GDK_WINDOW_TYPE (private) == GDK_WINDOW_CHILD)
    _gdk_window_move_resize_child (window, private->x, private->y, width, height);
  else
    {
      RECT outer_rect;
      get_outer_rect (window, width, height, &outer_rect);

      API_CALL (SetWindowPos, (GDK_WINDOW_HWND (window), NULL,
			       0, 0,
			       outer_rect.right - outer_rect.left,
			       outer_rect.bottom - outer_rect.top,
			       SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER));
      private->resize_count += 1;
    }
}

void
gdk_window_move_resize (GdkWindow *window,
			gint       x,
			gint       y,
			gint       width,
			gint       height)
{
  GdkWindowObject *private = (GdkWindowObject*) window;
  GdkWindowImplWin32 *impl;

  g_return_if_fail (window != NULL);
  g_return_if_fail (GDK_IS_WINDOW (window));

  if (GDK_WINDOW_DESTROYED (window))
    return;

  if (width < 1)
    width = 1;
  if (height < 1)
    height = 1;
  
  impl = GDK_WINDOW_IMPL_WIN32 (private->impl);

  if (private->state & GDK_WINDOW_STATE_FULLSCREEN)
    return;

  GDK_NOTE (MISC, g_print ("gdk_window_move_resize: %p: %dx%d@+%d+%d\n",
			   GDK_WINDOW_HWND (window),
			   width, height, x, y));
  
  if (GDK_WINDOW_TYPE (private) == GDK_WINDOW_CHILD)
    _gdk_window_move_resize_child (window, x, y, width, height);
  else
    {
      RECT outer_rect;

      get_outer_rect (window, width, height, &outer_rect);

      adjust_for_gravity_hints (impl, &outer_rect, &x, &y);

      API_CALL (SetWindowPos, (GDK_WINDOW_HWND (window), NULL,
			       x - _gdk_offset_x, y - _gdk_offset_y,
			       outer_rect.right - outer_rect.left,
			       outer_rect.bottom - outer_rect.top,
			       SWP_NOACTIVATE | SWP_NOZORDER));
    }
}

void
gdk_window_reparent (GdkWindow *window,
		     GdkWindow *new_parent,
		     gint       x,
		     gint       y)
{
  GdkWindowObject *window_private;
  GdkWindowObject *parent_private;
  GdkWindowObject *old_parent_private;
  GdkWindowImplWin32 *impl;

  g_return_if_fail (window != NULL);
  g_return_if_fail (GDK_IS_WINDOW (window));
  g_return_if_fail (new_parent == NULL || GDK_IS_WINDOW (new_parent));
  g_return_if_fail (GDK_WINDOW_TYPE (window) != GDK_WINDOW_ROOT);

  if (!new_parent)
    new_parent = _gdk_parent_root;

  window_private = (GdkWindowObject*) window;
  old_parent_private = (GdkWindowObject *) window_private->parent;
  parent_private = (GdkWindowObject*) new_parent;
  impl = GDK_WINDOW_IMPL_WIN32 (window_private->impl);

  if (!GDK_WINDOW_DESTROYED (window) && !GDK_WINDOW_DESTROYED (new_parent))
    {
      GDK_NOTE (MISC, g_print ("gdk_window_reparent: %p: %p\n",
			       GDK_WINDOW_HWND (window),
			       GDK_WINDOW_HWND (new_parent)));

      API_CALL (SetParent, (GDK_WINDOW_HWND (window),
			    GDK_WINDOW_HWND (new_parent)));

      API_CALL (MoveWindow, (GDK_WINDOW_HWND (window),
			     x, y, impl->width, impl->height, TRUE));
    }

  /* From here on, we treat parents of type GDK_WINDOW_FOREIGN like
   * the root window
   */
  if (GDK_WINDOW_TYPE (new_parent) == GDK_WINDOW_FOREIGN)
    new_parent = _gdk_parent_root;
  
  window_private->parent = (GdkWindowObject *)new_parent;

  if (old_parent_private)
    old_parent_private->children =
      g_list_remove (old_parent_private->children, window);

#if 0
  if ((old_parent_private &&
       (!old_parent_private->guffaw_gravity != !parent_private->guffaw_gravity)) ||
      (!old_parent_private && parent_private->guffaw_gravity))
    gdk_window_set_static_win_gravity (window, parent_private->guffaw_gravity);
#endif

  parent_private->children = g_list_prepend (parent_private->children, window);
  _gdk_window_init_position (GDK_WINDOW (window_private));
}

void
_gdk_windowing_window_clear_area (GdkWindow *window,
				  gint       x,
				  gint       y,
				  gint       width,
				  gint       height)
{
  GdkWindowImplWin32 *impl;

  g_return_if_fail (window != NULL);
  g_return_if_fail (GDK_IS_WINDOW (window));
  
  impl = GDK_WINDOW_IMPL_WIN32 (GDK_WINDOW_OBJECT (window)->impl);

  if (!GDK_WINDOW_DESTROYED (window))
    {
      HDC hdc;

      if (width == 0)
	width = impl->width - x;
      if (height == 0)
	height = impl->height - y;
      GDK_NOTE (MISC, g_print ("_gdk_windowing_window_clear_area: %p: "
			       "%dx%d@+%d+%d\n",
			       GDK_WINDOW_HWND (window),
			       width, height, x, y));
      hdc = GetDC (GDK_WINDOW_HWND (window));
      IntersectClipRect (hdc, x, y, x + width + 1, y + height + 1);
      SendMessage (GDK_WINDOW_HWND (window), WM_ERASEBKGND, (WPARAM) hdc, 0);
      GDI_CALL (ReleaseDC, (GDK_WINDOW_HWND (window), hdc));
    }
}

void
_gdk_windowing_window_clear_area_e (GdkWindow *window,
				    gint       x,
				    gint       y,
				    gint       width,
				    gint       height)
{
  g_return_if_fail (window != NULL);
  g_return_if_fail (GDK_IS_WINDOW (window));
  
  if (!GDK_WINDOW_DESTROYED (window))
    {
      RECT rect;

      GDK_NOTE (MISC, g_print ("_gdk_windowing_window_clear_area_e: %p: "
			       "%dx%d@+%d+%d\n",
			       GDK_WINDOW_HWND (window),
			       width, height, x, y));

      rect.left = x;
      rect.right = x + width + 1;
      rect.top = y;
      rect.bottom = y + height + 1;
      GDI_CALL (InvalidateRect, (GDK_WINDOW_HWND (window), &rect, TRUE));
      UpdateWindow (GDK_WINDOW_HWND (window));
    }
}

void
gdk_window_raise (GdkWindow *window)
{
  g_return_if_fail (window != NULL);
  g_return_if_fail (GDK_IS_WINDOW (window));
  
  if (!GDK_WINDOW_DESTROYED (window))
    {
      GDK_NOTE (MISC, g_print ("gdk_window_raise: %p\n",
			       GDK_WINDOW_HWND (window)));

      API_CALL (BringWindowToTop, (GDK_WINDOW_HWND (window)));
    }
}

void
gdk_window_lower (GdkWindow *window)
{
  g_return_if_fail (window != NULL);
  g_return_if_fail (GDK_IS_WINDOW (window));
  
  if (!GDK_WINDOW_DESTROYED (window))
    {
      GDK_NOTE (MISC, g_print ("gdk_window_lower: %p\n",
			       GDK_WINDOW_HWND (window)));

      API_CALL (SetWindowPos, (GDK_WINDOW_HWND (window), HWND_BOTTOM, 0, 0, 0, 0,
			       SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE));
    }
}

void
gdk_window_set_hints (GdkWindow *window,
		      gint       x,
		      gint       y,
		      gint       min_width,
		      gint       min_height,
		      gint       max_width,
		      gint       max_height,
		      gint       flags)
{
  /* Note that this function is obsolete */

  GdkWindowImplWin32 *impl;

  g_return_if_fail (window != NULL);
  g_return_if_fail (GDK_IS_WINDOW (window));
  
  if (GDK_WINDOW_DESTROYED (window))
    return;
  
  impl = GDK_WINDOW_IMPL_WIN32 (GDK_WINDOW_OBJECT (window)->impl);

  GDK_NOTE (MISC, g_print ("gdk_window_set_hints: %p: %dx%d..%dx%d @+%d+%d\n",
			   GDK_WINDOW_HWND (window),
			   min_width, min_height, max_width, max_height,
			   x, y));

  if (flags)
    {
      GdkGeometry geom;
      gint geom_mask = 0;

      geom.min_width  = min_width;
      geom.min_height = min_height;
      geom.max_width  = max_width;
      geom.max_height = max_height;

      if (flags & GDK_HINT_MIN_SIZE)
        geom_mask |= GDK_HINT_MIN_SIZE;

      if (flags & GDK_HINT_MAX_SIZE)
        geom_mask |= GDK_HINT_MAX_SIZE;

      gdk_window_set_geometry_hints (window, &geom, geom_mask);
    }
}

void 
gdk_window_set_geometry_hints (GdkWindow      *window,
			       GdkGeometry    *geometry,
			       GdkWindowHints  geom_mask)
{
  GdkWindowImplWin32 *impl;
#if 0
  WINDOWPLACEMENT size_hints;
  RECT rect;
  gint new_width = 0, new_height = 0;
#endif

  g_return_if_fail (window != NULL);
  g_return_if_fail (GDK_IS_WINDOW (window));
  
  if (GDK_WINDOW_DESTROYED (window))
    return;

  GDK_NOTE (MISC, g_print ("gdk_window_set_geometry_hints: %p\n",
			   GDK_WINDOW_HWND (window)));

  impl = GDK_WINDOW_IMPL_WIN32 (GDK_WINDOW_OBJECT (window)->impl);

  impl->hint_flags = geom_mask;
  impl->hints = *geometry;

  if (geom_mask & GDK_HINT_POS)
    ; /* even the X11 mplementation doesn't care */

  if (geom_mask & GDK_HINT_MIN_SIZE)
    {
      GDK_NOTE (MISC, g_print ("... MIN_SIZE: %dx%d\n",
			       geometry->min_width, geometry->min_height));

#if 0
      /* Check if the current size of the window is in bounds */
      GetClientRect (GDK_WINDOW_HWND (window), &rect);

      if (rect.right < geometry->min_width &&
	  rect.bottom < geometry->min_height)
	{
	  new_width = geometry->min_width;
	  new_height = geometry->min_height;
	}
      else if (rect.right < geometry->min_width)
	{
	  new_width = geometry->min_width;
	  new_height = rect.bottom;
	}
      else if (rect.bottom < geometry->min_height)
	{
	  new_width = rect.right;
	  new_height = geometry->min_height;
	}
#endif
    }
  
  if (geom_mask & GDK_HINT_MAX_SIZE)
    {
      GDK_NOTE (MISC, g_print ("... MAX_SIZE: %dx%d\n",
			       geometry->max_width, geometry->max_height));

#if 0
      /* Check if the current size of the window is in bounds */
      GetClientRect (GDK_WINDOW_HWND (window), &rect);

      if (rect.right > geometry->max_width &&
	  rect.bottom > geometry->max_height)
	{
	  new_width = geometry->max_width;
	  new_height = geometry->max_height;
	}
      else if (rect.right > geometry->max_width)
	{
	  new_width = geometry->max_width;
	  new_height = rect.bottom;
	}
      else if (rect.bottom > geometry->max_height)
	{
	  new_width = rect.right;
	  new_height = geometry->max_height;
	}
#endif
    }

#if 0
  /* Apply new size constraints */
  if (new_width != 0 && new_height != 0)
    gdk_window_resize (window, new_width, new_height);
#endif

  if (geom_mask & GDK_HINT_BASE_SIZE)
    {
      GDK_NOTE (MISC, g_print ("... BASE_SIZE: %dx%d\n",
			       geometry->base_width, geometry->base_height));

#if 0
      size_hints.length = sizeof (size_hints);

      if (API_CALL (GetWindowPlacement, (GDK_WINDOW_HWND (window), &size_hints)))
	{
	  GDK_NOTE (MISC,
		    g_print ("... rcNormalPosition: (%ld,%ld)--(%ld,%ld)\n",
			     size_hints.rcNormalPosition.left,
			     size_hints.rcNormalPosition.top,
			     size_hints.rcNormalPosition.right,
			     size_hints.rcNormalPosition.bottom));
	  size_hints.rcNormalPosition.right =
	    size_hints.rcNormalPosition.left + geometry->base_width;
	  size_hints.rcNormalPosition.bottom =
	    size_hints.rcNormalPosition.top + geometry->base_height;
	  GDK_NOTE (MISC, g_print ("...setting: rcNormal: (%ld,%ld)--(%ld,%ld)\n",
				   size_hints.rcNormalPosition.left,
				   size_hints.rcNormalPosition.top,
				   size_hints.rcNormalPosition.right,
				   size_hints.rcNormalPosition.bottom));
	  API_CALL (SetWindowPlacement, (GDK_WINDOW_HWND (window), &size_hints));
	}
#endif
    }
  
  if (geom_mask & GDK_HINT_RESIZE_INC)
    {
      GDK_NOTE (MISC, g_print ("... RESIZE_INC: (%d,%d)\n",
			       geometry->width_inc, geometry->height_inc));
    }
  
  if (geom_mask & GDK_HINT_ASPECT)
    {
      GDK_NOTE (MISC, g_print ("... ASPECT: %g--%g\n",
			       geometry->min_aspect, geometry->max_aspect));
    }

  if (geom_mask & GDK_HINT_WIN_GRAVITY)
    {
      GDK_NOTE (MISC, g_print ("... GRAVITY: %d\n", geometry->win_gravity));
    }
}

void
gdk_window_set_title (GdkWindow   *window,
		      const gchar *title)
{
  char *mbtitle;

  g_return_if_fail (window != NULL);
  g_return_if_fail (GDK_IS_WINDOW (window));
  g_return_if_fail (title != NULL);

  /* Empty window titles not allowed, so set it to just a period. */
  if (!title[0])
    title = ".";
  
  GDK_NOTE (MISC, g_print ("gdk_window_set_title: %p: %s\n",
			   GDK_WINDOW_HWND (window), title));
  
  if (!GDK_WINDOW_DESTROYED (window))
    {
      /* As the title is in UTF-8 we must translate it
       * to the system codepage.
       */
      mbtitle = g_locale_from_utf8 (title, -1, NULL, NULL, NULL);
      API_CALL (SetWindowText, (GDK_WINDOW_HWND (window), mbtitle));
      g_free (mbtitle);
    }
}

void          
gdk_window_set_role (GdkWindow   *window,
		     const gchar *role)
{
  g_return_if_fail (window != NULL);
  g_return_if_fail (GDK_IS_WINDOW (window));
  
  GDK_NOTE (MISC, g_print ("gdk_window_set_role: %p: %s\n",
			   GDK_WINDOW_HWND (window),
			   (role ? role : "NULL")));
  /* XXX */
}

void          
gdk_window_set_transient_for (GdkWindow *window, 
			      GdkWindow *parent)
{
  HWND window_id, parent_id;

  g_return_if_fail (window != NULL);
  g_return_if_fail (GDK_IS_WINDOW (window));
  
  GDK_NOTE (MISC, g_print ("gdk_window_set_transient_for: %p: %p\n",
			   GDK_WINDOW_HWND (window),
			   GDK_WINDOW_HWND (parent)));

  if (GDK_WINDOW_DESTROYED (window) || GDK_WINDOW_DESTROYED (parent))
    return;

  if (((GdkWindowObject *) window)->window_type == GDK_WINDOW_CHILD)
    {
      GDK_NOTE (MISC, g_print ("...a child window!\n"));
      return;
    }
  
  window_id = GDK_WINDOW_HWND (window);
  parent_id = GDK_WINDOW_HWND (parent);

  /* This changes the *owner* of the window, despite the misleading
   * name. (Owner and parent are unrelated concepts.) At least that's
   * what people who seem to know what they talk about say on
   * USENET. Search on Google.
   */
  SetLastError (0);
  if (SetWindowLong (window_id, GWL_HWNDPARENT, (long) parent_id) == 0 &&
      GetLastError () != 0)
    WIN32_API_FAILED ("SetWindowLong");
}

void
gdk_window_set_background (GdkWindow      *window,
			   const GdkColor *color)
{
  GdkWindowObject *private = (GdkWindowObject *)window;
  
  g_return_if_fail (window != NULL);
  g_return_if_fail (GDK_IS_WINDOW (window));
  
  GDK_NOTE (MISC, g_print ("gdk_window_set_background: %p: %s\n",
			   GDK_WINDOW_HWND (window), 
			   _gdk_win32_color_to_string (color)));

  private->bg_color = *color;

  if (private->bg_pixmap &&
      private->bg_pixmap != GDK_PARENT_RELATIVE_BG &&
      private->bg_pixmap != GDK_NO_BG)
    {
      g_object_unref (private->bg_pixmap);
      private->bg_pixmap = NULL;
    }
}

void
gdk_window_set_back_pixmap (GdkWindow *window,
			    GdkPixmap *pixmap,
			    gint       parent_relative)
{
  GdkWindowObject *private = (GdkWindowObject *)window;

  g_return_if_fail (window != NULL);
  g_return_if_fail (GDK_IS_WINDOW (window));
  g_return_if_fail (pixmap == NULL || !parent_relative);
  g_return_if_fail (pixmap == NULL || gdk_drawable_get_depth (window) == gdk_drawable_get_depth (pixmap));
  
  if (private->bg_pixmap &&
      private->bg_pixmap != GDK_PARENT_RELATIVE_BG &&
      private->bg_pixmap != GDK_NO_BG)
    g_object_unref (private->bg_pixmap);

  if (parent_relative)
    {
      private->bg_pixmap = GDK_PARENT_RELATIVE_BG;
      GDK_NOTE (MISC, g_print (G_STRLOC ": setting background pixmap to parent_relative\n"));
    }
  else
    {
      if (pixmap)
	{
	  g_object_ref (pixmap);
	  private->bg_pixmap = pixmap;
	}
      else
	{
	  private->bg_pixmap = GDK_NO_BG;
	}
    }
}

void
gdk_window_set_cursor (GdkWindow *window,
		       GdkCursor *cursor)
{
  GdkWindowImplWin32 *impl;
  GdkCursorPrivate *cursor_private;
  GdkWindowObject *parent_window;
  HCURSOR hcursor;
  HCURSOR hprevcursor;
  
  g_return_if_fail (window != NULL);
  g_return_if_fail (GDK_IS_WINDOW (window));
  
  impl = GDK_WINDOW_IMPL_WIN32 (GDK_WINDOW_OBJECT (window)->impl);
  cursor_private = (GdkCursorPrivate*) cursor;
  
  if (GDK_WINDOW_DESTROYED (window))
    return;

  if (!cursor)
    hcursor = NULL;
  else
    hcursor = cursor_private->hcursor;
  
  GDK_NOTE (MISC, g_print ("gdk_window_set_cursor: %p: %p\n",
			   GDK_WINDOW_HWND (window),
			   hcursor));

  /* First get the old cursor, if any (we wait to free the old one
   * since it may be the current cursor set in the Win32 API right
   * now).
   */
  hprevcursor = impl->hcursor;

  if (hcursor == NULL)
    impl->hcursor = NULL;
  else
    {
      /* We must copy the cursor as it is OK to destroy the GdkCursor
       * while still in use for some window. See for instance
       * gimp_change_win_cursor() which calls gdk_window_set_cursor
       * (win, cursor), and immediately afterwards gdk_cursor_destroy
       * (cursor).
       */
      if ((impl->hcursor = CopyCursor (hcursor)) == NULL)
	WIN32_API_FAILED ("CopyCursor");
      GDK_NOTE (MISC, g_print ("...CopyCursor (%p) = %p\n",
			       hcursor, impl->hcursor));
    }

  /* If the pointer is over our window, set new cursor if given */
  if (gdk_window_get_pointer(window, NULL, NULL, NULL) == window)
    if (impl->hcursor != NULL)
      SetCursor (impl->hcursor);

  /* Destroy the previous cursor: Need to make sure it's no longer in
   * use before we destroy it, in case we're not over our window but
   * the cursor is still set to our old one.
   */
  if (hprevcursor != NULL)
    {
      if (GetCursor() == hprevcursor)
	{
	  /* Look for a suitable cursor to use instead */
	  hcursor = NULL;
          parent_window = GDK_WINDOW_OBJECT (window)->parent;
          while (hcursor == NULL)
	    {
	      if (parent_window)
		{
		  impl = GDK_WINDOW_IMPL_WIN32 (parent_window->impl);
		  hcursor = impl->hcursor;
		  parent_window = parent_window->parent;
		}
	      else
		{
		  hcursor = LoadCursor (NULL, IDC_ARROW);
		}
	    }
          SetCursor (hcursor);
        }

      GDK_NOTE (MISC, g_print ("...DestroyCursor (%p)\n",
			       hprevcursor));
      
      API_CALL (DestroyCursor, (hprevcursor));
    }
}

void
gdk_window_get_geometry (GdkWindow *window,
			 gint      *x,
			 gint      *y,
			 gint      *width,
			 gint      *height,
			 gint      *depth)
{
  g_return_if_fail (window == NULL || GDK_IS_WINDOW (window));
  
  if (!window)
    window = _gdk_parent_root;
  
  if (!GDK_WINDOW_DESTROYED (window))
    {
      RECT rect;

      API_CALL (GetClientRect, (GDK_WINDOW_HWND (window), &rect));

      if (window != _gdk_parent_root)
	{
	  POINT pt;
	  GdkWindow *parent = gdk_window_get_parent (window);

	  pt.x = rect.left;
	  pt.y = rect.top;
	  ClientToScreen (GDK_WINDOW_HWND (window), &pt);
	  ScreenToClient (GDK_WINDOW_HWND (parent), &pt);
	  rect.left = pt.x;
	  rect.top = pt.y;

	  pt.x = rect.right;
	  pt.y = rect.bottom;
	  ClientToScreen (GDK_WINDOW_HWND (window), &pt);
	  ScreenToClient (GDK_WINDOW_HWND (parent), &pt);
	  rect.right = pt.x;
	  rect.bottom = pt.y;

	  if (parent == _gdk_parent_root)
	    {
	      rect.left += _gdk_offset_x;
	      rect.top += _gdk_offset_y;
	      rect.right += _gdk_offset_x;
	      rect.bottom += _gdk_offset_y;
	    }
	}

      if (x)
	*x = rect.left;
      if (y)
	*y = rect.top;
      if (width)
	*width = rect.right - rect.left;
      if (height)
	*height = rect.bottom - rect.top;
      if (depth)
	*depth = gdk_drawable_get_visual (window)->depth;

      GDK_NOTE (MISC, g_print ("gdk_window_get_geometry: %p: %ldx%ldx%d@+%ld+%ld\n",
			       GDK_WINDOW_HWND (window),
			       rect.right - rect.left, rect.bottom - rect.top,
			       gdk_drawable_get_visual (window)->depth,
			       rect.left, rect.top));
    }
}

gint
gdk_window_get_origin (GdkWindow *window,
		       gint      *x,
		       gint      *y)
{
  gint return_val;
  gint tx = 0;
  gint ty = 0;

  g_return_val_if_fail (window != NULL, 0);

  if (!GDK_WINDOW_DESTROYED (window))
    {
      POINT pt;

      pt.x = 0;
      pt.y = 0;
      ClientToScreen (GDK_WINDOW_HWND (window), &pt);
      tx = pt.x;
      ty = pt.y;
      return_val = 1;
    }
  else
    return_val = 0;
  
  if (x)
    *x = tx + _gdk_offset_x;
  if (y)
    *y = ty + _gdk_offset_y;

  GDK_NOTE (MISC, g_print ("gdk_window_get_origin: %p: +%d+%d\n",
			   GDK_WINDOW_HWND (window),
			   tx, ty));
  return return_val;
}

gboolean
gdk_window_get_deskrelative_origin (GdkWindow *window,
				    gint      *x,
				    gint      *y)
{
  return gdk_window_get_origin (window, x, y);
}

void
gdk_window_get_root_origin (GdkWindow *window,
			    gint      *x,
			    gint      *y)
{
  GdkRectangle rect;

  g_return_if_fail (GDK_IS_WINDOW (window));

  gdk_window_get_frame_extents (window, &rect);

  if (x)
    *x = rect.x;

  if (y)
    *y = rect.y;

  GDK_NOTE (MISC, g_print ("gdk_window_get_root_origin: %p: +%d+%d\n",
			   GDK_WINDOW_HWND (window), rect.x, rect.y));
}

void
gdk_window_get_frame_extents (GdkWindow    *window,
                              GdkRectangle *rect)
{
  GdkWindowObject *private;
  HWND hwnd;
  RECT r;

  g_return_if_fail (GDK_IS_WINDOW (window));
  g_return_if_fail (rect != NULL);

  private = GDK_WINDOW_OBJECT (window);

  rect->x = 0;
  rect->y = 0;
  rect->width = 1;
  rect->height = 1;
  
  if (GDK_WINDOW_DESTROYED (window))
    return;

  /* FIXME: window is documented to be a toplevel GdkWindow, so is it really
   * necessary to walk its parent chain?
   */
  while (private->parent && ((GdkWindowObject*) private->parent)->parent)
    private = (GdkWindowObject*) private->parent;

  hwnd = GDK_WINDOW_HWND (window);

  /* find the frame window */
  while (HWND_DESKTOP != GetParent (hwnd))
    {
      hwnd = GetParent (hwnd);
      g_return_if_fail (NULL != hwnd);
    }

  API_CALL (GetWindowRect, (hwnd, &r));

  rect->x = r.left + _gdk_offset_x;
  rect->y = r.top + _gdk_offset_y;
  rect->width = r.right - r.left;
  rect->height = r.bottom - r.top;

  GDK_NOTE (MISC, g_print ("gdk_window_get_frame_extents: %p: %ldx%ld@+%ld+%ld\n",
			   GDK_WINDOW_HWND (window),
			   r.right - r.left, r.bottom - r.top,
			   r.left, r.top));
}

GdkWindow*
_gdk_windowing_window_get_pointer (GdkDisplay      *display,
				   GdkWindow       *window,
				   gint            *x,
				   gint            *y,
				   GdkModifierType *mask)
{
  GdkWindow *return_val;
  POINT screen_point, point;
  HWND hwnd, hwndc;
  BYTE kbd[256];

  g_return_val_if_fail (window == NULL || GDK_IS_WINDOW (window), NULL);
  
  return_val = NULL;
  GetCursorPos (&screen_point);
  point = screen_point;
  ScreenToClient (GDK_WINDOW_HWND (window), &point);

  *x = point.x;
  *y = point.y;

  if (window == _gdk_parent_root)
    {
      *x += _gdk_offset_x;
      *y += _gdk_offset_y;
    }

  hwnd = WindowFromPoint (screen_point);
  if (hwnd != NULL)
    {
      gboolean done = FALSE;
      
      while (!done)
	{
	  point = screen_point;
	  ScreenToClient (hwnd, &point);
	  hwndc = ChildWindowFromPoint (hwnd, point);
	  if (hwndc == NULL)
	    done = TRUE;
	  else if (hwndc == hwnd)
	    done = TRUE;
	  else
	    hwnd = hwndc;
	}
      
      return_val = gdk_window_lookup ((GdkNativeWindow) hwnd);
    }
  else
    return_val = NULL;
      
  GetKeyboardState (kbd);
  *mask = 0;
  if (kbd[VK_SHIFT] & 0x80)
    *mask |= GDK_SHIFT_MASK;
  if (kbd[VK_CAPITAL] & 0x80)
    *mask |= GDK_LOCK_MASK;
  if (kbd[VK_CONTROL] & 0x80)
    *mask |= GDK_CONTROL_MASK;
  if (kbd[VK_MENU] & 0x80)
    *mask |= GDK_MOD1_MASK;
  if (kbd[VK_LBUTTON] & 0x80)
    *mask |= GDK_BUTTON1_MASK;
  if (kbd[VK_MBUTTON] & 0x80)
    *mask |= GDK_BUTTON2_MASK;
  if (kbd[VK_RBUTTON] & 0x80)
    *mask |= GDK_BUTTON3_MASK;
  
  return return_val;
}

void
_gdk_windowing_get_pointer (GdkDisplay       *display,
			    GdkScreen       **screen,
			    gint             *x,
			    gint             *y,
			    GdkModifierType  *mask)
{
  GdkScreen *default_screen = gdk_display_get_default_screen (display);
  GdkWindow *root_window = gdk_screen_get_root_window (default_screen);
  
  *screen = default_screen;
  _gdk_windowing_window_get_pointer (display, root_window, x, y, mask);
}

GdkWindow*
_gdk_windowing_window_at_pointer (GdkDisplay *display,
				  gint       *win_x,
				  gint       *win_y)
{
  GdkWindow *window;
  POINT point, pointc;
  HWND hwnd, hwndc;
  RECT rect;

  GetCursorPos (&pointc);
  point = pointc;
  hwnd = WindowFromPoint (point);

  if (hwnd == NULL)
    {
      window = _gdk_parent_root;
      *win_x = pointc.x + _gdk_offset_x;
      *win_y = pointc.y + _gdk_offset_y;
      return window;
    }
      
  ScreenToClient (hwnd, &point);

  do {
    hwndc = ChildWindowFromPoint (hwnd, point);
    ClientToScreen (hwnd, &point);
    ScreenToClient (hwndc, &point);
  } while (hwndc != hwnd && (hwnd = hwndc, 1));

  window = gdk_win32_handle_table_lookup ((GdkNativeWindow) hwnd);

  if (window && (win_x || win_y))
    {
      GetClientRect (hwnd, &rect);
      *win_x = point.x - rect.left;
      *win_y = point.y - rect.top;
    }

  GDK_NOTE (MISC, g_print ("_gdk_windowing_window_at_pointer: +%d+%d %p%s\n",
			   *win_x, *win_y,
			   hwnd,
			   (window == NULL ? " NULL" : "")));

  return window;
}

GdkEventMask  
gdk_window_get_events (GdkWindow *window)
{
  g_return_val_if_fail (window != NULL, 0);
  g_return_val_if_fail (GDK_IS_WINDOW (window), 0);

  if (GDK_WINDOW_DESTROYED (window))
    return 0;

  return GDK_WINDOW_OBJECT (window)->event_mask;
}

void          
gdk_window_set_events (GdkWindow   *window,
		       GdkEventMask event_mask)
{
  g_return_if_fail (window != NULL);
  g_return_if_fail (GDK_IS_WINDOW (window));

  if (GDK_WINDOW_DESTROYED (window))
    return;

  /* gdk_window_new() always sets the GDK_STRUCTURE_MASK, so better
   * set it here, too. Not that I know or remember why it is
   * necessary, will have to test some day.
   */
  GDK_WINDOW_OBJECT (window)->event_mask = GDK_STRUCTURE_MASK | event_mask;
}

void
gdk_window_shape_combine_mask (GdkWindow *window,
			       GdkBitmap *mask,
			       gint x, gint y)
{
  g_return_if_fail (window != NULL);
  g_return_if_fail (GDK_IS_WINDOW (window));

  if (!mask)
    {
      GDK_NOTE (MISC, g_print ("gdk_window_shape_combine_mask: %p: none\n",
			       GDK_WINDOW_HWND (window)));
      SetWindowRgn (GDK_WINDOW_HWND (window), NULL, TRUE);
    }
  else
    {
      HRGN hrgn;
      RECT rect;

      /* Convert mask bitmap to region */
      hrgn = _gdk_win32_bitmap_to_hrgn (mask);

      GDK_NOTE (MISC, g_print ("gdk_window_shape_combine_mask: %p: %p\n",
			       GDK_WINDOW_HWND (window),
			       GDK_WINDOW_HWND (mask)));

      _gdk_win32_get_adjusted_client_rect (window, &rect);

      OffsetRgn (hrgn, -rect.left, -rect.top);
      OffsetRgn (hrgn, x, y);

      /* If this is a top-level window, add the title bar to the region */
      if (GDK_WINDOW_TYPE (window) == GDK_WINDOW_TOPLEVEL)
	{
	  HRGN tmp = CreateRectRgn (0, 0, rect.right - rect.left, -rect.top);
	  CombineRgn (hrgn, hrgn, tmp, RGN_OR);
	  DeleteObject (tmp);
	}
      
      SetWindowRgn (GDK_WINDOW_HWND (window), hrgn, TRUE);
    }
}

void
gdk_window_set_override_redirect (GdkWindow *window,
				  gboolean   override_redirect)
{
  g_return_if_fail (window != NULL);
  g_return_if_fail (GDK_IS_WINDOW (window));

  g_warning ("gdk_window_set_override_redirect not implemented");
}

void
gdk_window_set_accept_focus (GdkWindow *window,
			     gboolean accept_focus)
{
  GdkWindowObject *private;
  g_return_if_fail (window != NULL);
  g_return_if_fail (GDK_IS_WINDOW (window));

  private = (GdkWindowObject *)window;  
  
  accept_focus = accept_focus != FALSE;

  if (private->accept_focus != accept_focus)
    private->accept_focus = accept_focus;
}

static HICON
pixbuf_to_hicon_alpha_winxp (GdkWindow *window,
			     GdkPixbuf *pixbuf)
{
  /* Based on code from
   * http://www.dotnet247.com/247reference/msgs/13/66301.aspx
   */
  HDC hdc;
  BITMAPV5HEADER bi;
  HBITMAP hBitmap, hMonoBitmap;
  guchar *indata, *inrow;
  guchar *outdata, *outrow;
  HICON hAlphaIcon = NULL;
  ICONINFO ii;
  gint width, height, i, j, rowstride;

  if (pixbuf == NULL)
    return NULL;

  width = gdk_pixbuf_get_width (pixbuf); /* width of icon */
  height = gdk_pixbuf_get_height (pixbuf); /* height of icon */

  ZeroMemory (&bi, sizeof (BITMAPV5HEADER));
  bi.bV5Size = sizeof (BITMAPV5HEADER);
  bi.bV5Width = width;
  bi.bV5Height = height;
  bi.bV5Planes = 1;
  bi.bV5BitCount = 32;
  bi.bV5Compression = BI_BITFIELDS;
  /* The following mask specification specifies a supported 32 BPP
   * alpha format for Windows XP (BGRA format).
   */
  bi.bV5RedMask   = 0x00FF0000;
  bi.bV5GreenMask = 0x0000FF00;
  bi.bV5BlueMask  = 0x000000FF;
  bi.bV5AlphaMask = 0xFF000000;

  /* Create the DIB section with an alpha channel. */
  hdc = GetDC (NULL);
  hBitmap = CreateDIBSection (hdc, (BITMAPINFO *)&bi, DIB_RGB_COLORS,
			      (void **)&outdata, NULL, (DWORD)0);
  ReleaseDC (NULL, hdc);

  /* Draw something on the DIB section */
  indata = gdk_pixbuf_get_pixels (pixbuf);
  rowstride = gdk_pixbuf_get_rowstride (pixbuf);
  for (j=0; j<height; j++)
    {
      outrow = outdata + 4*j*width;
      inrow  = indata  + (height-j-1)*rowstride;
      for (i=0; i<width; i++)
	{
	  outrow[4*i+0] = inrow[4*i+2];
	  outrow[4*i+1] = inrow[4*i+1];
	  outrow[4*i+2] = inrow[4*i+0];
	  outrow[4*i+3] = inrow[4*i+3];
	}
    }

  /* Create an empty mask bitmap */
  hMonoBitmap = CreateBitmap (width, height, 1, 1, NULL);

  ii.fIcon = TRUE;
  ii.xHotspot = 0;
  ii.yHotspot = 0;
  ii.hbmMask = hMonoBitmap;
  ii.hbmColor = hBitmap;

  /* Create the alpha cursor with the alpha DIB section */
  hAlphaIcon = CreateIconIndirect (&ii);

  GDI_CALL (DeleteObject, (hBitmap));
  GDI_CALL (DeleteObject, (hMonoBitmap));

  return hAlphaIcon;
}

static HICON
pixbuf_to_hicon_normal (GdkWindow *window,
			GdkPixbuf *pixbuf)
{
  GdkPixmap *pixmap;
  GdkBitmap *mask;
  HBITMAP hbmmask = NULL;
  ICONINFO ii;
  HICON hIcon;
  gint w = 0, h = 0;

  if (pixbuf == NULL)
    return NULL;

  /* create a normal icon with a bitmap mask */
  w = gdk_pixbuf_get_width (pixbuf);
  h = gdk_pixbuf_get_height (pixbuf);
  gdk_pixbuf_render_pixmap_and_mask_for_colormap (pixbuf, 
						  gdk_drawable_get_colormap (window),
						  &pixmap,
						  &mask,
						  128);

  /* we need the inverted mask for the XOR op */
  {
    HDC hdc1 = CreateCompatibleDC (NULL);
    HBITMAP hbmold1;

    hbmmask = CreateCompatibleBitmap (hdc1, w, h);
    hbmold1 = SelectObject (hdc1, hbmmask);
    if (mask)
      {
	HDC hdc2 = CreateCompatibleDC (NULL);
	HBITMAP hbmold2 = SelectObject (hdc2, GDK_PIXMAP_HBITMAP (mask));
	GDI_CALL (BitBlt, (hdc1, 0,0,w,h, hdc2, 0,0, NOTSRCCOPY));
	GDI_CALL (SelectObject, (hdc2, hbmold2));
	GDI_CALL (DeleteDC, (hdc2));
      }
    else
      {
	RECT rect;
	GetClipBox (hdc1, &rect);
	GDI_CALL (FillRect, (hdc1, &rect, GetStockObject (BLACK_BRUSH)));
      }
    GDI_CALL (SelectObject, (hdc1, hbmold1));
    GDI_CALL (DeleteDC, (hdc1));
  }

  ii.fIcon = TRUE;
  ii.xHotspot = ii.yHotspot = 0; /* ignored for icons */
  ii.hbmMask = hbmmask;
  ii.hbmColor = GDK_PIXMAP_HBITMAP (pixmap);
  hIcon = CreateIconIndirect (&ii);
  if (!hIcon)
    WIN32_API_FAILED ("CreateIconIndirect");
  GDI_CALL (DeleteObject, (hbmmask));

#if 0 /* to debug pixmap and mask setting */
  {
    static int num = 0;
    GdkPixbuf* pixbuf = NULL;
    char name[256];

    pixbuf = gdk_pixbuf_get_from_drawable (NULL, pixmap, NULL, 0, 0, 0, 0, w, h);
    if (pixbuf)
      {
	num = (num + 1) % 999; /* restrict maximim number */
	sprintf (name, "c:\\temp\\ico%03dpixm.png", num); 
	gdk_pixbuf_save (pixbuf, name, "png", NULL, NULL);
	gdk_pixbuf_unref (pixbuf);
      }
  }
#endif

  if (pixmap)
    g_object_unref (G_OBJECT (pixmap));
  if (mask)
    g_object_unref (G_OBJECT (mask));

  return hIcon;
}

static HICON
pixbuf_to_hicon (GdkWindow *window,
		 GdkPixbuf *pixbuf)
{
  static gboolean is_win_xp=FALSE, is_win_xp_checked=FALSE;

  if (!is_win_xp_checked)
    {
      OSVERSIONINFO version;

      is_win_xp_checked = TRUE;
      memset (&version, 0, sizeof (version));
      version.dwOSVersionInfoSize = sizeof (version);
      is_win_xp = GetVersionEx (&version)
	&& version.dwPlatformId == VER_PLATFORM_WIN32_NT
	&& (version.dwMajorVersion > 5
	    || (version.dwMajorVersion == 5 && version.dwMinorVersion >= 1));
    }

  if (pixbuf == NULL)
    return NULL;

  if (is_win_xp && gdk_pixbuf_get_has_alpha (pixbuf))
    return pixbuf_to_hicon_alpha_winxp (window, pixbuf);
  else
    return pixbuf_to_hicon_normal (window, pixbuf);
}

void          
gdk_window_set_icon_list (GdkWindow *window,
			  GList     *pixbufs)
{
  GdkPixbuf *pixbuf, *big_pixbuf, *small_pixbuf;
  gint big_diff, small_diff;
  gint big_w, big_h, small_w, small_h;
  gint w, h;
  gint dw, dh, diff;
  HICON small_hicon, big_hicon;
  GdkWindowImplWin32 *impl;
  gint i, big_i, small_i;

  g_return_if_fail (GDK_IS_WINDOW (window));

  if (GDK_WINDOW_DESTROYED (window))
    return;

  impl = GDK_WINDOW_IMPL_WIN32 (GDK_WINDOW_OBJECT (window)->impl);

  /* ideal sizes for small and large icons */
  big_w = GetSystemMetrics (SM_CXICON);
  big_h = GetSystemMetrics (SM_CYICON);
  small_w = GetSystemMetrics (SM_CXSMICON);
  small_h = GetSystemMetrics (SM_CYSMICON);

  /* find closest sized icons in the list */
  big_pixbuf = NULL;
  small_pixbuf = NULL;
  big_diff = 0;
  small_diff = 0;
  i = 0;
  while (pixbufs)
    {
      pixbuf = (GdkPixbuf*) pixbufs->data;
      w = gdk_pixbuf_get_width (pixbuf);
      h = gdk_pixbuf_get_height (pixbuf);

      dw = ABS (w - big_w);
      dh = ABS (h - big_h);
      diff = dw*dw + dh*dh;
      if (big_pixbuf == NULL || diff < big_diff)
	{
	  big_pixbuf = pixbuf;
	  big_diff = diff;
	  big_i = i;
	}

      dw = ABS(w - small_w);
      dh = ABS(h - small_h);
      diff = dw*dw + dh*dh;
      if (small_pixbuf == NULL || diff < small_diff)
	{
	  small_pixbuf = pixbuf;
	  small_diff = diff;
	  small_i = i;
	}

      pixbufs = g_list_next (pixbufs);
      i++;
    }

  /* Create the icons */
  big_hicon = pixbuf_to_hicon (window, big_pixbuf);
  small_hicon = pixbuf_to_hicon (window, small_pixbuf);

  /* Set the icons */
  SendMessage (GDK_WINDOW_HWND (window), WM_SETICON, ICON_BIG,
	       (LPARAM)big_hicon);
  SendMessage (GDK_WINDOW_HWND (window), WM_SETICON, ICON_SMALL,
  	       (LPARAM)small_hicon);

  /* Store the icons, destroying any previous icons */
  if (impl->hicon_big)
    GDI_CALL (DestroyIcon, (impl->hicon_big));
  impl->hicon_big = big_hicon;
  if (impl->hicon_small)
    GDI_CALL (DestroyIcon, (impl->hicon_small));
  impl->hicon_small = small_hicon;
}

void          
gdk_window_set_icon (GdkWindow *window, 
		     GdkWindow *icon_window,
		     GdkPixmap *pixmap,
		     GdkBitmap *mask)
{
  g_return_if_fail (window != NULL);
  g_return_if_fail (GDK_IS_WINDOW (window));

  /* do nothing, use gdk_window_set_icon_list instead */
}

void
gdk_window_set_icon_name (GdkWindow   *window, 
			  const gchar *name)
{
  g_return_if_fail (window != NULL);
  g_return_if_fail (GDK_IS_WINDOW (window));

  if (GDK_WINDOW_DESTROYED (window))
    return;
  
  API_CALL (SetWindowText, (GDK_WINDOW_HWND (window), name));
}

GdkWindow *
gdk_window_get_group (GdkWindow *window)
{
  g_return_val_if_fail (GDK_IS_WINDOW (window), NULL);
  g_return_val_if_fail (GDK_WINDOW_TYPE (window) != GDK_WINDOW_CHILD, NULL);

  if (GDK_WINDOW_DESTROYED (window))
    return NULL;
  
  g_warning ("gdk_window_get_group not yet implemented");

  return NULL;
}

void          
gdk_window_set_group (GdkWindow *window, 
		      GdkWindow *leader)
{
  g_return_if_fail (window != NULL);
  g_return_if_fail (GDK_IS_WINDOW (window));
  g_return_if_fail (leader != NULL);
  g_return_if_fail (GDK_IS_WINDOW (leader));

  if (GDK_WINDOW_DESTROYED (window) || GDK_WINDOW_DESTROYED (leader))
    return;
  
  g_warning ("gdk_window_set_group not implemented");
}

void
gdk_window_set_decorations (GdkWindow      *window,
			    GdkWMDecoration decorations)
{
  LONG style, bits;
  const LONG settable_bits = WS_BORDER|WS_THICKFRAME|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX|WS_MAXIMIZEBOX;

  g_return_if_fail (window != NULL);
  g_return_if_fail (GDK_IS_WINDOW (window));
  
  GDK_NOTE (MISC, g_print ("gdk_window_set_decorations: %p: %s%s%s%s%s%s%s\n",
			   GDK_WINDOW_HWND (window),
			   (decorations & GDK_DECOR_ALL ? "ALL " : ""),
			   (decorations & GDK_DECOR_BORDER ? "BORDER " : ""),
			   (decorations & GDK_DECOR_RESIZEH ? "RESIZEH " : ""),
			   (decorations & GDK_DECOR_TITLE ? "TITLE " : ""),
			   (decorations & GDK_DECOR_MENU ? "MENU " : ""),
			   (decorations & GDK_DECOR_MINIMIZE ? "MINIMIZE " : ""),
			   (decorations & GDK_DECOR_MAXIMIZE ? "MAXIMIZE " : "")));

  style = GetWindowLong (GDK_WINDOW_HWND (window), GWL_STYLE);

  bits = 0;

  if (decorations & GDK_DECOR_BORDER)
    bits |= WS_BORDER;
  if (decorations & GDK_DECOR_RESIZEH)
    bits |= WS_THICKFRAME;
  if (decorations & GDK_DECOR_TITLE)
    bits |= WS_CAPTION;
  if (decorations & GDK_DECOR_MENU)
    bits |= WS_SYSMENU;
  if (decorations & GDK_DECOR_MINIMIZE)
    bits |= WS_MINIMIZEBOX;
  if (decorations & GDK_DECOR_MAXIMIZE)
    bits |= WS_MAXIMIZEBOX;

  if (decorations & GDK_DECOR_ALL)
    style |= settable_bits, style &= ~bits;
  else
    style &= ~settable_bits, style |= bits;
  
  SetWindowLong (GDK_WINDOW_HWND (window), GWL_STYLE, style);
  SetWindowPos (GDK_WINDOW_HWND (window), NULL, 0, 0, 0, 0,
		SWP_FRAMECHANGED | SWP_NOACTIVATE | SWP_NOMOVE |
		SWP_NOREPOSITION | SWP_NOSIZE | SWP_NOZORDER);
}

gboolean
gdk_window_get_decorations(GdkWindow       *window,
			   GdkWMDecoration *decorations)
{
  LONG style = GetWindowLong (GDK_WINDOW_HWND (window), GWL_STYLE);

  *decorations = 0;

  if (style & WS_BORDER)
    *decorations |= GDK_DECOR_BORDER;
  if (style & WS_THICKFRAME)
    *decorations |= GDK_DECOR_RESIZEH;
  if (style & WS_CAPTION)
    *decorations |= GDK_DECOR_TITLE;
  if (style & WS_SYSMENU)
    *decorations |= GDK_DECOR_MENU;
  if (style & WS_MINIMIZEBOX)
    *decorations |= GDK_DECOR_MINIMIZE;
  if (style & WS_MAXIMIZEBOX)
    *decorations |= GDK_DECOR_MAXIMIZE;

  return *decorations != 0;
}

void
gdk_window_set_functions (GdkWindow    *window,
			  GdkWMFunction functions)
{
  LONG style, bits;
  const LONG settable_bits = (WS_THICKFRAME|WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_SYSMENU);

  g_return_if_fail (window != NULL);
  g_return_if_fail (GDK_IS_WINDOW (window));
  
  GDK_NOTE (MISC, g_print ("gdk_window_set_functions: %p: %s%s%s%s%s%s\n",
			   GDK_WINDOW_HWND (window),
			   (functions & GDK_FUNC_ALL ? "ALL " : ""),
			   (functions & GDK_FUNC_RESIZE ? "RESIZE " : ""),
			   (functions & GDK_FUNC_MOVE ? "MOVE " : ""),
			   (functions & GDK_FUNC_MINIMIZE ? "MINIMIZE " : ""),
			   (functions & GDK_FUNC_MAXIMIZE ? "MAXIMIZE " : ""),
			   (functions & GDK_FUNC_CLOSE ? "CLOSE " : "")));

  style = GetWindowLong (GDK_WINDOW_HWND (window), GWL_STYLE);

  bits = 0;

  if (functions & GDK_FUNC_RESIZE)
    bits |= WS_THICKFRAME;
  if (functions & GDK_FUNC_MOVE)
    bits |= (WS_THICKFRAME|WS_SYSMENU);
  if (functions & GDK_FUNC_MINIMIZE)
    bits |= WS_MINIMIZEBOX;
  if (functions & GDK_FUNC_MAXIMIZE)
    bits |= WS_MAXIMIZEBOX;
  if (functions & GDK_FUNC_CLOSE)
    bits |= WS_SYSMENU;
  
  if (functions & GDK_FUNC_ALL)
    style |= settable_bits, style &= ~bits;
  else
    style &= ~settable_bits, style |= bits;
  
  SetWindowLong (GDK_WINDOW_HWND (window), GWL_STYLE, style);
  SetWindowPos (GDK_WINDOW_HWND (window), NULL, 0, 0, 0, 0,
		SWP_FRAMECHANGED | SWP_NOACTIVATE | SWP_NOMOVE |
		SWP_NOREPOSITION | SWP_NOSIZE | SWP_NOZORDER);
}

static void
QueryTree (HWND   hwnd,
	   HWND **children,
	   gint  *nchildren)
{
  guint i, n;
  HWND child;

  n = 0;
  do {
    if (n == 0)
      child = GetWindow (hwnd, GW_CHILD);
    else
      child = GetWindow (child, GW_HWNDNEXT);
    if (child != NULL)
      n++;
  } while (child != NULL);

  if (n > 0)
    {
      *children = g_new (HWND, n);
      for (i = 0; i < n; i++)
	{
	  if (i == 0)
	    child = GetWindow (hwnd, GW_CHILD);
	  else
	    child = GetWindow (child, GW_HWNDNEXT);
	  *children[i] = child;
	}
    }
}

static void
gdk_propagate_shapes (HANDLE   win,
		      gboolean merge)
{
   RECT emptyRect;
   HRGN region, childRegion;
   HWND *list = NULL;
   gint i, num;

   SetRectEmpty (&emptyRect);
   region = CreateRectRgnIndirect (&emptyRect);
   if (merge)
     GetWindowRgn (win, region);
   
   QueryTree (win, &list, &num);
   if (list != NULL)
     {
       WINDOWPLACEMENT placement;

       placement.length = sizeof (WINDOWPLACEMENT);
       /* go through all child windows and combine regions */
       for (i = 0; i < num; i++)
	 {
	   GetWindowPlacement (list[i], &placement);
	   if (placement.showCmd == SW_SHOWNORMAL)
	     {
	       childRegion = CreateRectRgnIndirect (&emptyRect);
	       GetWindowRgn (list[i], childRegion);
	       CombineRgn (region, region, childRegion, RGN_OR);
	       DeleteObject (childRegion);
	     }
	  }
       SetWindowRgn (win, region, TRUE);
       g_free (list);
     }
   else
     DeleteObject (region);
}

void
gdk_window_set_child_shapes (GdkWindow *window)
{
  g_return_if_fail (window != NULL);
  g_return_if_fail (GDK_IS_WINDOW (window));
   
  if (GDK_WINDOW_DESTROYED (window))
    return;

  gdk_propagate_shapes (GDK_WINDOW_HWND (window), FALSE);
}

void
gdk_window_merge_child_shapes (GdkWindow *window)
{
  g_return_if_fail (window != NULL);
  g_return_if_fail (GDK_IS_WINDOW (window));
  
  if (GDK_WINDOW_DESTROYED (window))
    return;

  gdk_propagate_shapes (GDK_WINDOW_HWND (window), TRUE);
}

gboolean 
gdk_window_set_static_gravities (GdkWindow *window,
				 gboolean   use_static)
{
  GdkWindowObject *private = (GdkWindowObject *)window;
  
  g_return_val_if_fail (window != NULL, FALSE);
  g_return_val_if_fail (GDK_IS_WINDOW (window), FALSE);

  if (!use_static == !private->guffaw_gravity)
    return TRUE;
  
  if (use_static)
    return FALSE;
  
  private->guffaw_gravity = use_static;
  
  return TRUE;
}

/*
 * Setting window states
 */
void
gdk_window_iconify (GdkWindow *window)
{
  HWND old_active_window;

  g_return_if_fail (window != NULL);
  g_return_if_fail (GDK_IS_WINDOW (window));

  if (GDK_WINDOW_DESTROYED (window))
    return;

  GDK_NOTE (MISC, g_print ("gdk_window_iconify: %p: %s\n",
			   GDK_WINDOW_HWND (window),
			   _gdk_win32_window_state_to_string (((GdkWindowObject *) window)->state)));

  if (GDK_WINDOW_IS_MAPPED (window))
    {
      old_active_window = GetActiveWindow ();
      ShowWindow (GDK_WINDOW_HWND (window), SW_MINIMIZE);
      if (old_active_window != GDK_WINDOW_HWND (window))
	SetActiveWindow (old_active_window);
    }
  else
    {
      gdk_synthesize_window_state (window,
                                   0,
                                   GDK_WINDOW_STATE_ICONIFIED);
    }
}

void
gdk_window_deiconify (GdkWindow *window)
{
  g_return_if_fail (window != NULL);
  g_return_if_fail (GDK_IS_WINDOW (window));

  if (GDK_WINDOW_DESTROYED (window))
    return;

  GDK_NOTE (MISC, g_print ("gdk_window_deiconify: %p: %s\n",
			   GDK_WINDOW_HWND (window),
			   _gdk_win32_window_state_to_string (((GdkWindowObject *) window)->state)));

  if (GDK_WINDOW_IS_MAPPED (window))
    {  
      show_window_internal (window, FALSE, TRUE);
    }
  else
    {
      gdk_synthesize_window_state (window,
                                   GDK_WINDOW_STATE_ICONIFIED,
                                   0);
    }
}

void
gdk_window_stick (GdkWindow *window)
{
  g_return_if_fail (GDK_IS_WINDOW (window));

  if (GDK_WINDOW_DESTROYED (window))
    return;

  /* FIXME: Do something? */
}

void
gdk_window_unstick (GdkWindow *window)
{
  g_return_if_fail (GDK_IS_WINDOW (window));

  if (GDK_WINDOW_DESTROYED (window))
    return;

  /* FIXME: Do something? */
}

void
gdk_window_maximize (GdkWindow *window)
{
  g_return_if_fail (GDK_IS_WINDOW (window));

  if (GDK_WINDOW_DESTROYED (window))
    return;

  GDK_NOTE (MISC, g_print ("gdk_window_maximize: %p: %s\n",
			   GDK_WINDOW_HWND (window),
			   _gdk_win32_window_state_to_string (((GdkWindowObject *) window)->state)));

  if (GDK_WINDOW_IS_MAPPED (window))
    ShowWindow (GDK_WINDOW_HWND (window), SW_MAXIMIZE);
  else
    gdk_synthesize_window_state (window,
				 0,
				 GDK_WINDOW_STATE_MAXIMIZED);
}

void
gdk_window_unmaximize (GdkWindow *window)
{
  g_return_if_fail (GDK_IS_WINDOW (window));

  if (GDK_WINDOW_DESTROYED (window))
    return;

  GDK_NOTE (MISC, g_print ("gdk_window_unmaximize: %p: %s\n",
			   GDK_WINDOW_HWND (window),
			   _gdk_win32_window_state_to_string (((GdkWindowObject *) window)->state)));

  if (GDK_WINDOW_IS_MAPPED (window))
    ShowWindow (GDK_WINDOW_HWND (window), SW_RESTORE);
  else
    gdk_synthesize_window_state (window,
				 GDK_WINDOW_STATE_MAXIMIZED,
				 0);
}

typedef struct _FullscreenInfo FullscreenInfo;

struct _FullscreenInfo
{
  RECT  r;
  guint hint_flags;
  LONG  style;
};

void
gdk_window_fullscreen (GdkWindow *window)
{
  gint width, height;
  FullscreenInfo *fi;
  GdkWindowObject *private = (GdkWindowObject *) window;

  g_return_if_fail (GDK_IS_WINDOW (window));

  fi = g_new (FullscreenInfo, 1);

  if (!GetWindowRect (GDK_WINDOW_HWND (window), &(fi->r)))
    g_free (fi);
  else
    {
      GdkWindowImplWin32 *impl = GDK_WINDOW_IMPL_WIN32 (private->impl);

      width = GetSystemMetrics (SM_CXSCREEN);
      height = GetSystemMetrics (SM_CYSCREEN);
 
      /* remember for restoring */
      fi->hint_flags = impl->hint_flags;
      impl->hint_flags &= ~GDK_HINT_MAX_SIZE;
      g_object_set_data (G_OBJECT (window), "fullscreen-info", fi);
      fi->style = GetWindowLong (GDK_WINDOW_HWND (window), GWL_STYLE);

      SetWindowLong (GDK_WINDOW_HWND (window), GWL_STYLE, 
                     (fi->style & ~WS_OVERLAPPEDWINDOW) | WS_POPUP);
      if (!SetWindowPos (GDK_WINDOW_HWND (window), HWND_TOP /*not MOST, taskswitch!*/,
                         0, 0, width, height,
                         SWP_NOCOPYBITS | SWP_SHOWWINDOW))
        WIN32_API_FAILED ("SetWindowPos");

      gdk_synthesize_window_state (window, 0, GDK_WINDOW_STATE_FULLSCREEN);
    }
}

void
gdk_window_unfullscreen (GdkWindow *window)
{
  FullscreenInfo *fi;
  GdkWindowObject *private = (GdkWindowObject *) window;

  g_return_if_fail (GDK_IS_WINDOW (window));

  fi = g_object_get_data (G_OBJECT(window), "fullscreen-info");
  if (fi)
    {
      GdkWindowImplWin32 *impl = GDK_WINDOW_IMPL_WIN32 (private->impl);

      impl->hint_flags = fi->hint_flags;
      SetWindowLong (GDK_WINDOW_HWND (window), GWL_STYLE, fi->style);
      if (!SetWindowPos (GDK_WINDOW_HWND (window), HWND_NOTOPMOST,
                         fi->r.left, fi->r.top, fi->r.right - fi->r.left, fi->r.bottom - fi->r.top,
                         SWP_NOCOPYBITS | SWP_SHOWWINDOW))
         WIN32_API_FAILED ("SetWindowPos");

      g_object_set_data (G_OBJECT (window), "fullscreen-info", NULL);
      g_free (fi);

      gdk_synthesize_window_state (window, GDK_WINDOW_STATE_FULLSCREEN, 0);
    }
}

void
gdk_window_set_keep_above (GdkWindow *window, gboolean setting)
{
  g_return_if_fail (GDK_IS_WINDOW (window));

  if (GDK_WINDOW_DESTROYED (window))
    return;

  if (GDK_WINDOW_IS_MAPPED (window))
    {
      if (!SetWindowPos(GDK_WINDOW_HWND (window), setting ? HWND_TOPMOST : HWND_NOTOPMOST,
                        0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE))
         WIN32_API_FAILED ("SetWindowPos");
    }
  else
    gdk_synthesize_window_state (window,
    				 setting ? GDK_WINDOW_STATE_BELOW : GDK_WINDOW_STATE_ABOVE,
				 setting ? GDK_WINDOW_STATE_ABOVE : 0);
}

void
gdk_window_set_keep_below (GdkWindow *window, gboolean setting)
{
  g_return_if_fail (GDK_IS_WINDOW (window));

  if (GDK_WINDOW_DESTROYED (window))
    return;

  if (GDK_WINDOW_IS_MAPPED (window))
    {
      if (!SetWindowPos(GDK_WINDOW_HWND (window), setting ? HWND_BOTTOM : HWND_NOTOPMOST,
                        0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE))
         WIN32_API_FAILED ("SetWindowPos");
    }
  else
    gdk_synthesize_window_state (window,
				 setting ? GDK_WINDOW_STATE_ABOVE : GDK_WINDOW_STATE_BELOW,
				 setting ? GDK_WINDOW_STATE_BELOW : 0);
}

void
gdk_window_focus (GdkWindow *window,
                  guint32    timestamp)
{
  g_return_if_fail (GDK_IS_WINDOW (window));

  if (GDK_WINDOW_DESTROYED (window))
    return;
  
  GDK_NOTE (MISC, g_print ("gdk_window_focus: %p: %s\n",
			   GDK_WINDOW_HWND (window),
			   _gdk_win32_window_state_to_string (((GdkWindowObject *) window)->state)));

  if (((GdkWindowObject *) window)->state & GDK_WINDOW_STATE_MAXIMIZED)
    ShowWindow (GDK_WINDOW_HWND (window), SW_SHOWMAXIMIZED);
  else
    ShowWindow (GDK_WINDOW_HWND (window), SW_SHOWNORMAL);
  SetFocus (GDK_WINDOW_HWND (window));
}

void
gdk_window_set_modal_hint (GdkWindow *window,
			   gboolean   modal)
{
  GdkWindowObject *private;

  g_return_if_fail (window != NULL);
  g_return_if_fail (GDK_IS_WINDOW (window));
  
  if (GDK_WINDOW_DESTROYED (window))
    return;

  private = (GdkWindowObject*) window;

  private->modal_hint = modal;

  if (GDK_WINDOW_IS_MAPPED (window))
    API_CALL (SetWindowPos, (GDK_WINDOW_HWND (window), 
			     modal ? HWND_TOPMOST : HWND_NOTOPMOST,
			     0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE));
}

void
gdk_window_set_skip_taskbar_hint (GdkWindow *window,
				  gboolean   skips_taskbar)
{
  static GdkWindow *owner = NULL;
  GdkWindowAttr wa;

  g_return_if_fail (GDK_IS_WINDOW (window));

  GDK_NOTE (MISC, g_print ("gdk_window_set_skip_taskbar_hint: %p: %s\n",
			   GDK_WINDOW_HWND (window),
			   skips_taskbar ? "TRUE" : "FALSE"));

  if (skips_taskbar)
    {
      if (owner == NULL)
	{
	  wa.window_type = GDK_WINDOW_TEMP;
	  wa.wclass = GDK_INPUT_OUTPUT;
	  wa.width = wa.height = 1;
	  wa.event_mask = 0;
	  owner = gdk_window_new (NULL, &wa, 0);
	}

      SetWindowLong (GDK_WINDOW_HWND (window), GWL_HWNDPARENT,
		     (long) GDK_WINDOW_HWND (owner));

#if 0 /* Should we also turn off the minimize and maximize buttons? */
      SetWindowLong (GDK_WINDOW_HWND (window), GWL_STYLE,
		     GetWindowLong (GDK_WINDOW_HWND (window), GWL_STYLE) & ~(WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_SYSMENU));
      SetWindowPos (GDK_WINDOW_HWND (window), NULL, 0, 0, 0, 0,
		    SWP_FRAMECHANGED | SWP_NOACTIVATE | SWP_NOMOVE |
		    SWP_NOREPOSITION | SWP_NOSIZE | SWP_NOZORDER);
#endif
    }
  else
    {
      SetWindowLong (GDK_WINDOW_HWND (window), GWL_HWNDPARENT, 0);
    }
}

void
gdk_window_set_skip_pager_hint (GdkWindow *window,
				gboolean   skips_pager)
{
  g_return_if_fail (GDK_IS_WINDOW (window));
}

void
gdk_window_set_type_hint (GdkWindow        *window,
			  GdkWindowTypeHint hint)
{
  g_return_if_fail (window != NULL);
  g_return_if_fail (GDK_IS_WINDOW (window));
  
  if (GDK_WINDOW_DESTROYED (window))
    return;

  GDK_NOTE (MISC, g_print ("gdk_window_set_type_hint: %p: %d\n",
			   GDK_WINDOW_HWND (window), hint));
  switch (hint)
    {
    case GDK_WINDOW_TYPE_HINT_DIALOG:
      break;
    case GDK_WINDOW_TYPE_HINT_MENU:
      gdk_window_set_decorations (window,
				  GDK_DECOR_ALL |
				  GDK_DECOR_RESIZEH |
				  GDK_DECOR_MINIMIZE |
				  GDK_DECOR_MAXIMIZE);
      break;
    case GDK_WINDOW_TYPE_HINT_TOOLBAR:
      gdk_window_set_skip_taskbar_hint (window, TRUE);
      break;
    case GDK_WINDOW_TYPE_HINT_UTILITY:
      break;
    case GDK_WINDOW_TYPE_HINT_SPLASHSCREEN:
      gdk_window_set_decorations (window,
				  GDK_DECOR_ALL |
				  GDK_DECOR_RESIZEH |
				  GDK_DECOR_MENU |
				  GDK_DECOR_MINIMIZE |
				  GDK_DECOR_MAXIMIZE);
      break;
    case GDK_WINDOW_TYPE_HINT_DOCK:
      break;
    case GDK_WINDOW_TYPE_HINT_DESKTOP:
      break;
    default:
      g_warning ("Unknown hint %d passed to gdk_window_set_type_hint", hint);
      /* Fall thru */
    case GDK_WINDOW_TYPE_HINT_NORMAL:
      break;
    }
}

void
gdk_window_shape_combine_region (GdkWindow *window,
                                 GdkRegion *shape_region,
                                 gint       offset_x,
                                 gint       offset_y)
{
  g_return_if_fail (GDK_IS_WINDOW (window));

  if (GDK_WINDOW_DESTROYED (window))
    return;

  /* XXX: even on X implemented conditional ... */  
}

void
gdk_window_begin_resize_drag (GdkWindow     *window,
                              GdkWindowEdge  edge,
                              gint           button,
                              gint           root_x,
                              gint           root_y,
                              guint32        timestamp)
{
  g_return_if_fail (GDK_IS_WINDOW (window));
  
  if (GDK_WINDOW_DESTROYED (window))
    return;

  /* XXX: isn't all this default on win32 ... */  
}

void
gdk_window_begin_move_drag (GdkWindow *window,
                            gint       button,
                            gint       root_x,
                            gint       root_y,
                            guint32    timestamp)
{
  g_return_if_fail (GDK_IS_WINDOW (window));
  
  if (GDK_WINDOW_DESTROYED (window))
    return;

  /* XXX: isn't all this default on win32 ... */  
}

GdkWindow *
gdk_window_lookup_for_display (GdkDisplay *display, GdkNativeWindow anid)
{
  g_return_val_if_fail (display == gdk_display_get_default(), NULL);

  return gdk_window_lookup (anid);
}
