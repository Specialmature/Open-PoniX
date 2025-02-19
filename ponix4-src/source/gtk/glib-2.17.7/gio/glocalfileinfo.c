/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*- */

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

#include "config.h"

#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#endif
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <fcntl.h>
#include <errno.h>
#ifdef HAVE_GRP_H
#include <grp.h>
#endif
#ifdef HAVE_PWD_H
#include <pwd.h>
#endif
#ifdef HAVE_SELINUX
#include <selinux/selinux.h>
#endif

#ifdef HAVE_XATTR

#if defined HAVE_SYS_XATTR_H
  #include <sys/xattr.h>
#elif defined HAVE_ATTR_XATTR_H
  #include <attr/xattr.h>
#else
  #error "Neither <sys/xattr.h> nor <attr/xattr.h> is present but extended attribute support is enabled."
#endif /* defined HAVE_SYS_XATTR_H || HAVE_ATTR_XATTR_H */

#endif /* HAVE_XATTR */

#include <glib/gstdio.h>
#include <gfileattribute-priv.h>

#include "glibintl.h"

#ifdef G_OS_WIN32
#include <windows.h>
#include <io.h>
#ifndef W_OK
#define W_OK 2
#endif
#ifndef R_OK
#define R_OK 4
#endif
#ifndef X_OK
#define X_OK 0 /* not really */
#endif
#ifndef S_ISREG
#define S_ISREG(m) (((m) & _S_IFMT) == _S_IFREG)
#endif
#ifndef S_ISDIR
#define S_ISDIR(m) (((m) & _S_IFMT) == _S_IFDIR)
#endif
#ifndef S_IXUSR
#define S_IXUSR _S_IEXEC
#endif
#endif

#include "glocalfileinfo.h"
#include "gioerror.h"
#include "gthemedicon.h"
#include "gcontenttype.h"
#include "gcontenttypeprivate.h"

#include "gioalias.h"

struct ThumbMD5Context {
	guint32 buf[4];
	guint32 bits[2];
	unsigned char in[64];
};

#ifndef G_OS_WIN32

typedef struct {
  char *user_name;
  char *real_name;
} UidData;

G_LOCK_DEFINE_STATIC (uid_cache);
static GHashTable *uid_cache = NULL;

G_LOCK_DEFINE_STATIC (gid_cache);
static GHashTable *gid_cache = NULL;

#endif  /* !G_OS_WIN32 */

char *
_g_local_file_info_create_etag (GLocalFileStat *statbuf)
{
  GTimeVal tv;
  
  tv.tv_sec = statbuf->st_mtime;
#if defined (HAVE_STRUCT_STAT_ST_MTIMENSEC)
  tv.tv_usec = statbuf->st_mtimensec / 1000;
#elif defined (HAVE_STRUCT_STAT_ST_MTIM_TV_NSEC)
  tv.tv_usec = statbuf->st_mtim.tv_nsec / 1000;
#else
  tv.tv_usec = 0;
#endif

  return g_strdup_printf ("%lu:%lu", tv.tv_sec, tv.tv_usec);
}

static char *
_g_local_file_info_create_file_id (GLocalFileStat *statbuf)
{
  return g_strdup_printf ("l%" G_GUINT64_FORMAT ":%" G_GUINT64_FORMAT,
			  (guint64) statbuf->st_dev, 
			  (guint64) statbuf->st_ino);
}

static char *
_g_local_file_info_create_fs_id (GLocalFileStat *statbuf)
{
  return g_strdup_printf ("l%" G_GUINT64_FORMAT,
			  (guint64) statbuf->st_dev);
}


#ifdef S_ISLNK

static gchar *
read_link (const gchar *full_name)
{
#ifdef HAVE_READLINK
  gchar *buffer;
  guint size;
  
  size = 256;
  buffer = g_malloc (size);
  
  while (1)
    {
      int read_size;
      
      read_size = readlink (full_name, buffer, size);
      if (read_size < 0)
	{
	  g_free (buffer);
	  return NULL;
	}
      if (read_size < size)
	{
	  buffer[read_size] = 0;
	  return buffer;
	}
      size *= 2;
      buffer = g_realloc (buffer, size);
    }
#else
  return NULL;
#endif
}

#endif  /* S_ISLNK */

/* Get the SELinux security context */
static void
get_selinux_context (const char            *path,
		     GFileInfo             *info,
		     GFileAttributeMatcher *attribute_matcher,
		     gboolean               follow_symlinks)
{
#ifdef HAVE_SELINUX
  char *context;

  if (!g_file_attribute_matcher_matches (attribute_matcher, G_FILE_ATTRIBUTE_SELINUX_CONTEXT))
    return;
  
  if (is_selinux_enabled ())
    {
      if (follow_symlinks)
	{
	  if (lgetfilecon_raw (path, &context) < 0)
	    return;
	}
      else
	{
	  if (getfilecon_raw (path, &context) < 0)
	    return;
	}

      if (context)
	{
	  g_file_info_set_attribute_string (info, G_FILE_ATTRIBUTE_SELINUX_CONTEXT, context);
	  freecon (context);
	}
    }
#endif
}

#ifdef HAVE_XATTR

/* Wrappers to hide away differences between (Linux) getxattr/lgetxattr and
 * (Mac) getxattr(..., XATTR_NOFOLLOW)
 */
#ifdef HAVE_XATTR_NOFOLLOW
#define g_fgetxattr(fd,name,value,size)  fgetxattr(fd,name,value,size,0,0)
#define g_flistxattr(fd,name,size)       flistxattr(fd,name,size,0)
#define g_setxattr(path,name,value,size) setxattr(path,name,value,size,0,0)
#else
#define g_fgetxattr     fgetxattr
#define g_flistxattr    flistxattr
#define g_setxattr(path,name,value,size) setxattr(path,name,value,size,0)
#endif

static ssize_t
g_getxattr (const char *path, const char *name, void *value, size_t size,
            gboolean follow_symlinks)
{
#ifdef HAVE_XATTR_NOFOLLOW
  return getxattr (path, name, value, size, 0, follow_symlinks ? 0 : XATTR_NOFOLLOW);
#else
  if (follow_symlinks)
    return getxattr (path, name, value, size);
  else
    return lgetxattr (path, name, value, size);
#endif
}

static ssize_t
g_listxattr(const char *path, char *namebuf, size_t size,
            gboolean follow_symlinks)
{
#ifdef HAVE_XATTR_NOFOLLOW
  return listxattr (path, namebuf, size, follow_symlinks ? 0 : XATTR_NOFOLLOW);
#else
  if (follow_symlinks)
    return listxattr (path, namebuf, size);
  else
    return llistxattr (path, namebuf, size);
#endif
}

static gboolean
valid_char (char c)
{
  return c >= 32 && c <= 126 && c != '\\';
}

static gboolean
name_is_valid (const char *str)
{
  while (*str)
    {
      if (!valid_char (*str++))
	return FALSE;
    }
  return TRUE;
}

static char *
hex_escape_string (const char *str, 
                   gboolean   *free_return)
{
  int num_invalid, i;
  char *escaped_str, *p;
  unsigned char c;
  static char *hex_digits = "0123456789abcdef";
  int len;

  len = strlen (str);
  
  num_invalid = 0;
  for (i = 0; i < len; i++)
    {
      if (!valid_char (str[i]))
	num_invalid++;
    }

  if (num_invalid == 0)
    {
      *free_return = FALSE;
      return (char *)str;
    }

  escaped_str = g_malloc (len + num_invalid*3 + 1);

  p = escaped_str;
  for (i = 0; i < len; i++)
    {
      if (valid_char (str[i]))
	*p++ = str[i];
      else
	{
	  c = str[i];
	  *p++ = '\\';
	  *p++ = 'x';
	  *p++ = hex_digits[(c >> 4) & 0xf];
	  *p++ = hex_digits[c & 0xf];
	}
    }
  *p++ = 0;

  *free_return = TRUE;
  return escaped_str;
}

static char *
hex_unescape_string (const char *str, 
                     int        *out_len, 
                     gboolean   *free_return)
{
  int i;
  char *unescaped_str, *p;
  unsigned char c;
  int len;

  len = strlen (str);
  
  if (strchr (str, '\\') == NULL)
    {
      if (out_len)
	*out_len = len;
      *free_return = FALSE;
      return (char *)str;
    }
  
  unescaped_str = g_malloc (len + 1);

  p = unescaped_str;
  for (i = 0; i < len; i++)
    {
      if (str[i] == '\\' &&
	  str[i+1] == 'x' &&
	  len - i >= 4)
	{
	  c =
	    (g_ascii_xdigit_value (str[i+2]) << 4) |
	    g_ascii_xdigit_value (str[i+3]);
	  *p++ = c;
	  i += 3;
	}
      else
	*p++ = str[i];
    }
  *p++ = 0;

  if (out_len)
    *out_len = p - unescaped_str;
  *free_return = TRUE;
  return unescaped_str;
}

