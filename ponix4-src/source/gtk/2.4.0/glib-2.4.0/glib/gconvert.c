/* GLIB - Library of useful routines for C programming
 *
 * gconvert.c: Convert between character sets using iconv
 * Copyright Red Hat Inc., 2000
 * Authors: Havoc Pennington <hp@redhat.com>, Owen Taylor <otaylor@redhat.com
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

#include <iconv.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "glib.h"
#include "gprintfint.h"
#include "gthreadinit.h"

#ifdef G_PLATFORM_WIN32
#define STRICT
#include <windows.h>
#undef STRICT
#endif

#include "glibintl.h"

#if defined(USE_LIBICONV_GNU) && !defined (_LIBICONV_H)
#error GNU libiconv in use but included iconv.h not from libiconv
#endif
#if !defined(USE_LIBICONV_GNU) && defined (_LIBICONV_H)
#error GNU libiconv not in use but included iconv.h is from libiconv
#endif

GQuark 
g_convert_error_quark (void)
{
  static GQuark quark;
  if (!quark)
    quark = g_quark_from_static_string ("g_convert_error");

  return quark;
}

static gboolean
try_conversion (const char *to_codeset,
		const char *from_codeset,
		iconv_t    *cd)
{
  *cd = iconv_open (to_codeset, from_codeset);

  if (*cd == (iconv_t)-1 && errno == EINVAL)
    return FALSE;
  else
    return TRUE;
}

static gboolean
try_to_aliases (const char **to_aliases,
		const char  *from_codeset,
		iconv_t     *cd)
{
  if (to_aliases)
    {
      const char **p = to_aliases;
      while (*p)
	{
	  if (try_conversion (*p, from_codeset, cd))
	    return TRUE;

	  p++;
	}
    }

  return FALSE;
}

extern const char **_g_charset_get_aliases (const char *canonical_name);

/**
 * g_iconv_open:
 * @to_codeset: destination codeset
 * @from_codeset: source codeset
 * 
 * Same as the standard UNIX routine iconv_open(), but
 * may be implemented via libiconv on UNIX flavors that lack
 * a native implementation.
 * 
 * GLib provides g_convert() and g_locale_to_utf8() which are likely
 * more convenient than the raw iconv wrappers.
 * 
 * Return value: a "conversion descriptor", or (GIConv)-1 if
 *  opening the converter failed.
 **/
GIConv
g_iconv_open (const gchar  *to_codeset,
	      const gchar  *from_codeset)
{
  iconv_t cd;
  
  if (!try_conversion (to_codeset, from_codeset, &cd))
    {
      const char **to_aliases = _g_charset_get_aliases (to_codeset);
      const char **from_aliases = _g_charset_get_aliases (from_codeset);

      if (from_aliases)
	{
	  const char **p = from_aliases;
	  while (*p)
	    {
	      if (try_conversion (to_codeset, *p, &cd))
		goto out;

	      if (try_to_aliases (to_aliases, *p, &cd))
		goto out;

	      p++;
	    }
	}

      if (try_to_aliases (to_aliases, from_codeset, &cd))
	goto out;
    }

 out:
  return (cd == (iconv_t)-1) ? (GIConv)-1 : (GIConv)cd;
}

/**
 * g_iconv:
 * @converter: conversion descriptor from g_iconv_open()
 * @inbuf: bytes to convert
 * @inbytes_left: inout parameter, bytes remaining to convert in @inbuf
 * @outbuf: converted output bytes
 * @outbytes_left: inout parameter, bytes available to fill in @outbuf
 * 
 * Same as the standard UNIX routine iconv(), but
 * may be implemented via libiconv on UNIX flavors that lack
 * a native implementation.
 *
 * GLib provides g_convert() and g_locale_to_utf8() which are likely
 * more convenient than the raw iconv wrappers.
 * 
 * Return value: count of non-reversible conversions, or -1 on error
 **/
size_t 
g_iconv (GIConv   converter,
	 gchar  **inbuf,
	 gsize   *inbytes_left,
	 gchar  **outbuf,
	 gsize   *outbytes_left)
{
  iconv_t cd = (iconv_t)converter;

  return iconv (cd, inbuf, inbytes_left, outbuf, outbytes_left);
}

/**
 * g_iconv_close:
 * @converter: a conversion descriptor from g_iconv_open()
 *
 * Same as the standard UNIX routine iconv_close(), but
 * may be implemented via libiconv on UNIX flavors that lack
 * a native implementation. Should be called to clean up
 * the conversion descriptor from g_iconv_open() when
 * you are done converting things.
 *
 * GLib provides g_convert() and g_locale_to_utf8() which are likely
 * more convenient than the raw iconv wrappers.
 * 
 * Return value: -1 on error, 0 on success
 **/
gint
g_iconv_close (GIConv converter)
{
  iconv_t cd = (iconv_t)converter;

  return iconv_close (cd);
}


#define ICONV_CACHE_SIZE   (16)

struct _iconv_cache_bucket {
  gchar *key;
  guint32 refcount;
  gboolean used;
  GIConv cd;
};

static GList *iconv_cache_list;
static GHashTable *iconv_cache;
static GHashTable *iconv_open_hash;
static guint iconv_cache_size = 0;
G_LOCK_DEFINE_STATIC (iconv_cache_lock);

/* caller *must* hold the iconv_cache_lock */
static void
iconv_cache_init (void)
{
  static gboolean initialized = FALSE;
  
  if (initialized)
    return;
  
  iconv_cache_list = NULL;
  iconv_cache = g_hash_table_new (g_str_hash, g_str_equal);
  iconv_open_hash = g_hash_table_new (g_direct_hash, g_direct_equal);
  
  initialized = TRUE;
}


/**
 * iconv_cache_bucket_new:
 * @key: cache key
 * @cd: iconv descriptor
 *
 * Creates a new cache bucket, inserts it into the cache and
 * increments the cache size.
 *
 * Returns a pointer to the newly allocated cache bucket.
 **/
