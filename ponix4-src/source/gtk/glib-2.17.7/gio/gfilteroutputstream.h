/* GIO - GLib Input, Output and Streaming Library
 * 
 * Copyright (C) 2006-2007 Red Hat, Inc.
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
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * Author: Christian Kellner <gicmo@gnome.org> 
 */

#if !defined (__GIO_GIO_H_INSIDE__) && !defined (GIO_COMPILATION)
#error "Only <gio/gio.h> can be included directly."
#endif

#ifndef __G_FILTER_OUTPUT_STREAM_H__
#define __G_FILTER_OUTPUT_STREAM_H__

#include <gio/goutputstream.h>

G_BEGIN_DECLS

#define G_TYPE_FILTER_OUTPUT_STREAM         (g_filter_output_stream_get_type ())
#define G_FILTER_OUTPUT_STREAM(o)           (G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_FILTER_OUTPUT_STREAM, GFilterOutputStream))
#define G_FILTER_OUTPUT_STREAM_CLASS(k)     (G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_FILTER_OUTPUT_STREAM, GFilterOutputStreamClass))
#define G_IS_FILTER_OUTPUT_STREAM(o)        (G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_FILTER_OUTPUT_STREAM))
#define G_IS_FILTER_OUTPUT_STREAM_CLASS(k)  (G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_FILTER_OUTPUT_STREAM))
#define G_FILTER_OUTPUT_STREAM_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_FILTER_OUTPUT_STREAM, GFilterOutputStreamClass))

/**
 * GFilterOutputStream:
 * 
 * A base class for all output streams that work on an underlying stream.
 **/
typedef struct _GFilterOutputStreamClass    GFilterOutputStreamClass;
typedef struct _GFilterOutputStreamPrivate  GFilterOutputStreamPrivate;

struct _GFilterOutputStream
{
  GOutputStream parent_instance;

  /*< protected >*/
  GOutputStream *base_stream;
};

struct _GFilterOutputStreamClass
{
 GOutputStreamClass parent_class;

  /*< private >*/
  /* Padding for future expansion */
  void (*_g_reserved1) (void);
  void (*_g_reserved2) (void);
  void (*_g_reserved3) (void);
};


GType           g_filter_output_stream_get_type  (void) G_GNUC_CONST;
GOutputStream  *g_filter_output_stream_get_base_stream (GFilterOutputStream *stream);
G_END_DECLS

#endif /* __G_FILTER_OUTPUT_STREAM_H__ */