static void
escape_xattr (GFileInfo  *info,
	      const char *gio_attr, /* gio attribute name */
	      const char *value, /* Is zero terminated */
	      size_t      len /* not including zero termination */)
{
  char *escaped_val;
  gboolean free_escaped_val;
  
  escaped_val = hex_escape_string (value, &free_escaped_val);
  
  g_file_info_set_attribute_string (info, gio_attr, escaped_val);
  
  if (free_escaped_val)
    g_free (escaped_val);
}

static void
get_one_xattr (const char *path,
	       GFileInfo  *info,
	       const char *gio_attr,
	       const char *xattr,
	       gboolean    follow_symlinks)
{
  char value[64];
  char *value_p;
  ssize_t len;

  len = g_getxattr (path, xattr, value, sizeof (value)-1, follow_symlinks);

  value_p = NULL;
  if (len >= 0)
    value_p = value;
  else if (len == -1 && errno == ERANGE)
    {
      len = g_getxattr (path, xattr, NULL, 0, follow_symlinks);

      if (len < 0)
	return;

      value_p = g_malloc (len+1);

      len = g_getxattr (path, xattr, value_p, len, follow_symlinks);

      if (len < 0)
	{
	  g_free (value_p);
	  return;
	}
    }
  else
    return;
  
  /* Null terminate */
  value_p[len] = 0;

  escape_xattr (info, gio_attr, value_p, len);
  
  if (value_p != value)
    g_free (value_p);
}

#endif /* defined HAVE_XATTR */

static void
get_xattrs (const char            *path,
	    gboolean               user,
	    GFileInfo             *info,
	    GFileAttributeMatcher *matcher,
	    gboolean               follow_symlinks)
{
#ifdef HAVE_XATTR
  gboolean all;
  gsize list_size;
  ssize_t list_res_size;
  size_t len;
  char *list;
  const char *attr, *attr2;

  if (user)
    all = g_file_attribute_matcher_enumerate_namespace (matcher, "xattr");
  else
    all = g_file_attribute_matcher_enumerate_namespace (matcher, "xattr-sys");

  if (all)
    {
      list_res_size = g_listxattr (path, NULL, 0, follow_symlinks);

      if (list_res_size == -1 ||
	  list_res_size == 0)
	return;

      list_size = list_res_size;
      list = g_malloc (list_size);

    retry:
      
      list_res_size = g_listxattr (path, list, list_size, follow_symlinks);
      
      if (list_res_size == -1 && errno == ERANGE)
	{
	  list_size = list_size * 2;
	  list = g_realloc (list, list_size);
	  goto retry;
	}

      if (list_res_size == -1)
	return;

      attr = list;
      while (list_res_size > 0)
	{
	  if ((user && g_str_has_prefix (attr, "user.")) ||
	      (!user && !g_str_has_prefix (attr, "user.")))
	    {
	      char *escaped_attr, *gio_attr;
	      gboolean free_escaped_attr;
	      
	      if (user)
		{
		  escaped_attr = hex_escape_string (attr + 5, &free_escaped_attr);
		  gio_attr = g_strconcat ("xattr::", escaped_attr, NULL);
		}
	      else
		{
		  escaped_attr = hex_escape_string (attr, &free_escaped_attr);
		  gio_attr = g_strconcat ("xattr-sys::", escaped_attr, NULL);
		}
	      
	      if (free_escaped_attr)
		g_free (escaped_attr);
	      
	      get_one_xattr (path, info, gio_attr, attr, follow_symlinks);
	    }
	      
	  len = strlen (attr) + 1;
	  attr += len;
	  list_res_size -= len;
	}

      g_free (list);
    }
  else
    {
      while ((attr = g_file_attribute_matcher_enumerate_next (matcher)) != NULL)
	{
	  char *unescaped_attribute, *a;
	  gboolean free_unescaped_attribute;

	  attr2 = strchr (attr, ':');
	  if (attr2)
	    {
	      attr2++; /* Skip ':' */
	      unescaped_attribute = hex_unescape_string (attr2, NULL, &free_unescaped_attribute);
	      if (user)
		a = g_strconcat ("user.", unescaped_attribute, NULL);
	      else
		a = unescaped_attribute;
	      
	      get_one_xattr (path, info, attr, a, follow_symlinks);

	      if (user)
		g_free (a);
	      
	      if (free_unescaped_attribute)
		g_free (unescaped_attribute);
	    }
	}
    }
#endif /* defined HAVE_XATTR */
}

#ifdef HAVE_XATTR
static void
get_one_xattr_from_fd (int         fd,
		       GFileInfo  *info,
		       const char *gio_attr,
		       const char *xattr)
{
  char value[64];
  char *value_p;
  ssize_t len;

  len = g_fgetxattr (fd, xattr, value, sizeof (value) - 1);

  value_p = NULL;
  if (len >= 0)
    value_p = value;
  else if (len == -1 && errno == ERANGE)
    {
      len = g_fgetxattr (fd, xattr, NULL, 0);

      if (len < 0)
	return;

      value_p = g_malloc (len + 1);

      len = g_fgetxattr (fd, xattr, value_p, len);

      if (len < 0)
	{
	  g_free (value_p);
	  return;
	}
    }
  else
    return;
  
  /* Null terminate */
  value_p[len] = 0;

  escape_xattr (info, gio_attr, value_p, len);
  
  if (value_p != value)
    g_free (value_p);
}
#endif /* defined HAVE_XATTR */

static void
get_xattrs_from_fd (int                    fd,
		    gboolean               user,
		    GFileInfo             *info,
		    GFileAttributeMatcher *matcher)
{
#ifdef HAVE_XATTR
  gboolean all;
  gsize list_size;
  ssize_t list_res_size;
  size_t len;
  char *list;
  const char *attr, *attr2;

  if (user)
    all = g_file_attribute_matcher_enumerate_namespace (matcher, "xattr");
  else
    all = g_file_attribute_matcher_enumerate_namespace (matcher, "xattr-sys");

  if (all)
    {
      list_res_size = g_flistxattr (fd, NULL, 0);

      if (list_res_size == -1 ||
	  list_res_size == 0)
	return;

      list_size = list_res_size;
      list = g_malloc (list_size);

    retry:
      
      list_res_size = g_flistxattr (fd, list, list_size);
      
      if (list_res_size == -1 && errno == ERANGE)
	{
	  list_size = list_size * 2;
	  list = g_realloc (list, list_size);
	  goto retry;
	}

      if (list_res_size == -1)
	return;

      attr = list;
      while (list_res_size > 0)
	{
	  if ((user && g_str_has_prefix (attr, "user.")) ||
	      (!user && !g_str_has_prefix (attr, "user.")))
	    {
	      char *escaped_attr, *gio_attr;
	      gboolean free_escaped_attr;
	      
	      if (user)
		{
		  escaped_attr = hex_escape_string (attr + 5, &free_escaped_attr);
		  gio_attr = g_strconcat ("xattr::", escaped_attr, NULL);
		}
	      else
		{
		  escaped_attr = hex_escape_string (attr, &free_escaped_attr);
		  gio_attr = g_strconcat ("xattr-sys::", escaped_attr, NULL);
		}
	      
	      if (free_escaped_attr)
		g_free (escaped_attr);
	      
	      get_one_xattr_from_fd (fd, info, gio_attr, attr);
	    }
	  
	  len = strlen (attr) + 1;
	  attr += len;
	  list_res_size -= len;
	}

      g_free (list);
    }
  else
    {
      while ((attr = g_file_attribute_matcher_enumerate_next (matcher)) != NULL)
	{
	  char *unescaped_attribute, *a;
	  gboolean free_unescaped_attribute;

	  attr2 = strchr (attr, ':');
	  if (attr2)
	    {
	      attr2++; /* Skip ':' */
	      unescaped_attribute = hex_unescape_string (attr2, NULL, &free_unescaped_attribute);
	      if (user)
		a = g_strconcat ("user.", unescaped_attribute, NULL);
	      else
		a = unescaped_attribute;
	      
	      get_one_xattr_from_fd (fd, info, attr, a);

	      if (user)
		g_free (a);
	      
	      if (free_unescaped_attribute)
		g_free (unescaped_attribute);
	    }
	}
    }
#endif /* defined HAVE_XATTR */
}