static struct _iconv_cache_bucket *
iconv_cache_bucket_new (const gchar *key, GIConv cd)
{
  struct _iconv_cache_bucket *bucket;
  
  bucket = g_new (struct _iconv_cache_bucket, 1);
  bucket->key = g_strdup (key);
  bucket->refcount = 1;
  bucket->used = TRUE;
  bucket->cd = cd;
  
  g_hash_table_insert (iconv_cache, bucket->key, bucket);
  
  /* FIXME: if we sorted the list so items with few refcounts were
     first, then we could expire them faster in iconv_cache_expire_unused () */
  iconv_cache_list = g_list_prepend (iconv_cache_list, bucket);
  
  iconv_cache_size++;
  
  return bucket;
}


/**
 * iconv_cache_bucket_expire:
 * @node: cache bucket's node
 * @bucket: cache bucket
 *
 * Expires a single cache bucket @bucket. This should only ever be
 * called on a bucket that currently has no used iconv descriptors
 * open.
 *
 * @node is not a required argument. If @node is not supplied, we
 * search for it ourselves.
 **/
static void
iconv_cache_bucket_expire (GList *node, struct _iconv_cache_bucket *bucket)
{
  g_hash_table_remove (iconv_cache, bucket->key);
  
  if (node == NULL)
    node = g_list_find (iconv_cache_list, bucket);
  
  g_assert (node != NULL);
  
  if (node->prev)
    {
      node->prev->next = node->next;
      if (node->next)
        node->next->prev = node->prev;
    }
  else
    {
      iconv_cache_list = node->next;
      if (node->next)
        node->next->prev = NULL;
    }
  
  g_list_free_1 (node);
  
  g_free (bucket->key);
  g_iconv_close (bucket->cd);
  g_free (bucket);
  
  iconv_cache_size--;
}


/**
 * iconv_cache_expire_unused:
 *
 * Expires as many unused cache buckets as it needs to in order to get
 * the total number of buckets < ICONV_CACHE_SIZE.
 **/
static void
iconv_cache_expire_unused (void)
{
  struct _iconv_cache_bucket *bucket;
  GList *node, *next;
  
  node = iconv_cache_list;
  while (node && iconv_cache_size >= ICONV_CACHE_SIZE)
    {
      next = node->next;
      
      bucket = node->data;
      if (bucket->refcount == 0)
        iconv_cache_bucket_expire (node, bucket);
      
      node = next;
    }
}

static GIConv
open_converter (const gchar *to_codeset,
		const gchar *from_codeset,
		GError     **error)
{
  struct _iconv_cache_bucket *bucket;
  gchar *key;
  GIConv cd;
  
  /* create our key */
  key = g_alloca (strlen (from_codeset) + strlen (to_codeset) + 2);
  _g_sprintf (key, "%s:%s", from_codeset, to_codeset);
  
  G_LOCK (iconv_cache_lock);
  
  /* make sure the cache has been initialized */
  iconv_cache_init ();
  
  bucket = g_hash_table_lookup (iconv_cache, key);
  if (bucket)
    {
      if (bucket->used)
        {
          cd = g_iconv_open (to_codeset, from_codeset);
          if (cd == (GIConv) -1)
            goto error;
        }
      else
        {
	  /* Apparently iconv on Solaris <= 7 segfaults if you pass in
	   * NULL for anything but inbuf; work around that. (NULL outbuf
	   * or NULL *outbuf is allowed by Unix98.)
	   */
	  gsize inbytes_left = 0;
	  gchar *outbuf = NULL;
	  gsize outbytes_left = 0;
		
          cd = bucket->cd;
          bucket->used = TRUE;
          
          /* reset the descriptor */
          g_iconv (cd, NULL, &inbytes_left, &outbuf, &outbytes_left);
        }
      
      bucket->refcount++;
    }
  else
    {
      cd = g_iconv_open (to_codeset, from_codeset);
      if (cd == (GIConv) -1)
        goto error;
      
      iconv_cache_expire_unused ();
      
      bucket = iconv_cache_bucket_new (key, cd);
    }
  
  g_hash_table_insert (iconv_open_hash, cd, bucket->key);
  
  G_UNLOCK (iconv_cache_lock);
  
  return cd;
  
 error:
  
  G_UNLOCK (iconv_cache_lock);
  
  /* Something went wrong.  */
  if (errno == EINVAL)
    g_set_error (error, G_CONVERT_ERROR, G_CONVERT_ERROR_NO_CONVERSION,
		 _("Conversion from character set '%s' to '%s' is not supported"),
		 from_codeset, to_codeset);
  else
    g_set_error (error, G_CONVERT_ERROR, G_CONVERT_ERROR_FAILED,
		 _("Could not open converter from '%s' to '%s': %s"),
		 from_codeset, to_codeset, g_strerror (errno));
  
  return cd;
}

static int
close_converter (GIConv converter)
{
  struct _iconv_cache_bucket *bucket;
  const gchar *key;
  GIConv cd;
  
  cd = converter;
  
  if (cd == (GIConv) -1)
    return 0;
  
  G_LOCK (iconv_cache_lock);
  
  key = g_hash_table_lookup (iconv_open_hash, cd);
  if (key)
    {
      g_hash_table_remove (iconv_open_hash, cd);
      
      bucket = g_hash_table_lookup (iconv_cache, key);
      g_assert (bucket);
      
      bucket->refcount--;
      
      if (cd == bucket->cd)
        bucket->used = FALSE;
      else
        g_iconv_close (cd);
      
      if (!bucket->refcount && iconv_cache_size > ICONV_CACHE_SIZE)
        {
          /* expire this cache bucket */
          iconv_cache_bucket_expire (NULL, bucket);
        }
    }
  else
    {
      G_UNLOCK (iconv_cache_lock);
      
      g_warning ("This iconv context wasn't opened using open_converter");
      
      return g_iconv_close (converter);
    }
  
  G_UNLOCK (iconv_cache_lock);
  
  return 0;
}


