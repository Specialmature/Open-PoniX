/*
 * Copyright © 2013 Keith Packard
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting documentation, and
 * that the name of the copyright holders not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "xshmfenceint.h"

/**
 * xshmfence_alloc_shm:
 *
 * Allocates a shared memory object large enough to hold a single
 * fence.
 *
 * Return value: the file descriptor of the object, or -1 on failure
 * (in which case, errno will be set as appropriate).
 **/
int
xshmfence_alloc_shm(void)
{
	char	template[] = SHMDIR "/shmfd-XXXXXX";
	int	fd;

#ifdef O_TMPFILE
	fd = open(SHMDIR, O_TMPFILE|O_RDWR|O_CLOEXEC|O_EXCL, 0666);
	if (fd < 0)
#endif
        {
            fd = mkstemp(template);
            if (fd < 0)
		return fd;
            unlink(template);
        }
	ftruncate(fd, sizeof (struct xshmfence));
        xshmfence_init(fd);
	return fd;
}

/**
 * xshmfence_map_shm:
 *
 * Map a shared memory fence referenced by @fd.
 *
 * Return value: the fence or NULL (in which case, errno will be set
 * as appropriate).
 **/
struct xshmfence *
xshmfence_map_shm(int fd)
{
	struct xshmfence *addr;
	addr = mmap (NULL, sizeof (struct xshmfence) , PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if (addr == MAP_FAILED) {
		close (fd);
		return 0;
	}
	return addr;
}

/**
 * xshmfence_unmap_shm:
 *
 * Unap a shared memory fence @f.
 **/
void
xshmfence_unmap_shm(struct xshmfence *f)
{
        munmap(f, sizeof (struct xshmfence));
}
