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
 * Author: Alexander Larsson <alexl@redhat.com>
 */

#ifndef __G_LOCAL_FILE_OUTPUT_STREAM_H__
#define __G_LOCAL_FILE_OUTPUT_STREAM_H__

#include <gio/gfileoutputstream.h>

G_BEGIN_DECLS

#define G_TYPE_LOCAL_FILE_OUTPUT_STREAM         (_g_local_file_output_stream_get_type ())
#define G_LOCAL_FILE_OUTPUT_STREAM(o)           (G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_LOCAL_FILE_OUTPUT_STREAM, GLocalFileOutputStream))
#define G_LOCAL_FILE_OUTPUT_STREAM_CLASS(k)     (G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_LOCAL_FILE_OUTPUT_STREAM, GLocalFileOutputStreamClass))
#define G_IS_LOCAL_FILE_OUTPUT_STREAM(o)        (G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_LOCAL_FILE_OUTPUT_STREAM))
#define G_IS_LOCAL_FILE_OUTPUT_STREAM_CLASS(k)  (G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_LOCAL_FILE_OUTPUT_STREAM))
#define G_LOCAL_FILE_OUTPUT_STREAM_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_LOCAL_FILE_OUTPUT_STREAM, GLocalFileOutputStreamClass))

typedef struct _GLocalFileOutputStream         GLocalFileOutputStream;
typedef struct _GLocalFileOutputStreamClass    GLocalFileOutputStreamClass;
typedef struct _GLocalFileOutputStreamPrivate  GLocalFileOutputStreamPrivate;

struct _GLocalFileOutputStream
{
  GFileOutputStream parent_instance;

  /*< private >*/
  GLocalFileOutputStreamPrivate *priv;
};

struct _GLocalFileOutputStreamClass
{
  GFileOutputStreamClass parent_class;
};

GType _g_local_file_output_stream_get_type (void) G_GNUC_CONST;
GFileOutputStream *_g_local_file_output_stream_create  (const char       *filename,
							GFileCreateFlags  flags,
							GCancellable     *cancellable,
							GError          **error);
GFileOutputStream *_g_local_file_output_stream_append  (const char       *filename,
							GFileCreateFlags  flags,
							GCancellable     *cancellable,
							GError          **error);
GFileOutputStream *_g_local_file_output_stream_replace (const char       *filename,
							const char       *etag,
							gboolean          create_backup,
							GFileCreateFlags  flags,
							GCancellable     *cancellable,
							GError          **error);

G_END_DECLS

#endif /* __G_LOCAL_FILE_OUTPUT_STREAM_H__ */