/**
 * g_convert:
 * @str:           the string to convert
 * @len:           the length of the string
 * @to_codeset:    name of character set into which to convert @str
 * @from_codeset:  character set of @str.
 * @bytes_read:    location to store the number of bytes in the
 *                 input string that were successfully converted, or %NULL.
 *                 Even if the conversion was successful, this may be 
 *                 less than @len if there were partial characters
 *                 at the end of the input. If the error
 *                 #G_CONVERT_ERROR_ILLEGAL_SEQUENCE occurs, the value
 *                 stored will the byte offset after the last valid
 *                 input sequence.
 * @bytes_written: the number of bytes stored in the output buffer (not 
 *                 including the terminating nul).
 * @error:         location to store the error occuring, or %NULL to ignore
 *                 errors. Any of the errors in #GConvertError may occur.
 *
 * Converts a string from one character set to another.
 *
 * Return value: If the conversion was successful, a newly allocated
 *               nul-terminated string, which must be freed with
 *               g_free(). Otherwise %NULL and @error will be set.
 **/
gchar*
g_convert (const gchar *str,
           gssize       len,  
           const gchar *to_codeset,
           const gchar *from_codeset,
           gsize       *bytes_read, 
	   gsize       *bytes_written, 
	   GError     **error)
{
  gchar *res;
  GIConv cd;
  
  g_return_val_if_fail (str != NULL, NULL);
  g_return_val_if_fail (to_codeset != NULL, NULL);
  g_return_val_if_fail (from_codeset != NULL, NULL);
  
  cd = open_converter (to_codeset, from_codeset, error);

  if (cd == (GIConv) -1)
    {
      if (bytes_read)
        *bytes_read = 0;
      
      if (bytes_written)
        *bytes_written = 0;
      
      return NULL;
    }

  res = g_convert_with_iconv (str, len, cd,
			      bytes_read, bytes_written,
			      error);
  
  close_converter (cd);

  return res;
}

/**
 * g_convert_with_iconv:
 * @str:           the string to convert
 * @len:           the length of the string
 * @converter:     conversion descriptor from g_iconv_open()
 * @bytes_read:    location to store the number of bytes in the
 *                 input string that were successfully converted, or %NULL.
 *                 Even if the conversion was successful, this may be 
 *                 less than @len if there were partial characters
 *                 at the end of the input. If the error
 *                 #G_CONVERT_ERROR_ILLEGAL_SEQUENCE occurs, the value
 *                 stored will the byte offset after the last valid
 *                 input sequence.
 * @bytes_written: the number of bytes stored in the output buffer (not 
 *                 including the terminating nul).
 * @error:         location to store the error occuring, or %NULL to ignore
 *                 errors. Any of the errors in #GConvertError may occur.
 *
 * Converts a string from one character set to another.
 *
 * Return value: If the conversion was successful, a newly allocated
 *               nul-terminated string, which must be freed with
 *               g_free(). Otherwise %NULL and @error will be set.
 **/
gchar*
g_convert_with_iconv (const gchar *str,
		      gssize       len,
		      GIConv       converter,
		      gsize       *bytes_read, 
		      gsize       *bytes_written, 
		      GError     **error)
{
  gchar *dest;
  gchar *outp;
  const gchar *p;
  gsize inbytes_remaining;
  gsize outbytes_remaining;
  gsize err;
  gsize outbuf_size;
  gboolean have_error = FALSE;
  
  g_return_val_if_fail (str != NULL, NULL);
  g_return_val_if_fail (converter != (GIConv) -1, NULL);
     
  if (len < 0)
    len = strlen (str);

  p = str;
  inbytes_remaining = len;
  outbuf_size = len + 1; /* + 1 for nul in case len == 1 */
  
  outbytes_remaining = outbuf_size - 1; /* -1 for nul */
  outp = dest = g_malloc (outbuf_size);

 again:
  
  err = g_iconv (converter, (char **)&p, &inbytes_remaining, &outp, &outbytes_remaining);

  if (err == (size_t) -1)
    {
      switch (errno)
	{
	case EINVAL:
	  /* Incomplete text, do not report an error */
	  break;
	case E2BIG:
	  {
	    size_t used = outp - dest;

	    outbuf_size *= 2;
	    dest = g_realloc (dest, outbuf_size);
		
	    outp = dest + used;
	    outbytes_remaining = outbuf_size - used - 1; /* -1 for nul */

	    goto again;
	  }
	case EILSEQ:
	  g_set_error (error, G_CONVERT_ERROR, G_CONVERT_ERROR_ILLEGAL_SEQUENCE,
		       _("Invalid byte sequence in conversion input"));
	  have_error = TRUE;
	  break;
	default:
	  g_set_error (error, G_CONVERT_ERROR, G_CONVERT_ERROR_FAILED,
		       _("Error during conversion: %s"),
		       g_strerror (errno));
	  have_error = TRUE;
	  break;
	}
    }

  *outp = '\0';
  
  if (bytes_read)
    *bytes_read = p - str;
  else
    {
      if ((p - str) != len) 
	{
          if (!have_error)
            {
              g_set_error (error, G_CONVERT_ERROR, G_CONVERT_ERROR_PARTIAL_INPUT,
                           _("Partial character sequence at end of input"));
              have_error = TRUE;
            }
	}
    }

  if (bytes_written)
    *bytes_written = outp - dest;	/* Doesn't include '\0' */

  if (have_error)
    {
      g_free (dest);
      return NULL;
    }
  else
    return dest;
}

