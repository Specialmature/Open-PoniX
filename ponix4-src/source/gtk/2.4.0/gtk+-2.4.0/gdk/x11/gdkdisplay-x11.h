/*
 * gdkdisplay-x11.h
 * 
 * Copyright 2001 Sun Microsystems Inc. 
 *
 * Erwann Chenede <erwann.chenede@sun.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef __GDK_DISPLAY_X11__
#define __GDK_DISPLAY_X11__

#include <X11/X.h>
#include <X11/Xlib.h>
#include <glib.h>
#include <gdk/gdkdisplay.h>
#include <gdk/gdkkeys.h>
#include <gdk/gdkwindow.h>
#include <gdk/gdk.h>		/* For gdk_get_program_class() */

G_BEGIN_DECLS

typedef struct _GdkDisplayX11 GdkDisplayX11;
typedef struct _GdkDisplayX11Class GdkDisplayX11Class;

#define GDK_TYPE_DISPLAY_X11              (_gdk_display_x11_get_type())
#define GDK_DISPLAY_X11(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_DISPLAY_X11, GdkDisplayX11))
#define GDK_DISPLAY_X11_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GDK_TYPE_DISPLAY_X11, GdkDisplayX11Class))
#define GDK_IS_DISPLAY_X11(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_DISPLAY_X11))
#define GDK_IS_DISPLAY_X11_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GDK_TYPE_DISPLAY_X11))
#define GDK_DISPLAY_X11_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GDK_TYPE_DISPLAY_X11, GdkDisplayX11Class))

typedef enum 
{
  GDK_UNKNOWN,
  GDK_NO,
  GDK_YES
} GdkTristate;

struct _GdkDisplayX11
{
  GdkDisplay parent_instance;
  Display *xdisplay;
  GdkScreen *default_screen;
  GdkScreen **screens;

  GSource *event_source;

  gint grab_count;

  /* Keyboard related information */

  gint xkb_event_type;
  gboolean use_xkb;
  
  /* Whether we were able to turn on detectable-autorepeat using
   * XkbSetDetectableAutorepeat. If FALSE, we'll fall back
   * to checking the next event with XPending(). */
  gboolean have_xkb_autorepeat;

  GdkKeymap *keymap;
  guint	    keymap_serial;

  gboolean use_xshm;
  gboolean have_shm_pixmaps;
  GdkTristate have_render;
  
  /* Information about current pointer and keyboard grabs held by this
   * client. If gdk_pointer_xgrab_window or gdk_keyboard_xgrab_window
   * window is NULL, then the other associated fields are ignored
   */
  GdkWindowObject *pointer_xgrab_window;
  gulong pointer_xgrab_serial;
  gboolean pointer_xgrab_owner_events;

  GdkWindowObject *keyboard_xgrab_window;
  gulong keyboard_xgrab_serial;
  gboolean keyboard_xgrab_owner_events;

  /* drag and drop information */
  GdkDragContext *current_dest_drag;

  /* data needed for MOTIF DnD */

  Window motif_drag_window;
  GdkWindow *motif_drag_gdk_window;
  GList **motif_target_lists;
  gint motif_n_target_lists;

  /* Mapping to/from virtual atoms */

  GHashTable *atom_from_virtual;
  GHashTable *atom_to_virtual;

  /* Session Management leader window see ICCCM */
  Window leader_window;
  GdkWindow *leader_gdk_window;
  gboolean leader_window_title_set;
  
  /* list of filters for client messages */
  GList *client_filters;

  /* List of functions to go from extension event => X window */
  GSList *event_types;
  
  /* X ID hashtable */
  GHashTable *xid_ht;

  /* translation queue */
  GQueue *translate_queue;

  /* Input device */
  /* input GdkDevice list */
  GList *input_devices;

  /* input GdkWindow list */
  GList *input_windows;

  gint input_ignore_core;
  /* information about network port and host for gxid daemon */
  gchar *input_gxid_host;
  gint   input_gxid_port;

  /* Startup notification */
  gchar *startup_notification_id;

  /* Sets of atoms for DND */
  guint base_dnd_atoms_precached : 1;
  guint xdnd_atoms_precached : 1;
  guint motif_atoms_precached : 1;
};

struct _GdkDisplayX11Class
{
  GdkDisplayClass parent_class;
};

GType      _gdk_display_x11_get_type            (void);
GdkScreen *_gdk_x11_display_screen_for_xrootwin (GdkDisplay *display,
						 Window      xrootwin);

G_END_DECLS

#endif				/* __GDK_DISPLAY_X11__ */