#ifdef HAVE_XATTR
static gboolean
set_xattr (char                       *filename,
	   const char                 *escaped_attribute,
	   const GFileAttributeValue  *attr_value,
	   GError                    **error)
{
  char *attribute, *value;
  gboolean free_attribute, free_value;
  int val_len, res, errsv;
  gboolean is_user;
  char *a;

  if (attr_value == NULL)
    {
      g_set_error_literal (error, G_IO_ERROR, G_IO_ERROR_INVALID_ARGUMENT,
                           _("Attribute value must be non-NULL"));
      return FALSE;
    }

  if (attr_value->type != G_FILE_ATTRIBUTE_TYPE_STRING)
    {
      g_set_error_literal (error, G_IO_ERROR, G_IO_ERROR_INVALID_ARGUMENT,
                           _("Invalid attribute type (string expected)"));
      return FALSE;
    }

  if (!name_is_valid (escaped_attribute))
    {
      g_set_error_literal (error, G_IO_ERROR, G_IO_ERROR_INVALID_ARGUMENT,
                           _("Invalid extended attribute name"));
      return FALSE;
    }

  if (g_str_has_prefix (escaped_attribute, "xattr::"))
    {
      escaped_attribute += strlen ("xattr::");
      is_user = TRUE;
    }
  else
    {
      g_warn_if_fail (g_str_has_prefix (escaped_attribute, "xattr-sys::"));
      escaped_attribute += strlen ("xattr-sys::");
      is_user = FALSE;
    }
  
  attribute = hex_unescape_string (escaped_attribute, NULL, &free_attribute);
  value = hex_unescape_string (attr_value->u.string, &val_len, &free_value);

  if (is_user)
    a = g_strconcat ("user.", attribute, NULL);
  else
    a = attribute;
  
  res = g_setxattr (filename, a, value, val_len);
  errsv = errno;
  
  if (is_user)
    g_free (a);
  
  if (free_attribute)
    g_free (attribute);
  
  if (free_value)
    g_free (value);

  if (res == -1)
    {
      g_set_error (error, G_IO_ERROR,
		   g_io_error_from_errno (errsv),
		   _("Error setting extended attribute '%s': %s"),
		   escaped_attribute, g_strerror (errsv));
      return FALSE;
    }
  
  return TRUE;
}

#endif


void
_g_local_file_info_get_parent_info (const char            *dir,
				    GFileAttributeMatcher *attribute_matcher,
				    GLocalParentFileInfo  *parent_info)
{
  /* Use plain struct stat for now as long as we only look at the
   * S_ISVTX bit which doesn't exist on Win32 anyway.
   */
  struct stat statbuf;
  int res;
  
  parent_info->writable = FALSE;
  parent_info->is_sticky = FALSE;
  parent_info->has_trash_dir = FALSE;
  parent_info->device = 0;

  if (g_file_attribute_matcher_matches (attribute_matcher, G_FILE_ATTRIBUTE_ACCESS_CAN_RENAME) ||
      g_file_attribute_matcher_matches (attribute_matcher, G_FILE_ATTRIBUTE_ACCESS_CAN_DELETE) ||
      g_file_attribute_matcher_matches (attribute_matcher, G_FILE_ATTRIBUTE_ACCESS_CAN_TRASH) ||
      g_file_attribute_matcher_matches (attribute_matcher, G_FILE_ATTRIBUTE_UNIX_IS_MOUNTPOINT))
    {
      /* FIXME: Windows: The underlying _waccess() call in the C
       * library is mostly pointless as it only looks at the READONLY
       * FAT-style attribute of the file, it doesn't check the ACL at
       * all.
       */
      parent_info->writable = (g_access (dir, W_OK) == 0);
      
      res = g_stat (dir, &statbuf);

      /*
       * The sticky bit (S_ISVTX) on a directory means that a file in that directory can be
       * renamed or deleted only by the owner of the file, by the owner of the directory, and
       * by a privileged process.
       */
      if (res == 0)
	{
#ifdef S_ISVTX
	  parent_info->is_sticky = (statbuf.st_mode & S_ISVTX) != 0;
#else
	  parent_info->is_sticky = FALSE;
#endif
	  parent_info->owner = statbuf.st_uid;
	  parent_info->device = statbuf.st_dev;
          /* No need to find trash dir if its not writable anyway */
          if (parent_info->writable &&
              g_file_attribute_matcher_matches (attribute_matcher, G_FILE_ATTRIBUTE_ACCESS_CAN_TRASH))
            parent_info->has_trash_dir = _g_local_file_has_trash_dir (dir, statbuf.st_dev);
	}
    }
}

static void
get_access_rights (GFileAttributeMatcher *attribute_matcher,
		   GFileInfo             *info,
		   const gchar           *path,
		   GLocalFileStat        *statbuf,
		   GLocalParentFileInfo  *parent_info)
{
  /* FIXME: Windows: The underlyin _waccess() is mostly pointless */
  if (g_file_attribute_matcher_matches (attribute_matcher,
					G_FILE_ATTRIBUTE_ACCESS_CAN_READ))
    g_file_info_set_attribute_boolean (info, G_FILE_ATTRIBUTE_ACCESS_CAN_READ,
				       g_access (path, R_OK) == 0);
  
  if (g_file_attribute_matcher_matches (attribute_matcher,
					G_FILE_ATTRIBUTE_ACCESS_CAN_WRITE))
    g_file_info_set_attribute_boolean (info, G_FILE_ATTRIBUTE_ACCESS_CAN_WRITE,
				       g_access (path, W_OK) == 0);
  
  if (g_file_attribute_matcher_matches (attribute_matcher,
					G_FILE_ATTRIBUTE_ACCESS_CAN_EXECUTE))
    g_file_info_set_attribute_boolean (info, G_FILE_ATTRIBUTE_ACCESS_CAN_EXECUTE,
				       g_access (path, X_OK) == 0);


  if (parent_info)
    {
      gboolean writable;

      writable = FALSE;
      if (parent_info->writable)
	{
	  if (parent_info->is_sticky)
	    {
#ifndef G_OS_WIN32
	      uid_t uid = geteuid ();

	      if (uid == statbuf->st_uid ||
		  uid == parent_info->owner ||
		  uid == 0)
#endif
		writable = TRUE;
	    }
	  else
	    writable = TRUE;
	}

      if (g_file_attribute_matcher_matches (attribute_matcher, G_FILE_ATTRIBUTE_ACCESS_CAN_RENAME))
	g_file_info_set_attribute_boolean (info, G_FILE_ATTRIBUTE_ACCESS_CAN_RENAME,
					   writable);
      
      if (g_file_attribute_matcher_matches (attribute_matcher, G_FILE_ATTRIBUTE_ACCESS_CAN_DELETE))
	g_file_info_set_attribute_boolean (info, G_FILE_ATTRIBUTE_ACCESS_CAN_DELETE,
					   writable);

      if (g_file_attribute_matcher_matches (attribute_matcher, G_FILE_ATTRIBUTE_ACCESS_CAN_TRASH))
        g_file_info_set_attribute_boolean (info, G_FILE_ATTRIBUTE_ACCESS_CAN_TRASH,
                                           writable && parent_info->has_trash_dir);
    }
}