/**
 * g_convert_with_fallback:
 * @str:          the string to convert
 * @len:          the length of the string
 * @to_codeset:   name of character set into which to convert @str
 * @from_codeset: character set of @str.
 * @fallback:     UTF-8 string to use in place of character not
 *                present in the target encoding. (This must be
 *                in the target encoding), if %NULL, characters
 *                not in the target encoding will be represented
 *                as Unicode escapes \uxxxx or \Uxxxxyyyy.
 * @bytes_read:   location to store the number of bytes in the
 *                input string that were successfully converted, or %NULL.
 *                Even if the conversion was successful, this may be 
 *                less than @len if there were partial characters
 *                at the end of the input.
 * @bytes_written: the number of bytes stored in the output buffer (not 
 *                including the terminating nul).
 * @error:        location to store the error occuring, or %NULL to ignore
 *                errors. Any of the errors in #GConvertError may occur.
 *
 * Converts a string from one character set to another, possibly
 * including fallback sequences for characters not representable
 * in the output. Note that it is not guaranteed that the specification
 * for the fallback sequences in @fallback will be honored. Some
 * systems may do a approximate conversion from @from_codeset
 * to @to_codeset in their iconv() functions, 
 * in which case GLib will simply return that approximate conversion.
 *
 * Return value: If the conversion was successful, a newly allocated
 *               nul-terminated string, which must be freed with
 *               g_free(). Otherwise %NULL and @error will be set.
 **/
gchar*
g_convert_with_fallback (const gchar *str,
			 gssize       len,    
			 const gchar *to_codeset,
			 const gchar *from_codeset,
			 gchar       *fallback,
			 gsize       *bytes_read,
			 gsize       *bytes_written,
			 GError     **error)
{
  gchar *utf8;
  gchar *dest;
  gchar *outp;
  const gchar *insert_str = NULL;
  const gchar *p;
  gsize inbytes_remaining;   
  const gchar *save_p = NULL;
  gsize save_inbytes = 0;
  gsize outbytes_remaining; 
  gsize err;
  GIConv cd;
  gsize outbuf_size;
  gboolean have_error = FALSE;
  gboolean done = FALSE;

  GError *local_error = NULL;
  
  g_return_val_if_fail (str != NULL, NULL);
  g_return_val_if_fail (to_codeset != NULL, NULL);
  g_return_val_if_fail (from_codeset != NULL, NULL);
     
  if (len < 0)
    len = strlen (str);
  
  /* Try an exact conversion; we only proceed if this fails
   * due to an illegal sequence in the input string.
   */
  dest = g_convert (str, len, to_codeset, from_codeset, 
		    bytes_read, bytes_written, &local_error);
  if (!local_error)
    return dest;

  if (!g_error_matches (local_error, G_CONVERT_ERROR, G_CONVERT_ERROR_ILLEGAL_SEQUENCE))
    {
      g_propagate_error (error, local_error);
      return NULL;
    }
  else
    g_error_free (local_error);

  local_error = NULL;
  
  /* No go; to proceed, we need a converter from "UTF-8" to
   * to_codeset, and the string as UTF-8.
   */
  cd = open_converter (to_codeset, "UTF-8", error);
  if (cd == (GIConv) -1)
    {
      if (bytes_read)
        *bytes_read = 0;
      
      if (bytes_written)
        *bytes_written = 0;
      
      return NULL;
    }

  utf8 = g_convert (str, len, "UTF-8", from_codeset, 
		    bytes_read, &inbytes_remaining, error);
  if (!utf8)
    {
      close_converter (cd);
      if (bytes_written)
        *bytes_written = 0;
      return NULL;
    }

  /* Now the heart of the code. We loop through the UTF-8 string, and
   * whenever we hit an offending character, we form fallback, convert
   * the fallback to the target codeset, and then go back to
   * converting the original string after finishing with the fallback.
   *
   * The variables save_p and save_inbytes store the input state
   * for the original string while we are converting the fallback
   */
  p = utf8;

  outbuf_size = len + 1; /* + 1 for nul in case len == 1 */
  outbytes_remaining = outbuf_size - 1; /* -1 for nul */
  outp = dest = g_malloc (outbuf_size);

  while (!done && !have_error)
    {
      size_t inbytes_tmp = inbytes_remaining;
      err = g_iconv (cd, (char **)&p, &inbytes_tmp, &outp, &outbytes_remaining);
      inbytes_remaining = inbytes_tmp;

      if (err == (size_t) -1)
	{
	  switch (errno)
	    {
	    case EINVAL:
	      g_assert_not_reached();
	      break;
	    case E2BIG:
	      {
		size_t used = outp - dest;

		outbuf_size *= 2;
		dest = g_realloc (dest, outbuf_size);
		
		outp = dest + used;
		outbytes_remaining = outbuf_size - used - 1; /* -1 for nul */
		
		break;
	      }
	    case EILSEQ:
	      if (save_p)
		{
		  /* Error converting fallback string - fatal
		   */
		  g_set_error (error, G_CONVERT_ERROR, G_CONVERT_ERROR_ILLEGAL_SEQUENCE,
			       _("Cannot convert fallback '%s' to codeset '%s'"),
			       insert_str, to_codeset);
		  have_error = TRUE;
		  break;
		}
	      else
		{
		  if (!fallback)
		    { 
		      gunichar ch = g_utf8_get_char (p);
		      insert_str = g_strdup_printf (ch < 0x10000 ? "\\u%04x" : "\\U%08x",
						    ch);
		    }
		  else
		    insert_str = fallback;
		  
		  save_p = g_utf8_next_char (p);
		  save_inbytes = inbytes_remaining - (save_p - p);
		  p = insert_str;
		  inbytes_remaining = strlen (p);
		}
	      break;
	    default:
	      g_set_error (error, G_CONVERT_ERROR, G_CONVERT_ERROR_FAILED,
			   _("Error during conversion: %s"),
			   g_strerror (errno));
	      have_error = TRUE;
	      break;
	    }
	}
      else
	{
	  if (save_p)
	    {
	      if (!fallback)
		g_free ((gchar *)insert_str);
	      p = save_p;
	      inbytes_remaining = save_inbytes;
	      save_p = NULL;
	    }
	  else
	    done = TRUE;
	}
    }

  /* Cleanup
   */
  *outp = '\0';
  
  close_converter (cd);

  if (bytes_written)
    *bytes_written = outp - dest;	/* Doesn't include '\0' */

  g_free (utf8);

  if (have_error)
    {
      if (save_p && !fallback)
	g_free ((gchar *)insert_str);
      g_free (dest);
      return NULL;
    }
  else
    return dest;
}

