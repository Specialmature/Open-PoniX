/* GDK - The GIMP Drawing Kit
 * Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald
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
#include "gdkprivate-x11.h"
#include "gdkdisplay-x11.h"
#include <stdio.h>

static guint     gdk_xid_hash  (XID *xid);
static gboolean  gdk_xid_equal (XID *a,
				XID *b);


void
_gdk_xid_table_insert (GdkDisplay *display,
		       XID	  *xid,
		       gpointer    data)
{
  GdkDisplayX11 *display_x11;
  
  g_return_if_fail (xid != NULL);
  g_return_if_fail (GDK_IS_DISPLAY (display));
  
  display_x11 = GDK_DISPLAY_X11 (display);

  if (!display_x11->xid_ht)
    display_x11->xid_ht = g_hash_table_new ((GHashFunc) gdk_xid_hash,
					    (GEqualFunc) gdk_xid_equal);

  g_hash_table_insert (display_x11->xid_ht, xid, data);
}

void
_gdk_xid_table_remove (GdkDisplay *display,
		       XID	   xid)
{
  GdkDisplayX11 *display_x11;
  
  g_return_if_fail (GDK_IS_DISPLAY (display));
  
  display_x11 = GDK_DISPLAY_X11 (display);
  
  if (display_x11->xid_ht)
    g_hash_table_remove (display_x11->xid_ht, &xid);
}

/** 
 * gdk_xid_table_lookup_for_display:
 * @display: the #GdkDisplay.
 * @xid: an X id.
 *
 * Returns the GDK object associated with the given X id.
 *
 * Returns: a GDK object associated with the given X id.
 *
 * Since: 2.2
 */
gpointer
gdk_xid_table_lookup_for_display (GdkDisplay  *display,
				  XID	       xid)
{
  GdkDisplayX11 *display_x11;
  gpointer data = NULL;
  
  g_return_val_if_fail (GDK_IS_DISPLAY (display), NULL);
  
  display_x11 = GDK_DISPLAY_X11 (display);

  if (display_x11->xid_ht)
    data = g_hash_table_lookup (display_x11->xid_ht, &xid);
  
  return data;
}


/**
 * gdk_xid_table_lookup:
 * @xid: an X id.
 * 
 * Returns the Gdk object associated with the given X id.
 * 
 * Return value: the associated Gdk object, which may be a #GdkPixmap,
 * a #GdkWindow or a #GdkFont.
 **/
gpointer
gdk_xid_table_lookup (XID xid)
{
  return gdk_xid_table_lookup_for_display (gdk_display_get_default (), xid);
}

static guint
gdk_xid_hash (XID *xid)
{
  return *xid;
}

static gboolean
gdk_xid_equal (XID *a,
	       XID *b)
{
  return (*a == *b);
}