static void
set_info_from_stat (GFileInfo             *info, 
                    GLocalFileStat        *statbuf,
		    GFileAttributeMatcher *attribute_matcher)
{
  GFileType file_type;

  file_type = G_FILE_TYPE_UNKNOWN;

  if (S_ISREG (statbuf->st_mode))
    file_type = G_FILE_TYPE_REGULAR;
  else if (S_ISDIR (statbuf->st_mode))
    file_type = G_FILE_TYPE_DIRECTORY;
#ifndef G_OS_WIN32
  else if (S_ISCHR (statbuf->st_mode) ||
	   S_ISBLK (statbuf->st_mode) ||
	   S_ISFIFO (statbuf->st_mode)
#ifdef S_ISSOCK
	   || S_ISSOCK (statbuf->st_mode)
#endif
	   )
    file_type = G_FILE_TYPE_SPECIAL;
#endif
#ifdef S_ISLNK
  else if (S_ISLNK (statbuf->st_mode))
    file_type = G_FILE_TYPE_SYMBOLIC_LINK;
#endif

  g_file_info_set_file_type (info, file_type);
  g_file_info_set_size (info, statbuf->st_size);

  g_file_info_set_attribute_uint32 (info, G_FILE_ATTRIBUTE_UNIX_DEVICE, statbuf->st_dev);
#ifndef G_OS_WIN32
  /* Pointless setting these on Windows even if they exist in the struct */
  g_file_info_set_attribute_uint64 (info, G_FILE_ATTRIBUTE_UNIX_INODE, statbuf->st_ino);
  g_file_info_set_attribute_uint32 (info, G_FILE_ATTRIBUTE_UNIX_NLINK, statbuf->st_nlink);
  g_file_info_set_attribute_uint32 (info, G_FILE_ATTRIBUTE_UNIX_UID, statbuf->st_uid);
  g_file_info_set_attribute_uint32 (info, G_FILE_ATTRIBUTE_UNIX_GID, statbuf->st_gid);
  g_file_info_set_attribute_uint32 (info, G_FILE_ATTRIBUTE_UNIX_RDEV, statbuf->st_rdev);
#endif
  /* FIXME: st_mode is mostly pointless on Windows, too. Set the attribute or not? */
  g_file_info_set_attribute_uint32 (info, G_FILE_ATTRIBUTE_UNIX_MODE, statbuf->st_mode);
#if defined (HAVE_STRUCT_STAT_ST_BLKSIZE)
  g_file_info_set_attribute_uint32 (info, G_FILE_ATTRIBUTE_UNIX_BLOCK_SIZE, statbuf->st_blksize);
#endif
#if defined (HAVE_STRUCT_STAT_ST_BLOCKS)
  g_file_info_set_attribute_uint64 (info, G_FILE_ATTRIBUTE_UNIX_BLOCKS, statbuf->st_blocks);
#endif
  
  g_file_info_set_attribute_uint64 (info, G_FILE_ATTRIBUTE_TIME_MODIFIED, statbuf->st_mtime);
#if defined (HAVE_STRUCT_STAT_ST_MTIMENSEC)
  g_file_info_set_attribute_uint32 (info, G_FILE_ATTRIBUTE_TIME_MODIFIED_USEC, statbuf->st_mtimensec / 1000);
#elif defined (HAVE_STRUCT_STAT_ST_MTIM_TV_NSEC)
  g_file_info_set_attribute_uint32 (info, G_FILE_ATTRIBUTE_TIME_MODIFIED_USEC, statbuf->st_mtim.tv_nsec / 1000);
#endif
  
  g_file_info_set_attribute_uint64 (info, G_FILE_ATTRIBUTE_TIME_ACCESS, statbuf->st_atime);
#if defined (HAVE_STRUCT_STAT_ST_ATIMENSEC)
  g_file_info_set_attribute_uint32 (info, G_FILE_ATTRIBUTE_TIME_ACCESS_USEC, statbuf->st_atimensec / 1000);
#elif defined (HAVE_STRUCT_STAT_ST_ATIM_TV_NSEC)
  g_file_info_set_attribute_uint32 (info, G_FILE_ATTRIBUTE_TIME_ACCESS_USEC, statbuf->st_atim.tv_nsec / 1000);
#endif
  
  g_file_info_set_attribute_uint64 (info, G_FILE_ATTRIBUTE_TIME_CHANGED, statbuf->st_ctime);
#if defined (HAVE_STRUCT_STAT_ST_CTIMENSEC)
  g_file_info_set_attribute_uint32 (info, G_FILE_ATTRIBUTE_TIME_CHANGED_USEC, statbuf->st_ctimensec / 1000);
#elif defined (HAVE_STRUCT_STAT_ST_CTIM_TV_NSEC)
  g_file_info_set_attribute_uint32 (info, G_FILE_ATTRIBUTE_TIME_CHANGED_USEC, statbuf->st_ctim.tv_nsec / 1000);
#endif

  if (g_file_attribute_matcher_matches (attribute_matcher,
					G_FILE_ATTRIBUTE_ETAG_VALUE))
    {
      char *etag = _g_local_file_info_create_etag (statbuf);
      g_file_info_set_attribute_string (info, G_FILE_ATTRIBUTE_ETAG_VALUE, etag);
      g_free (etag);
    }

  if (g_file_attribute_matcher_matches (attribute_matcher,
					G_FILE_ATTRIBUTE_ID_FILE))
    {
      char *id = _g_local_file_info_create_file_id (statbuf);
      g_file_info_set_attribute_string (info, G_FILE_ATTRIBUTE_ID_FILE, id);
      g_free (id);
    }

  if (g_file_attribute_matcher_matches (attribute_matcher,
					G_FILE_ATTRIBUTE_ID_FILESYSTEM))
    {
      char *id = _g_local_file_info_create_fs_id (statbuf);
      g_file_info_set_attribute_string (info, G_FILE_ATTRIBUTE_ID_FILESYSTEM, id);
      g_free (id);
    }
}

#ifndef G_OS_WIN32

static char *
make_valid_utf8 (const char *name)
{
  GString *string;
  const gchar *remainder, *invalid;
  gint remaining_bytes, valid_bytes;
  
  string = NULL;
  remainder = name;
  remaining_bytes = strlen (name);
  
  while (remaining_bytes != 0) 
    {
      if (g_utf8_validate (remainder, remaining_bytes, &invalid)) 
	break;
      valid_bytes = invalid - remainder;
    
      if (string == NULL) 
	string = g_string_sized_new (remaining_bytes);

      g_string_append_len (string, remainder, valid_bytes);
      /* append U+FFFD REPLACEMENT CHARACTER */
      g_string_append (string, "\357\277\275");
      
      remaining_bytes -= valid_bytes + 1;
      remainder = invalid + 1;
    }
  
  if (string == NULL)
    return g_strdup (name);
  
  g_string_append (string, remainder);

  g_warn_if_fail (g_utf8_validate (string->str, -1, NULL));
  
  return g_string_free (string, FALSE);
}

static char *
convert_pwd_string_to_utf8 (char *pwd_str)
{
  char *utf8_string;
  
  if (!g_utf8_validate (pwd_str, -1, NULL))
    {
      utf8_string = g_locale_to_utf8 (pwd_str, -1, NULL, NULL, NULL);
      if (utf8_string == NULL)
	utf8_string = make_valid_utf8 (pwd_str);
    }
  else 
    utf8_string = g_strdup (pwd_str);
  
  return utf8_string;
}

static void
uid_data_free (UidData *data)
{
  g_free (data->user_name);
  g_free (data->real_name);
  g_free (data);
}

/* called with lock held */
static UidData *
lookup_uid_data (uid_t uid)
{
  UidData *data;
  char buffer[4096];
  struct passwd pwbuf;
  struct passwd *pwbufp;
  char *gecos, *comma;
  
  if (uid_cache == NULL)
    uid_cache = g_hash_table_new_full (NULL, NULL, NULL, (GDestroyNotify)uid_data_free);

  data = g_hash_table_lookup (uid_cache, GINT_TO_POINTER (uid));

  if (data)
    return data;

  data = g_new0 (UidData, 1);

#if defined(HAVE_POSIX_GETPWUID_R)
  getpwuid_r (uid, &pwbuf, buffer, sizeof(buffer), &pwbufp);
#elif defined(HAVE_NONPOSIX_GETPWUID_R)
  pwbufp = getpwuid_r (uid, &pwbuf, buffer, sizeof(buffer));
#else
  pwbufp = getpwuid (uid);
#endif

  if (pwbufp != NULL)
    {
      if (pwbufp->pw_name != NULL && pwbufp->pw_name[0] != 0)
	data->user_name = convert_pwd_string_to_utf8 (pwbufp->pw_name);

      gecos = pwbufp->pw_gecos;

      if (gecos)
	{
	  comma = strchr (gecos, ',');
	  if (comma)
	    *comma = 0;
	  data->real_name = convert_pwd_string_to_utf8 (gecos);
	}
    }

  /* Default fallbacks */
  if (data->real_name == NULL)
    {
      if (data->user_name != NULL)
	data->real_name = g_strdup (data->user_name);
      else
	data->real_name = g_strdup_printf ("user #%d", (int)uid);
    }
  
  if (data->user_name == NULL)
    data->user_name = g_strdup_printf ("%d", (int)uid);
  
  g_hash_table_replace (uid_cache, GINT_TO_POINTER (uid), data);
  
  return data;
}

static char *
get_username_from_uid (uid_t uid)
{
  char *res;
  UidData *data;
  
  G_LOCK (uid_cache);
  data = lookup_uid_data (uid);
  res = g_strdup (data->user_name);  
  G_UNLOCK (uid_cache);

  return res;
}

static char *
get_realname_from_uid (uid_t uid)
{
  char *res;
  UidData *data;
  
  G_LOCK (uid_cache);
  data = lookup_uid_data (uid);
  res = g_strdup (data->real_name);  
  G_UNLOCK (uid_cache);
  
  return res;
}

/* called with lock held */
static char *
lookup_gid_name (gid_t gid)
{
  char *name;
  char buffer[4096];
  struct group gbuf;
  struct group *gbufp;
  
  if (gid_cache == NULL)
    gid_cache = g_hash_table_new_full (NULL, NULL, NULL, (GDestroyNotify)g_free);

  name = g_hash_table_lookup (gid_cache, GINT_TO_POINTER (gid));

  if (name)
    return name;

#if defined (HAVE_POSIX_GETGRGID_R)
  getgrgid_r (gid, &gbuf, buffer, sizeof(buffer), &gbufp);
#elif defined (HAVE_NONPOSIX_GETGRGID_R)
  gbufp = getgrgid_r (gid, &gbuf, buffer, sizeof(buffer));
#else
  gbufp = getgrgid (gid);
#endif

  if (gbufp != NULL &&
      gbufp->gr_name != NULL &&
      gbufp->gr_name[0] != 0)
    name = convert_pwd_string_to_utf8 (gbufp->gr_name);
  else
    name = g_strdup_printf("%d", (int)gid);
  
  g_hash_table_replace (gid_cache, GINT_TO_POINTER (gid), name);
  
  return name;
}