/*
 * g_locale_to_utf8
 *
 * 
 */

static gchar *
strdup_len (const gchar *string,
	    gssize       len,
	    gsize       *bytes_written,
	    gsize       *bytes_read,
	    GError      **error)
	 
{
  gsize real_len;

  if (!g_utf8_validate (string, len, NULL))
    {
      if (bytes_read)
	*bytes_read = 0;
      if (bytes_written)
	*bytes_written = 0;

      g_set_error (error, G_CONVERT_ERROR, G_CONVERT_ERROR_ILLEGAL_SEQUENCE,
		   _("Invalid byte sequence in conversion input"));
      return NULL;
    }
  
  if (len < 0)
    real_len = strlen (string);
  else
    {
      real_len = 0;
      
      while (real_len < len && string[real_len])
	real_len++;
    }
  
  if (bytes_read)
    *bytes_read = real_len;
  if (bytes_written)
    *bytes_written = real_len;

  return g_strndup (string, real_len);
}

/**
 * g_locale_to_utf8:
 * @opsysstring:   a string in the encoding of the current locale
 * @len:           the length of the string, or -1 if the string is
 *                 nul-terminated.
 * @bytes_read:    location to store the number of bytes in the
 *                 input string that were successfully converted, or %NULL.
 *                 Even if the conversion was successful, this may be 
 *                 less than @len if there were partial characters
 *                 at the end of the input. If the error
 *                 #G_CONVERT_ERROR_ILLEGAL_SEQUENCE occurs, the value
 *                 stored will the byte offset after the last valid
 *                 input sequence.
 * @bytes_written: the number of bytes stored in the output buffer (not 
 *                 including the terminating nul).
 * @error:         location to store the error occuring, or %NULL to ignore
 *                 errors. Any of the errors in #GConvertError may occur.
 * 
 * Converts a string which is in the encoding used for strings by
 * the C runtime (usually the same as that used by the operating
 * system) in the current locale into a UTF-8 string.
 * 
 * Return value: The converted string, or %NULL on an error.
 **/
gchar *
g_locale_to_utf8 (const gchar  *opsysstring,
		  gssize        len,            
		  gsize        *bytes_read,    
		  gsize        *bytes_written,
		  GError      **error)
{
  const char *charset;

  if (g_get_charset (&charset))
    return strdup_len (opsysstring, len, bytes_read, bytes_written, error);
  else
    return g_convert (opsysstring, len, 
		      "UTF-8", charset, bytes_read, bytes_written, error);
}

/**
 * g_locale_from_utf8:
 * @utf8string:    a UTF-8 encoded string 
 * @len:           the length of the string, or -1 if the string is
 *                 nul-terminated.
 * @bytes_read:    location to store the number of bytes in the
 *                 input string that were successfully converted, or %NULL.
 *                 Even if the conversion was successful, this may be 
 *                 less than @len if there were partial characters
 *                 at the end of the input. If the error
 *                 #G_CONVERT_ERROR_ILLEGAL_SEQUENCE occurs, the value
 *                 stored will the byte offset after the last valid
 *                 input sequence.
 * @bytes_written: the number of bytes stored in the output buffer (not 
 *                 including the terminating nul).
 * @error:         location to store the error occuring, or %NULL to ignore
 *                 errors. Any of the errors in #GConvertError may occur.
 * 
 * Converts a string from UTF-8 to the encoding used for strings by
 * the C runtime (usually the same as that used by the operating
 * system) in the current locale.
 * 
 * Return value: The converted string, or %NULL on an error.
 **/
gchar *
g_locale_from_utf8 (const gchar *utf8string,
		    gssize       len,            
		    gsize       *bytes_read,    
		    gsize       *bytes_written,
		    GError     **error)
{
  const gchar *charset;

  if (g_get_charset (&charset))
    return strdup_len (utf8string, len, bytes_read, bytes_written, error);
  else
    return g_convert (utf8string, len,
		      charset, "UTF-8", bytes_read, bytes_written, error);
}

#ifndef G_PLATFORM_WIN32

typedef struct _GFilenameCharsetCache GFilenameCharsetCache;

struct _GFilenameCharsetCache {
  gboolean is_utf8;
  gchar *charset;
  gchar *filename_charset;
};

static void
filename_charset_cache_free (gpointer data)
{
  GFilenameCharsetCache *cache = data;
  g_free (cache->charset);
  g_free (cache->filename_charset);
  g_free (cache);
}

/*
 * get_filename_charset:
 * @charset: return location for the name of the filename encoding 
 *
 * Determines the character set used for filenames by consulting the 
 * environment variables G_FILENAME_ENCODING and G_BROKEN_FILENAMES. 
 *
 * G_FILENAME_ENCODING may be set to a comma-separated list of character 
 * set names. The special token "@locale" is taken to mean the character set 
 * for the current locale. The first character set from the list is taken 
 * as the filename encoding. 
 * If G_FILENAME_ENCODING is not set, but G_BROKEN_FILENAMES is, the
 * character set of the current locale is taken as the filename encoding.
 *
 * The returned @charset belongs to GLib and must not be freed.
 * 
 * Return value: %TRUE if the charset used for filename is UTF-8.
 */
