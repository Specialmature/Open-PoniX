/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 8 -*- */
/* GdkPixbuf library - Private declarations
 *
 * Copyright (C) 1999 The Free Software Foundation
 *
 * Authors: Mark Crichton <crichton@gimp.org>
 *          Miguel de Icaza <miguel@gnu.org>
 *          Federico Mena-Quintero <federico@gimp.org>
 *          Havoc Pennington <hp@redhat.com>
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

#ifndef GDK_PIXBUF_PRIVATE_H
#define GDK_PIXBUF_PRIVATE_H

#include "gdk-pixbuf.h"
#include "gdk-pixbuf-io.h"
#include "gdk-pixbuf-i18n.h"
#include <stdio.h>



typedef struct _GdkPixbufClass GdkPixbufClass;

#define GDK_PIXBUF_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GDK_TYPE_PIXBUF, GdkPixbufClass))
#define GDK_IS_PIXBUF_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GDK_TYPE_PIXBUF))
#define GDK_PIXBUF_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GDK_TYPE_PIXBUF, GdkPixbufClass))

/* Private part of the GdkPixbuf structure */
struct _GdkPixbuf {
        GObject parent_instance;

	/* Color space */
	GdkColorspace colorspace;

	/* Number of channels, alpha included */
	int n_channels;

	/* Bits per channel */
	int bits_per_sample;

	/* Size */
	int width, height;

	/* Offset between rows */
	int rowstride;

	/* The pixel array */
	guchar *pixels;

	/* Destroy notification function; it is supposed to free the pixel array */
	GdkPixbufDestroyNotify destroy_fn;

	/* User data for the destroy notification function */
	gpointer destroy_fn_data;

	/* Do we have an alpha channel? */
	guint has_alpha : 1;
};

struct _GdkPixbufClass {
        GObjectClass parent_class;

};

#ifdef GDK_PIXBUF_ENABLE_BACKEND

gboolean _gdk_pixbuf_lock (GdkPixbufModule *image_module);
void _gdk_pixbuf_unlock (GdkPixbufModule *image_module);

GdkPixbufModule *_gdk_pixbuf_get_module (guchar *buffer, guint size,
                                         const gchar *filename,
                                         GError **error);
GdkPixbufModule *_gdk_pixbuf_get_named_module (const char *name,
                                               GError **error);
gboolean _gdk_pixbuf_load_module (GdkPixbufModule *image_module,
                                  GError **error);

GdkPixbuf *_gdk_pixbuf_generic_image_load (GdkPixbufModule *image_module,
					   FILE *f,
					   GError **error);

GdkPixbufFormat *_gdk_pixbuf_get_format (GdkPixbufModule *image_module);

#endif /* GDK_PIXBUF_ENABLE_BACKEND */

#endif /* GDK_PIXBUF_PRIVATE_H */