static char *
get_groupname_from_gid (gid_t gid)
{
  char *res;
  char *name;
  
  G_LOCK (gid_cache);
  name = lookup_gid_name (gid);
  res = g_strdup (name);  
  G_UNLOCK (gid_cache);
  return res;
}

#endif /* !G_OS_WIN32 */

static char *
get_content_type (const char          *basename,
		  const char          *path,
		  GLocalFileStat      *statbuf,
		  gboolean             is_symlink,
		  gboolean             symlink_broken,
		  GFileQueryInfoFlags  flags,
		  gboolean             fast)
{
  if (is_symlink &&
      (symlink_broken || (flags & G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS)))
    return g_strdup  ("inode/symlink");
  else if (S_ISDIR(statbuf->st_mode))
    return g_strdup ("inode/directory");
#ifndef G_OS_WIN32
  else if (S_ISCHR(statbuf->st_mode))
    return g_strdup ("inode/chardevice");
  else if (S_ISBLK(statbuf->st_mode))
    return g_strdup ("inode/blockdevice");
  else if (S_ISFIFO(statbuf->st_mode))
    return g_strdup ("inode/fifo");
#endif
#ifdef S_ISSOCK
  else if (S_ISSOCK(statbuf->st_mode))
    return g_strdup ("inode/socket");
#endif
  else
    {
      char *content_type;
      gboolean result_uncertain;
      
      content_type = g_content_type_guess (basename, NULL, 0, &result_uncertain);
      
#ifndef G_OS_WIN32
      if (!fast && result_uncertain && path != NULL)
	{
	  guchar sniff_buffer[4096];
	  gsize sniff_length;
	  int fd;

	  sniff_length = _g_unix_content_type_get_sniff_len ();
	  if (sniff_length > 4096)
	    sniff_length = 4096;
	  
	  fd = open (path, O_RDONLY);
	  if (fd != -1)
	    {
	      ssize_t res;
	      
	      res = read (fd, sniff_buffer, sniff_length);
	      close (fd);
	      if (res >= 0)
		{
		  g_free (content_type);
		  content_type = g_content_type_guess (basename, sniff_buffer, res, NULL);
		}
	    }
	}
#endif
      
      return content_type;
    }
  
}

static void
get_thumbnail_attributes (const char *path,
                          GFileInfo  *info)
{
  GChecksum *checksum;
  char *uri;
  char *filename;
  char *basename;

  uri = g_filename_to_uri (path, NULL, NULL);

  checksum = g_checksum_new (G_CHECKSUM_MD5);
  g_checksum_update (checksum, (const guchar *) uri, strlen (uri));
  
  g_free (uri);

  basename = g_strconcat (g_checksum_get_string (checksum), ".png", NULL);
  g_checksum_free (checksum);

  filename = g_build_filename (g_get_home_dir (),
                               ".thumbnails", "normal", basename,
                               NULL);

  if (g_file_test (filename, G_FILE_TEST_IS_REGULAR))
    g_file_info_set_attribute_byte_string (info, G_FILE_ATTRIBUTE_THUMBNAIL_PATH, filename);
  else
    {
      g_free (filename);
      filename = g_build_filename (g_get_home_dir (),
                                   ".thumbnails", "fail",
                                   "gnome-thumbnail-factory",
                                   basename,
                                   NULL);

      if (g_file_test (filename, G_FILE_TEST_IS_REGULAR))
	g_file_info_set_attribute_boolean (info, G_FILE_ATTRIBUTE_THUMBNAILING_FAILED, TRUE);
    }
  g_free (basename);
  g_free (filename);
}

#ifdef G_OS_WIN32
static void
win32_get_file_user_info (const gchar  *filename,
			  gchar       **group_name, 
			  gchar       **user_name, 
			  gchar       **real_name)
{
  PSECURITY_DESCRIPTOR psd = NULL;
  DWORD sd_size = 0; /* first call calculates the size required */
  
  wchar_t *wfilename = g_utf8_to_utf16 (filename, -1, NULL, NULL, NULL);
  if ((GetFileSecurityW (wfilename, 
                        GROUP_SECURITY_INFORMATION | OWNER_SECURITY_INFORMATION,
			NULL,
			sd_size,
			&sd_size) || (ERROR_INSUFFICIENT_BUFFER == GetLastError())) &&
     (psd = g_try_malloc (sd_size)) != NULL &&
     GetFileSecurityW (wfilename, 
                       GROUP_SECURITY_INFORMATION | OWNER_SECURITY_INFORMATION,
		       psd,
		       sd_size,
		       &sd_size))
    {
      PSID psid = 0;
      BOOL defaulted;
      SID_NAME_USE name_use = 0; /* don't care? */
      wchar_t *name = NULL;
      wchar_t *domain = NULL;
      DWORD name_len = 0;
      DWORD domain_len = 0;
      /* get the user name */
      do {
        if (!user_name)
	  break;
	if (!GetSecurityDescriptorOwner (psd, &psid, &defaulted))
	  break;
	if (!LookupAccountSidW (NULL, /* local machine */
                                psid, 
			        name, &name_len,
			        domain, &domain_len, /* no domain info yet */
			        &name_use)  && (ERROR_INSUFFICIENT_BUFFER != GetLastError()))
	  break;
	name = g_try_malloc (name_len * sizeof (wchar_t));
	domain = g_try_malloc (domain_len * sizeof (wchar_t));
	if (name && domain &&
            LookupAccountSidW (NULL, /* local machine */
                               psid, 
			       name, &name_len,
			       domain, &domain_len, /* no domain info yet */
			       &name_use))
	  {
	    *user_name = g_utf16_to_utf8 (name, -1, NULL, NULL, NULL);
	  }
	g_free (name);
	g_free (domain);
      } while (FALSE);

      /* get the group name */
      do {
        if (!group_name)
	  break;
	if (!GetSecurityDescriptorGroup (psd, &psid, &defaulted))
	  break;
	if (!LookupAccountSidW (NULL, /* local machine */
                                psid, 
			        name, &name_len,
			        domain, &domain_len, /* no domain info yet */
			        &name_use)  && (ERROR_INSUFFICIENT_BUFFER != GetLastError()))
	  break;
	name = g_try_malloc (name_len * sizeof (wchar_t));
	domain = g_try_malloc (domain_len * sizeof (wchar_t));
	if (name && domain &&
            LookupAccountSidW (NULL, /* local machine */
                               psid, 
			       name, &name_len,
			       domain, &domain_len, /* no domain info yet */
			       &name_use))
	  {
	    *group_name = g_utf16_to_utf8 (name, -1, NULL, NULL, NULL);
	  }
	g_free (name);
	g_free (domain);
      } while (FALSE);

      /* TODO: get real name */

      g_free (psd);
    }
  g_free (wfilename);
}
#endif /* G_OS_WIN32 */