static gboolean
get_filename_charset (const gchar **filename_charset)
{
  static GStaticPrivate cache_private = G_STATIC_PRIVATE_INIT;
  GFilenameCharsetCache *cache = g_static_private_get (&cache_private);
  const gchar *charset;
  
  if (!cache)
    {
      cache = g_new0 (GFilenameCharsetCache, 1);
      g_static_private_set (&cache_private, cache, filename_charset_cache_free);
    }

  g_get_charset (&charset);

  if (!(cache->charset && strcmp (cache->charset, charset) == 0))
    {
      const gchar *new_charset;
      gchar *p, *q;

      g_free (cache->charset);
      g_free (cache->filename_charset);
      cache->charset = g_strdup (charset);
      
      p = getenv ("G_FILENAME_ENCODING");
      if (p != NULL) 
	{
	  q = strchr (p, ',');
	  if (!q) 
	    q = p + strlen (p);

	  if (strncmp ("@locale", p, q - p) == 0)
	    {
	      cache->is_utf8 = g_get_charset (&new_charset);
	      cache->filename_charset = g_strdup (new_charset);
	    }
	  else
	    {
	      cache->filename_charset = g_strndup (p, q - p);
	      cache->is_utf8 = (strcmp (cache->filename_charset, "UTF-8") == 0);
	    }
	}
      else if (getenv ("G_BROKEN_FILENAMES") != NULL)
	{
	  cache->is_utf8 = g_get_charset (&new_charset);
	  cache->filename_charset = g_strdup (new_charset);
	}
      else 
	{
	  cache->filename_charset = g_strdup ("UTF-8");
	  cache->is_utf8 = TRUE;
	}
    }

  if (filename_charset)
    *filename_charset = cache->filename_charset;

  return cache->is_utf8;
}

#else /* G_PLATFORM_WIN32 */
static gboolean
get_filename_charset (const gchar **filename_charset) 
{
  g_get_charset (filename_charset);
  return FALSE;
}
#endif /* G_PLATFORM_WIN32 */

/* This is called from g_thread_init(). It's used to
 * initialize some static data in a threadsafe way.
 */
void 
_g_convert_thread_init (void)
{
  const gchar *dummy;
  (void) get_filename_charset (&dummy);
}

/**
 * g_filename_to_utf8:
 * @opsysstring:   a string in the encoding for filenames
 * @len:           the length of the string, or -1 if the string is
 *                 nul-terminated.
 * @bytes_read:    location to store the number of bytes in the
 *                 input string that were successfully converted, or %NULL.
 *                 Even if the conversion was successful, this may be 
 *                 less than @len if there were partial characters
 *                 at the end of the input. If the error
 *                 #G_CONVERT_ERROR_ILLEGAL_SEQUENCE occurs, the value
 *                 stored will the byte offset after the last valid
 *                 input sequence.
 * @bytes_written: the number of bytes stored in the output buffer (not 
 *                 including the terminating nul).
 * @error:         location to store the error occuring, or %NULL to ignore
 *                 errors. Any of the errors in #GConvertError may occur.
 * 
 * Converts a string which is in the encoding used for filenames
 * into a UTF-8 string.
 * 
 * Return value: The converted string, or %NULL on an error.
 **/
gchar*
g_filename_to_utf8 (const gchar *opsysstring, 
		    gssize       len,           
		    gsize       *bytes_read,   
		    gsize       *bytes_written,
		    GError     **error)
{
  const gchar *charset;

  if (get_filename_charset (&charset))
    return strdup_len (opsysstring, len, bytes_read, bytes_written, error);
  else
    return g_convert (opsysstring, len, 
		      "UTF-8", charset, bytes_read, bytes_written, error);
}

/**
 * g_filename_from_utf8:
 * @utf8string:    a UTF-8 encoded string.
 * @len:           the length of the string, or -1 if the string is
 *                 nul-terminated.
 * @bytes_read:    location to store the number of bytes in the
 *                 input string that were successfully converted, or %NULL.
 *                 Even if the conversion was successful, this may be 
 *                 less than @len if there were partial characters
 *                 at the end of the input. If the error
 *                 #G_CONVERT_ERROR_ILLEGAL_SEQUENCE occurs, the value
 *                 stored will the byte offset after the last valid
 *                 input sequence.
 * @bytes_written: the number of bytes stored in the output buffer (not 
 *                 including the terminating nul).
 * @error:         location to store the error occuring, or %NULL to ignore
 *                 errors. Any of the errors in #GConvertError may occur.
 * 
 * Converts a string from UTF-8 to the encoding used for filenames.
 * 
 * Return value: The converted string, or %NULL on an error.
 **/
gchar*
g_filename_from_utf8 (const gchar *utf8string,
		      gssize       len,            
		      gsize       *bytes_read,    
		      gsize       *bytes_written,
		      GError     **error)
{
  const gchar *charset;

  if (get_filename_charset (&charset))
    return strdup_len (utf8string, len, bytes_read, bytes_written, error);
  else
    return g_convert (utf8string, len,
		      charset, "UTF-8", bytes_read, bytes_written, error);
}

/* Test of haystack has the needle prefix, comparing case
 * insensitive. haystack may be UTF-8, but needle must
 * contain only ascii. */
static gboolean
has_case_prefix (const gchar *haystack, const gchar *needle)
{
  const gchar *h, *n;
  
  /* Eat one character at a time. */
  h = haystack;
  n = needle;

  while (*n && *h &&
	 g_ascii_tolower (*n) == g_ascii_tolower (*h))
    {
      n++;
      h++;
    }
  
  return *n == '\0';
}

typedef enum {
  UNSAFE_ALL        = 0x1,  /* Escape all unsafe characters   */
  UNSAFE_ALLOW_PLUS = 0x2,  /* Allows '+'  */
  UNSAFE_PATH       = 0x8,  /* Allows '/', '&', '=', ':', '@', '+', '$' and ',' */
  UNSAFE_HOST       = 0x10, /* Allows '/' and ':' and '@' */
  UNSAFE_SLASHES    = 0x20  /* Allows all characters except for '/' and '%' */
} UnsafeCharacterSet;