GFileInfo *
_g_local_file_info_get (const char             *basename,
			const char             *path,
			GFileAttributeMatcher  *attribute_matcher,
			GFileQueryInfoFlags     flags,
			GLocalParentFileInfo   *parent_info,
			GError                **error)
{
  GFileInfo *info;
  GLocalFileStat statbuf;
#ifdef S_ISLNK
  struct stat statbuf2;
#endif
  int res;
  gboolean is_symlink, symlink_broken;
#ifdef G_OS_WIN32
  DWORD dos_attributes;
#endif

  info = g_file_info_new ();

  /* Make sure we don't set any unwanted attributes */
  g_file_info_set_attribute_mask (info, attribute_matcher);
  
  g_file_info_set_name (info, basename);

  /* Avoid stat in trivial case */
  if (attribute_matcher == NULL)
    return info;

#ifndef G_OS_WIN32
  res = g_lstat (path, &statbuf);
#else
  {
    wchar_t *wpath = g_utf8_to_utf16 (path, -1, NULL, NULL, error);
    int len;

    if (wpath == NULL)
      {
        g_object_unref (info);
        return NULL;
      }

    len = wcslen (wpath);
    while (len > 0 && G_IS_DIR_SEPARATOR (wpath[len-1]))
      len--;
    if (len > 0 &&
        (!g_path_is_absolute (path) || len > g_path_skip_root (path) - path))
      wpath[len] = '\0';

    res = _wstati64 (wpath, &statbuf);
    dos_attributes = GetFileAttributesW (wpath);

    g_free (wpath);
  }
#endif

  if (res == -1)
    {
      int errsv = errno;
      char *display_name = g_filename_display_name (path);
      g_object_unref (info);
      g_set_error (error, G_IO_ERROR,
		   g_io_error_from_errno (errsv),
		   _("Error stating file '%s': %s"),
		   display_name, g_strerror (errsv));
      g_free (display_name);
      return NULL;
    }
  
#ifdef S_ISLNK
  is_symlink = S_ISLNK (statbuf.st_mode);
#else
  is_symlink = FALSE;
#endif
  symlink_broken = FALSE;
#ifdef S_ISLNK
  if (is_symlink)
    {
      g_file_info_set_is_symlink (info, TRUE);

      /* Unless NOFOLLOW was set we default to following symlinks */
      if (!(flags & G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS))
	{
	  res = stat (path, &statbuf2);

	    /* Report broken links as symlinks */
	  if (res != -1)
	    statbuf = statbuf2;
	  else
	    symlink_broken = TRUE;
	}
    }
#endif

  set_info_from_stat (info, &statbuf, attribute_matcher);
  
#ifndef G_OS_WIN32
  if (basename != NULL && basename[0] == '.')
    g_file_info_set_is_hidden (info, TRUE);

  if (basename != NULL && basename[strlen (basename) -1] == '~')
    g_file_info_set_attribute_boolean (info, G_FILE_ATTRIBUTE_STANDARD_IS_BACKUP, TRUE);
#else
  if (dos_attributes & FILE_ATTRIBUTE_HIDDEN)
    g_file_info_set_is_hidden (info, TRUE);

  if (dos_attributes & FILE_ATTRIBUTE_ARCHIVE)
    g_file_info_set_attribute_boolean (info, G_FILE_ATTRIBUTE_DOS_IS_ARCHIVE, TRUE);

  if (dos_attributes & FILE_ATTRIBUTE_SYSTEM)
    g_file_info_set_attribute_boolean (info, G_FILE_ATTRIBUTE_DOS_IS_SYSTEM, TRUE);
#endif

#ifdef S_ISLNK
  if (is_symlink &&
      g_file_attribute_matcher_matches (attribute_matcher,
					G_FILE_ATTRIBUTE_STANDARD_SYMLINK_TARGET))
    {
      char *link = read_link (path);
      g_file_info_set_symlink_target (info, link);
      g_free (link);
    }
#endif

  if (g_file_attribute_matcher_matches (attribute_matcher,
					G_FILE_ATTRIBUTE_STANDARD_DISPLAY_NAME))
    {
      char *display_name = g_filename_display_basename (path);
     
      /* look for U+FFFD REPLACEMENT CHARACTER */ 
      if (strstr (display_name, "\357\277\275") != NULL)
	{
	  char *p = display_name;
	  display_name = g_strconcat (display_name, _(" (invalid encoding)"), NULL);
	  g_free (p);
	}
      g_file_info_set_display_name (info, display_name);
      g_free (display_name);
    }
  
  if (g_file_attribute_matcher_matches (attribute_matcher,
					G_FILE_ATTRIBUTE_STANDARD_EDIT_NAME))
    {
      char *edit_name = g_filename_display_basename (path);
      g_file_info_set_edit_name (info, edit_name);
      g_free (edit_name);
    }

  
  if (g_file_attribute_matcher_matches (attribute_matcher,
					G_FILE_ATTRIBUTE_STANDARD_COPY_NAME))
    {
      char *copy_name = g_filename_to_utf8 (basename, -1, NULL, NULL, NULL);
      if (copy_name)
	g_file_info_set_attribute_string (info, G_FILE_ATTRIBUTE_STANDARD_COPY_NAME, copy_name);
      g_free (copy_name);
    }

  if (g_file_attribute_matcher_matches (attribute_matcher,
					G_FILE_ATTRIBUTE_STANDARD_CONTENT_TYPE) ||
      g_file_attribute_matcher_matches (attribute_matcher,
					G_FILE_ATTRIBUTE_STANDARD_ICON))
    {
      char *content_type = get_content_type (basename, path, &statbuf, is_symlink, symlink_broken, flags, FALSE);

      if (content_type)
	{
	  g_file_info_set_content_type (info, content_type);

	  if (g_file_attribute_matcher_matches (attribute_matcher,
						G_FILE_ATTRIBUTE_STANDARD_ICON))
	    {
	      GIcon *icon;

              if (strcmp (path, g_get_home_dir ()) == 0)
                icon = g_themed_icon_new ("user-home");
              else if (strcmp (path, g_get_user_special_dir (G_USER_DIRECTORY_DESKTOP)) == 0) 
                icon = g_themed_icon_new ("user-desktop");
              else 
                {
                  icon = g_content_type_get_icon (content_type);
                  if (G_IS_THEMED_ICON (icon))
                    {
                      const char *type_icon = NULL;

                      if (S_ISDIR (statbuf.st_mode)) 
                        type_icon = "folder";
                      else if (statbuf.st_mode & S_IXUSR)
                        type_icon = "application-x-executable";
                      else
                        type_icon = "text-x-generic";

                      g_themed_icon_append_name (G_THEMED_ICON (icon), type_icon);
                    }
                }

              if (icon != NULL)
                {
                  g_file_info_set_icon (info, icon);
                  g_object_unref (icon);
                }
	    }
	  
	  g_free (content_type);
	}
    }

  if (g_file_attribute_matcher_matches (attribute_matcher,
					G_FILE_ATTRIBUTE_STANDARD_FAST_CONTENT_TYPE))
    {
      char *content_type = get_content_type (basename, path, &statbuf, is_symlink, symlink_broken, flags, TRUE);
      
      if (content_type)
	{
	  g_file_info_set_attribute_string (info, G_FILE_ATTRIBUTE_STANDARD_FAST_CONTENT_TYPE, content_type);
	  g_free (content_type);
	}
    }

  if (g_file_attribute_matcher_matches (attribute_matcher,
					G_FILE_ATTRIBUTE_OWNER_USER))
    {
      char *name = NULL;
      
#ifdef G_OS_WIN32
      win32_get_file_user_info (path, NULL, &name, NULL);
#else
      name = get_username_from_uid (statbuf.st_uid);
#endif
      if (name)
	g_file_info_set_attribute_string (info, G_FILE_ATTRIBUTE_OWNER_USER, name);
      g_free (name);
    }

  if (g_file_attribute_matcher_matches (attribute_matcher,
					G_FILE_ATTRIBUTE_OWNER_USER_REAL))
    {
      char *name = NULL;
#ifdef G_OS_WIN32
      win32_get_file_user_info (path, NULL, NULL, &name);
#else
      name = get_realname_from_uid (statbuf.st_uid);
#endif
      if (name)
	g_file_info_set_attribute_string (info, G_FILE_ATTRIBUTE_OWNER_USER_REAL, name);
      g_free (name);
    }
  
  if (g_file_attribute_matcher_matches (attribute_matcher,
					G_FILE_ATTRIBUTE_OWNER_GROUP))
    {
      char *name = NULL;
#ifdef G_OS_WIN32
      win32_get_file_user_info (path, &name, NULL, NULL);
#else
      name = get_groupname_from_gid (statbuf.st_gid);
#endif
      if (name)
	g_file_info_set_attribute_string (info, G_FILE_ATTRIBUTE_OWNER_GROUP, name);
      g_free (name);
    }

  if (parent_info && parent_info->device != 0 &&
      g_file_attribute_matcher_matches (attribute_matcher, G_FILE_ATTRIBUTE_UNIX_IS_MOUNTPOINT) &&
      statbuf.st_dev != parent_info->device) 
    g_file_info_set_attribute_boolean (info, G_FILE_ATTRIBUTE_UNIX_IS_MOUNTPOINT, TRUE);
  
  get_access_rights (attribute_matcher, info, path, &statbuf, parent_info);
  
  get_selinux_context (path, info, attribute_matcher, (flags & G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS) == 0);
  get_xattrs (path, TRUE, info, attribute_matcher, (flags & G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS) == 0);
  get_xattrs (path, FALSE, info, attribute_matcher, (flags & G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS) == 0);

  if (g_file_attribute_matcher_matches (attribute_matcher,
					G_FILE_ATTRIBUTE_THUMBNAIL_PATH))
    get_thumbnail_attributes (path, info);
  
  g_file_info_unset_attribute_mask (info);

  return info;
}