static const guchar acceptable[96] = {
  /* A table of the ASCII chars from space (32) to DEL (127) */
  /*      !    "    #    $    %    &    '    (    )    *    +    ,    -    .    / */ 
  0x00,0x3F,0x20,0x20,0x28,0x00,0x2C,0x3F,0x3F,0x3F,0x3F,0x2A,0x28,0x3F,0x3F,0x1C,
  /* 0    1    2    3    4    5    6    7    8    9    :    ;    <    =    >    ? */
  0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x38,0x20,0x20,0x2C,0x20,0x20,
  /* @    A    B    C    D    E    F    G    H    I    J    K    L    M    N    O */
  0x38,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,
  /* P    Q    R    S    T    U    V    W    X    Y    Z    [    \    ]    ^    _ */
  0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x20,0x20,0x20,0x20,0x3F,
  /* `    a    b    c    d    e    f    g    h    i    j    k    l    m    n    o */
  0x20,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,
  /* p    q    r    s    t    u    v    w    x    y    z    {    |    }    ~  DEL */
  0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x20,0x20,0x20,0x3F,0x20
};

static const gchar hex[16] = "0123456789ABCDEF";

/* Note: This escape function works on file: URIs, but if you want to
 * escape something else, please read RFC-2396 */
static gchar *
g_escape_uri_string (const gchar *string, 
		     UnsafeCharacterSet mask)
{
#define ACCEPTABLE(a) ((a)>=32 && (a)<128 && (acceptable[(a)-32] & use_mask))

  const gchar *p;
  gchar *q;
  gchar *result;
  int c;
  gint unacceptable;
  UnsafeCharacterSet use_mask;
  
  g_return_val_if_fail (mask == UNSAFE_ALL
			|| mask == UNSAFE_ALLOW_PLUS
			|| mask == UNSAFE_PATH
			|| mask == UNSAFE_HOST
			|| mask == UNSAFE_SLASHES, NULL);
  
  unacceptable = 0;
  use_mask = mask;
  for (p = string; *p != '\0'; p++)
    {
      c = (guchar) *p;
      if (!ACCEPTABLE (c)) 
	unacceptable++;
    }
  
  result = g_malloc (p - string + unacceptable * 2 + 1);
  
  use_mask = mask;
  for (q = result, p = string; *p != '\0'; p++)
    {
      c = (guchar) *p;
      
      if (!ACCEPTABLE (c))
	{
	  *q++ = '%'; /* means hex coming */
	  *q++ = hex[c >> 4];
	  *q++ = hex[c & 15];
	}
      else
	*q++ = *p;
    }
  
  *q = '\0';
  
  return result;
}


static gchar *
g_escape_file_uri (const gchar *hostname,
		   const gchar *pathname)
{
  char *escaped_hostname = NULL;
  char *escaped_path;
  char *res;

#ifdef G_OS_WIN32
  char *p, *backslash;

  /* Turn backslashes into forward slashes. That's what Netscape
   * does, and they are actually more or less equivalent in Windows.
   */
  
  pathname = g_strdup (pathname);
  p = (char *) pathname;
  
  while ((backslash = strchr (p, '\\')) != NULL)
    {
      *backslash = '/';
      p = backslash + 1;
    }
#endif

  if (hostname && *hostname != '\0')
    {
      escaped_hostname = g_escape_uri_string (hostname, UNSAFE_HOST);
    }

  escaped_path = g_escape_uri_string (pathname, UNSAFE_PATH);

  res = g_strconcat ("file://",
		     (escaped_hostname) ? escaped_hostname : "",
		     (*escaped_path != '/') ? "/" : "",
		     escaped_path,
		     NULL);

#ifdef G_OS_WIN32
  g_free ((char *) pathname);
#endif

  g_free (escaped_hostname);
  g_free (escaped_path);
  
  return res;
}

static int
unescape_character (const char *scanner)
{
  int first_digit;
  int second_digit;

  first_digit = g_ascii_xdigit_value (scanner[0]);
  if (first_digit < 0) 
    return -1;
  
  second_digit = g_ascii_xdigit_value (scanner[1]);
  if (second_digit < 0) 
    return -1;
  
  return (first_digit << 4) | second_digit;
}

static gchar *
g_unescape_uri_string (const char *escaped,
		       int         len,
		       const char *illegal_escaped_characters,
		       gboolean    ascii_must_not_be_escaped)
{
  const gchar *in, *in_end;
  gchar *out, *result;
  int c;
  
  if (escaped == NULL)
    return NULL;

  if (len < 0)
    len = strlen (escaped);

  result = g_malloc (len + 1);
  
  out = result;
  for (in = escaped, in_end = escaped + len; in < in_end; in++)
    {
      c = *in;

      if (c == '%')
	{
	  /* catch partial escape sequences past the end of the substring */
	  if (in + 3 > in_end)
	    break;

	  c = unescape_character (in + 1);

	  /* catch bad escape sequences and NUL characters */
	  if (c <= 0)
	    break;

	  /* catch escaped ASCII */
	  if (ascii_must_not_be_escaped && c <= 0x7F)
	    break;

	  /* catch other illegal escaped characters */
	  if (strchr (illegal_escaped_characters, c) != NULL)
	    break;

	  in += 2;
	}

      *out++ = c;
    }
  
  g_assert (out - result <= len);
  *out = '\0';

  if (in != in_end || !g_utf8_validate (result, -1, NULL))
    {
      g_free (result);
      return NULL;
    }

  return result;
}

static gboolean
is_escalphanum (gunichar c)
{
  return c > 0x7F || g_ascii_isalnum (c);
}

static gboolean
is_escalpha (gunichar c)
{
  return c > 0x7F || g_ascii_isalpha (c);
}

/* allows an empty string */
static gboolean
hostname_validate (const char *hostname)
{
  const char *p;
  gunichar c, first_char, last_char;

  p = hostname;
  if (*p == '\0')
    return TRUE;
  do
    {
      /* read in a label */
      c = g_utf8_get_char (p);
      p = g_utf8_next_char (p);
      if (!is_escalphanum (c))
	return FALSE;
      first_char = c;
      do
	{
	  last_char = c;
	  c = g_utf8_get_char (p);
	  p = g_utf8_next_char (p);
	}
      while (is_escalphanum (c) || c == '-');
      if (last_char == '-')
	return FALSE;
      
      /* if that was the last label, check that it was a toplabel */
      if (c == '\0' || (c == '.' && *p == '\0'))
	return is_escalpha (first_char);
    }
  while (c == '.');
  return FALSE;
}

/**
 * g_filename_from_uri:
 * @uri: a uri describing a filename (escaped, encoded in UTF-8).
 * @hostname: Location to store hostname for the URI, or %NULL.
 *            If there is no hostname in the URI, %NULL will be
 *            stored in this location.
 * @error: location to store the error occuring, or %NULL to ignore
 *         errors. Any of the errors in #GConvertError may occur.
 * 
 * Converts an escaped UTF-8 encoded URI to a local filename in the
 * encoding used for filenames. 
 * 
 * Return value: a newly-allocated string holding the resulting
 *               filename, or %NULL on an error.
 **/
gchar *
g_filename_from_uri (const gchar *uri,
		     gchar      **hostname,
		     GError     **error)
{
  const char *path_part;
  const char *host_part;
  char *unescaped_hostname;
  char *result;
  char *filename;
  int offs;
#ifdef G_OS_WIN32
  char *p, *slash;
#endif

  if (hostname)
    *hostname = NULL;

  if (!has_case_prefix (uri, "file:/"))
    {
      g_set_error (error, G_CONVERT_ERROR, G_CONVERT_ERROR_BAD_URI,
		   _("The URI '%s' is not an absolute URI using the file scheme"),
		   uri);
      return NULL;
    }
  
  path_part = uri + strlen ("file:");
  
  if (strchr (path_part, '#') != NULL)
    {
      g_set_error (error, G_CONVERT_ERROR, G_CONVERT_ERROR_BAD_URI,
		   _("The local file URI '%s' may not include a '#'"),
		   uri);
      return NULL;
    }
	
  if (has_case_prefix (path_part, "///")) 
    path_part += 2;
  else if (has_case_prefix (path_part, "//"))
    {
      path_part += 2;
      host_part = path_part;

      path_part = strchr (path_part, '/');

      if (path_part == NULL)
	{
	  g_set_error (error, G_CONVERT_ERROR, G_CONVERT_ERROR_BAD_URI,
		       _("The URI '%s' is invalid"),
		       uri);
	  return NULL;
	}

      unescaped_hostname = g_unescape_uri_string (host_part, path_part - host_part, "", TRUE);

      if (unescaped_hostname == NULL ||
	  !hostname_validate (unescaped_hostname))
	{
	  g_free (unescaped_hostname);
	  g_set_error (error, G_CONVERT_ERROR, G_CONVERT_ERROR_BAD_URI,
		       _("The hostname of the URI '%s' is invalid"),
		       uri);
	  return NULL;
	}
      
      if (hostname)
	*hostname = unescaped_hostname;
      else
	g_free (unescaped_hostname);
    }

  filename = g_unescape_uri_string (path_part, -1, "/", FALSE);

  if (filename == NULL)
    {
      g_set_error (error, G_CONVERT_ERROR, G_CONVERT_ERROR_BAD_URI,
		   _("The URI '%s' contains invalidly escaped characters"),
		   uri);
      return NULL;
    }

  offs = 0;
#ifdef G_OS_WIN32
  /* Drop localhost */
  if (hostname && *hostname != NULL &&
      g_ascii_strcasecmp (*hostname, "localhost") == 0)
    {
      g_free (*hostname);
      *hostname = NULL;
    }

  /* Turn slashes into backslashes, because that's the canonical spelling */
  p = filename;
  while ((slash = strchr (p, '/')) != NULL)
    {
      *slash = '\\';
      p = slash + 1;
    }

  /* Windows URIs with a drive letter can be like "file://host/c:/foo"
   * or "file://host/c|/foo" (some Netscape versions). In those cases, start
   * the filename from the drive letter.
   */
  if (g_ascii_isalpha (filename[1]))
    {
      if (filename[2] == ':')
	offs = 1;
      else if (filename[2] == '|')
	{
	  filename[2] = ':';
	  offs = 1;
	}
    }
#endif
  
  result = g_filename_from_utf8 (filename + offs, -1, NULL, NULL, error);
  g_free (filename);
  
  return result;
}

/**
 * g_filename_to_uri:
 * @filename: an absolute filename specified in the encoding
 *            used for filenames by the operating system.
 * @hostname: A UTF-8 encoded hostname, or %NULL for none.
 * @error: location to store the error occuring, or %NULL to ignore
 *         errors. Any of the errors in #GConvertError may occur.
 * 
 * Converts an absolute filename to an escaped UTF-8 encoded URI.
 * 
 * Return value: a newly-allocated string holding the resulting
 *               URI, or %NULL on an error.
 **/
gchar *
g_filename_to_uri   (const gchar *filename,
		     const gchar *hostname,
		     GError     **error)
{
  char *escaped_uri;
  char *utf8_filename;

  g_return_val_if_fail (filename != NULL, NULL);

  if (!g_path_is_absolute (filename))
    {
      g_set_error (error, G_CONVERT_ERROR, G_CONVERT_ERROR_NOT_ABSOLUTE_PATH,
		   _("The pathname '%s' is not an absolute path"),
		   filename);
      return NULL;
    }

  if (hostname &&
      !(g_utf8_validate (hostname, -1, NULL)
	&& hostname_validate (hostname)))
    {
      g_set_error (error, G_CONVERT_ERROR, G_CONVERT_ERROR_ILLEGAL_SEQUENCE,
		   _("Invalid hostname"));
      return NULL;
    }
  
  utf8_filename = g_filename_to_utf8 (filename, -1, NULL, NULL, error);
  if (utf8_filename == NULL)
    return NULL;
  
#ifdef G_OS_WIN32
  /* Don't use localhost unnecessarily */
  if (hostname && g_ascii_strcasecmp (hostname, "localhost") == 0)
    hostname = NULL;
#endif

  escaped_uri = g_escape_file_uri (hostname,
				   utf8_filename);
  g_free (utf8_filename);
  
  return escaped_uri;
}