GFileInfo *
_g_local_file_info_get_from_fd (int      fd,
				char    *attributes,
				GError **error)
{
  GLocalFileStat stat_buf;
  GFileAttributeMatcher *matcher;
  GFileInfo *info;
  
#ifdef G_OS_WIN32
#define FSTAT _fstati64
#else
#define FSTAT fstat
#endif

  if (FSTAT (fd, &stat_buf) == -1)
    {
      int errsv = errno;

      g_set_error (error, G_IO_ERROR,
		   g_io_error_from_errno (errsv),
		   _("Error stating file descriptor: %s"),
		   g_strerror (errsv));
      return NULL;
    }

  info = g_file_info_new ();

  matcher = g_file_attribute_matcher_new (attributes);

  /* Make sure we don't set any unwanted attributes */
  g_file_info_set_attribute_mask (info, matcher);
  
  set_info_from_stat (info, &stat_buf, matcher);
  
#ifdef HAVE_SELINUX
  if (g_file_attribute_matcher_matches (matcher, G_FILE_ATTRIBUTE_SELINUX_CONTEXT) &&
      is_selinux_enabled ())
    {
      char *context;
      if (fgetfilecon_raw (fd, &context) >= 0)
	{
	  g_file_info_set_attribute_string (info, G_FILE_ATTRIBUTE_SELINUX_CONTEXT, context);
	  freecon (context);
	}
    }
#endif

  get_xattrs_from_fd (fd, TRUE, info, matcher);
  get_xattrs_from_fd (fd, FALSE, info, matcher);
  
  g_file_attribute_matcher_unref (matcher);

  g_file_info_unset_attribute_mask (info);
  
  return info;
}

static gboolean
get_uint32 (const GFileAttributeValue  *value,
	    guint32                    *val_out,
	    GError                    **error)
{
  if (value->type != G_FILE_ATTRIBUTE_TYPE_UINT32)
    {
      g_set_error_literal (error, G_IO_ERROR, G_IO_ERROR_INVALID_ARGUMENT,
                           _("Invalid attribute type (uint32 expected)"));
      return FALSE;
    }

  *val_out = value->u.uint32;
  
  return TRUE;
}

#ifdef HAVE_UTIMES
static gboolean
get_uint64 (const GFileAttributeValue  *value,
	    guint64                    *val_out,
	    GError                    **error)
{
  if (value->type != G_FILE_ATTRIBUTE_TYPE_UINT64)
    {
      g_set_error_literal (error, G_IO_ERROR, G_IO_ERROR_INVALID_ARGUMENT,
                           _("Invalid attribute type (uint64 expected)"));
      return FALSE;
    }

  *val_out = value->u.uint64;
  
  return TRUE;
}
#endif

#if defined(HAVE_SYMLINK)
static gboolean
get_byte_string (const GFileAttributeValue  *value,
		 const char                **val_out,
		 GError                    **error)
{
  if (value->type != G_FILE_ATTRIBUTE_TYPE_BYTE_STRING)
    {
      g_set_error_literal (error, G_IO_ERROR, G_IO_ERROR_INVALID_ARGUMENT,
                           _("Invalid attribute type (byte string expected)"));
      return FALSE;
    }

  *val_out = value->u.string;
  
  return TRUE;
}
#endif

static gboolean
get_string (const GFileAttributeValue  *value,
	    const char                **val_out,
	    GError                    **error)
{
  if (value->type != G_FILE_ATTRIBUTE_TYPE_STRING)
    {
      g_set_error (error, G_IO_ERROR, G_IO_ERROR_INVALID_ARGUMENT,
		   _("Invalid attribute type (byte string expected)"));
      return FALSE;
    }

  *val_out = value->u.string;
  
  return TRUE;
}


static gboolean
set_unix_mode (char                       *filename,
	       const GFileAttributeValue  *value,
	       GError                    **error)
{
  guint32 val;
  
  if (!get_uint32 (value, &val, error))
    return FALSE;
  
  if (g_chmod (filename, val) == -1)
    {
      int errsv = errno;

      g_set_error (error, G_IO_ERROR,
		   g_io_error_from_errno (errsv),
		   _("Error setting permissions: %s"),
		   g_strerror (errsv));
      return FALSE;
    }
  return TRUE;
}

#ifdef HAVE_CHOWN
static gboolean
set_unix_uid_gid (char                       *filename,
		  const GFileAttributeValue  *uid_value,
		  const GFileAttributeValue  *gid_value,
		  GFileQueryInfoFlags         flags,
		  GError                    **error)
{
  int res;
  guint32 val;
  uid_t uid;
  gid_t gid;
  
  if (uid_value)
    {
      if (!get_uint32 (uid_value, &val, error))
	return FALSE;
      uid = val;
    }
  else
    uid = -1;
  
  if (gid_value)
    {
      if (!get_uint32 (gid_value, &val, error))
	return FALSE;
      gid = val;
    }
  else
    gid = -1;
  
#ifdef HAVE_LCHOWN
  if (flags & G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS)
    res = lchown (filename, uid, gid);
  else
#endif
    res = chown (filename, uid, gid);
  
  if (res == -1)
    {
      int errsv = errno;

      g_set_error (error, G_IO_ERROR,
		   g_io_error_from_errno (errsv),
		   _("Error setting owner: %s"),
		   g_strerror (errsv));
	  return FALSE;
    }
  return TRUE;
}
#endif

#ifdef HAVE_SYMLINK
static gboolean
set_symlink (char                       *filename,
	     const GFileAttributeValue  *value,
	     GError                    **error)
{
  const char *val;
  struct stat statbuf;
  
  if (!get_byte_string (value, &val, error))
    return FALSE;
  
  if (val == NULL)
    {
      g_set_error_literal (error, G_IO_ERROR, G_IO_ERROR_INVALID_ARGUMENT,
                           _("symlink must be non-NULL"));
      return FALSE;
    }
  
  if (g_lstat (filename, &statbuf))
    {
      int errsv = errno;

      g_set_error (error, G_IO_ERROR,
		   g_io_error_from_errno (errsv),
		   _("Error setting symlink: %s"),
		   g_strerror (errsv));
      return FALSE;
    }
  
  if (!S_ISLNK (statbuf.st_mode))
    {
      g_set_error_literal (error, G_IO_ERROR,
                           G_IO_ERROR_NOT_SYMBOLIC_LINK,
                           _("Error setting symlink: file is not a symlink"));
      return FALSE;
    }
  
  if (g_unlink (filename))
    {
      int errsv = errno;

      g_set_error (error, G_IO_ERROR,
		   g_io_error_from_errno (errsv),
		   _("Error setting symlink: %s"),
		   g_strerror (errsv));
      return FALSE;
    }
  
  if (symlink (filename, val) != 0)
    {
      int errsv = errno;

      g_set_error (error, G_IO_ERROR,
		   g_io_error_from_errno (errsv),
		   _("Error setting symlink: %s"),
		   g_strerror (errsv));
      return FALSE;
    }
  
  return TRUE;
}
#endif

#ifdef HAVE_UTIMES
static int
lazy_stat (char        *filename, 
           struct stat *statbuf, 
           gboolean    *called_stat)
{
  int res;

  if (*called_stat)
    return 0;
  
  res = g_stat (filename, statbuf);
  
  if (res == 0)
    *called_stat = TRUE;
  
  return res;
}


static gboolean
set_mtime_atime (char                       *filename,
		 const GFileAttributeValue  *mtime_value,
		 const GFileAttributeValue  *mtime_usec_value,
		 const GFileAttributeValue  *atime_value,
		 const GFileAttributeValue  *atime_usec_value,
		 GError                    **error)
{
  int res;
  guint64 val;
  guint32 val_usec;
  struct stat statbuf;
  gboolean got_stat = FALSE;
  struct timeval times[2] = { {0, 0}, {0, 0} };

  /* ATIME */
  if (atime_value)
    {
      if (!get_uint64 (atime_value, &val, error))
	return FALSE;
      times[0].tv_sec = val;
    }
  else
    {
      if (lazy_stat (filename, &statbuf, &got_stat) == 0)
	{
	  times[0].tv_sec = statbuf.st_mtime;
#if defined (HAVE_STRUCT_STAT_ST_ATIMENSEC)
	  times[0].tv_usec = statbuf.st_atimensec / 1000;
#elif defined (HAVE_STRUCT_STAT_ST_ATIM_TV_NSEC)
	  times[0].tv_usec = statbuf.st_atim.tv_nsec / 1000;
#endif
	}
    }
  
  if (atime_usec_value)
    {
      if (!get_uint32 (atime_usec_value, &val_usec, error))
	return FALSE;
      times[0].tv_usec = val_usec;
    }

  /* MTIME */
  if (mtime_value)
    {
      if (!get_uint64 (mtime_value, &val, error))
	return FALSE;
      times[1].tv_sec = val;
    }
  else
    {
      if (lazy_stat (filename, &statbuf, &got_stat) == 0)
	{
	  times[1].tv_sec = statbuf.st_mtime;
#if defined (HAVE_STRUCT_STAT_ST_MTIMENSEC)
	  times[1].tv_usec = statbuf.st_mtimensec / 1000;
#elif defined (HAVE_STRUCT_STAT_ST_MTIM_TV_NSEC)
	  times[1].tv_usec = statbuf.st_mtim.tv_nsec / 1000;
#endif
	}
    }
  
  if (mtime_usec_value)
    {
      if (!get_uint32 (mtime_usec_value, &val_usec, error))
	return FALSE;
      times[1].tv_usec = val_usec;
    }
  
  res = utimes (filename, times);
  if (res == -1)
    {
      int errsv = errno;

      g_set_error (error, G_IO_ERROR,
		   g_io_error_from_errno (errsv),
		   _("Error setting owner: %s"),
		   g_strerror (errsv));
	  return FALSE;
    }
  return TRUE;
}
#endif


static gboolean
set_selinux_context (char                       *filename,
		 const GFileAttributeValue  *value,
		 GError                    **error)
{
  const char *val;

  if (!get_string (value, &val, error))
    return FALSE;

  if (val == NULL)
  {
    g_set_error (error, G_IO_ERROR, G_IO_ERROR_INVALID_ARGUMENT,
               _("SELinux context must be non-NULL"));
    return FALSE;
  }

#ifdef HAVE_SELINUX
  if (is_selinux_enabled ()) {
	security_context_t val_s;
	
	val_s = g_strdup (val);
	
	if (setfilecon_raw (filename, val_s) < 0)
	{
            int errsv = errno;
            
            g_set_error (error, G_IO_ERROR,
                         g_io_error_from_errno (errsv),
                	_("Error setting SELinux context: %s"),
                         g_strerror (errsv));
            return FALSE;
        }
        g_free (val_s);
  } else {
    g_set_error (error, G_IO_ERROR, G_IO_ERROR_INVALID_ARGUMENT,
               _("SELinux is not enabled on this system"));
    return FALSE;
  }
#endif 
                                                     
  return TRUE;
}


gboolean
_g_local_file_info_set_attribute (char                 *filename,
				  const char           *attribute,
				  GFileAttributeType    type,
				  gpointer              value_p,
				  GFileQueryInfoFlags   flags,
				  GCancellable         *cancellable,
				  GError              **error)
{
  GFileAttributeValue value = { 0 };

  _g_file_attribute_value_set_from_pointer (&value, type, value_p, FALSE);
  
  if (strcmp (attribute, G_FILE_ATTRIBUTE_UNIX_MODE) == 0)
    return set_unix_mode (filename, &value, error);
  
#ifdef HAVE_CHOWN
  else if (strcmp (attribute, G_FILE_ATTRIBUTE_UNIX_UID) == 0)
    return set_unix_uid_gid (filename, &value, NULL, flags, error);
  else if (strcmp (attribute, G_FILE_ATTRIBUTE_UNIX_GID) == 0)
    return set_unix_uid_gid (filename, NULL, &value, flags, error);
#endif
  
#ifdef HAVE_SYMLINK
  else if (strcmp (attribute, G_FILE_ATTRIBUTE_STANDARD_SYMLINK_TARGET) == 0)
    return set_symlink (filename, &value, error);
#endif

#ifdef HAVE_UTIMES
  else if (strcmp (attribute, G_FILE_ATTRIBUTE_TIME_MODIFIED) == 0)
    return set_mtime_atime (filename, &value, NULL, NULL, NULL, error);
  else if (strcmp (attribute, G_FILE_ATTRIBUTE_TIME_MODIFIED_USEC) == 0)
    return set_mtime_atime (filename, NULL, &value, NULL, NULL, error);
  else if (strcmp (attribute, G_FILE_ATTRIBUTE_TIME_ACCESS) == 0)
    return set_mtime_atime (filename, NULL, NULL, &value, NULL, error);
  else if (strcmp (attribute, G_FILE_ATTRIBUTE_TIME_ACCESS_USEC) == 0)
    return set_mtime_atime (filename, NULL, NULL, NULL, &value, error);
#endif

#ifdef HAVE_XATTR
  else if (g_str_has_prefix (attribute, "xattr::"))
    return set_xattr (filename, attribute, &value, error);
  else if (g_str_has_prefix (attribute, "xattr-sys::"))
    return set_xattr (filename, attribute, &value, error);
#endif

#ifdef HAVE_SELINUX 
  else if (strcmp (attribute, G_FILE_ATTRIBUTE_SELINUX_CONTEXT) == 0)
    return set_selinux_context (filename, &value, error);
#endif
  
  g_set_error (error, G_IO_ERROR, G_IO_ERROR_NOT_SUPPORTED,
	       _("Setting attribute %s not supported"), attribute);
  return FALSE;
}

gboolean
_g_local_file_info_set_attributes  (char                 *filename,
				    GFileInfo            *info,
				    GFileQueryInfoFlags   flags,
				    GCancellable         *cancellable,
				    GError              **error)
{
  GFileAttributeValue *value;
#ifdef HAVE_CHOWN
  GFileAttributeValue *uid, *gid;
#endif
#ifdef HAVE_UTIMES
  GFileAttributeValue *mtime, *mtime_usec, *atime, *atime_usec;
#endif
#if defined (HAVE_CHOWN) && defined (HAVE_UTIMES)
  GFileAttributeStatus status;
#endif
  gboolean res;
  
  /* Handles setting multiple specified data in a single set, and takes care
     of ordering restrictions when setting attributes */

  res = TRUE;

  /* Set symlink first, since this recreates the file */
#ifdef HAVE_SYMLINK
  value = _g_file_info_get_attribute_value (info, G_FILE_ATTRIBUTE_STANDARD_SYMLINK_TARGET);
  if (value)
    {
      if (!set_symlink (filename, value, error))
	{
	  value->status = G_FILE_ATTRIBUTE_STATUS_ERROR_SETTING;
	  res = FALSE;
	  /* Don't set error multiple times */
	  error = NULL;
	}
      else
	value->status = G_FILE_ATTRIBUTE_STATUS_SET;
	
    }
#endif

#ifdef HAVE_CHOWN
  /* Group uid and gid setting into one call
   * Change ownership before permissions, since ownership changes can
     change permissions (e.g. setuid)
   */
  uid = _g_file_info_get_attribute_value (info, G_FILE_ATTRIBUTE_UNIX_UID);
  gid = _g_file_info_get_attribute_value (info, G_FILE_ATTRIBUTE_UNIX_GID);
  
  if (uid || gid)
    {
      if (!set_unix_uid_gid (filename, uid, gid, flags, error))
	{
	  status = G_FILE_ATTRIBUTE_STATUS_ERROR_SETTING;
	  res = FALSE;
	  /* Don't set error multiple times */
	  error = NULL;
	}
      else
	status = G_FILE_ATTRIBUTE_STATUS_SET;
      if (uid)
	uid->status = status;
      if (gid)
	gid->status = status;
    }
#endif
  
  value = _g_file_info_get_attribute_value (info, G_FILE_ATTRIBUTE_UNIX_MODE);
  if (value)
    {
      if (!set_unix_mode (filename, value, error))
	{
	  value->status = G_FILE_ATTRIBUTE_STATUS_ERROR_SETTING;
	  res = FALSE;
	  /* Don't set error multiple times */
	  error = NULL;
	}
      else
	value->status = G_FILE_ATTRIBUTE_STATUS_SET;
	
    }

#ifdef HAVE_UTIMES
  /* Group all time settings into one call
   * Change times as the last thing to avoid it changing due to metadata changes
   */
  
  mtime = _g_file_info_get_attribute_value (info, G_FILE_ATTRIBUTE_TIME_MODIFIED);
  mtime_usec = _g_file_info_get_attribute_value (info, G_FILE_ATTRIBUTE_TIME_MODIFIED_USEC);
  atime = _g_file_info_get_attribute_value (info, G_FILE_ATTRIBUTE_TIME_ACCESS);
  atime_usec = _g_file_info_get_attribute_value (info, G_FILE_ATTRIBUTE_TIME_ACCESS_USEC);

  if (mtime || mtime_usec || atime || atime_usec)
    {
      if (!set_mtime_atime (filename, mtime, mtime_usec, atime, atime_usec, error))
	{
	  status = G_FILE_ATTRIBUTE_STATUS_ERROR_SETTING;
	  res = FALSE;
	  /* Don't set error multiple times */
	  error = NULL;
	}
      else
	status = G_FILE_ATTRIBUTE_STATUS_SET;
      
      if (mtime)
	mtime->status = status;
      if (mtime_usec)
	mtime_usec->status = status;
      if (atime)
	atime->status = status;
      if (atime_usec)
	atime_usec->status = status;
    }
#endif

  /* xattrs are handled by default callback */


  /*  SELinux context */
#ifdef HAVE_SELINUX 
  if (is_selinux_enabled ()) {
    value = _g_file_info_get_attribute_value (info, G_FILE_ATTRIBUTE_SELINUX_CONTEXT);
    if (value)
    {
      if (!set_selinux_context (filename, value, error))
        {
          value->status = G_FILE_ATTRIBUTE_STATUS_ERROR_SETTING;
          res = FALSE;
          /* Don't set error multiple times */
          error = NULL;
        }
      else
        value->status = G_FILE_ATTRIBUTE_STATUS_SET;
    }
  }
#endif

  return res;
}
