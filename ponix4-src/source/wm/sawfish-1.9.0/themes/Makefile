# Makefile.in for sawfish's themes
# $Id: Makefile.in,v 1.20 2001/01/20 02:40:29 jsh Exp $
#
# Copyright (C) 1999 John Harper <john@dcs.warwick.ac.uk>
#
# This file is part of sawfish.
#
# sawfish is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.
#
# sawfish is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with sawfish; see the file COPYING.  If not, write to
# the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.

include ../Makedefs

top_builddir=..
top_srcdir=..
srcdir=.

themedir := ${sawfishdir}/themes

# also in lisp/Makefile.in
sawfish_prog = $(rep_LIBTOOL) --mode=execute -dlopen ../src/gradient.la \
		../src/sawfish --batch --no-rc
COMPILE_ENV = SAWFISHLISPDIR=../lisp \
	      SAWFISHEXECDIR=$(top_builddir)/src/.libs \
	      SAWFISHDOCFILE=../DOC \
	      SAWFISH_USER_LISP_DIR=

THEMES := StyleTab absolute-e Crux microGUI mxflat Elberg-tabbed Zami-like candido gradient-tabbed

all :
# only uncompiled themes are loaded for now, so no point doing this
#	for d in $(THEMES); do \
#	  $(COMPILE_ENV) $(sawfish_prog) compiler -f compile-lib-batch $$d; \
#	done

install : all installdirs
	for d in $(THEMES); do \
	  rm -rf $(DESTDIR)$(themedir)/$$d; \
	  for f in $(srcdir)/$$d/*; do \
	    if [ $$f != $(srcdir)/$$d/CVS ]; then \
	      ( cd $(srcdir) && tar czf $$d.tar.gz $$d/* ) ; \
	      $(INSTALL_DATA) $$d.tar.gz $(DESTDIR)$(themedir)/$$d.tar.gz; \
	    fi \
	  done \
	done
	@# Don't use tar for StyleTab. It's not compression, but tar
	@# itself slows in librep.
	cd $(DESTDIR)$(themedir) && tar xf StyleTab.tar.gz && rm StyleTab.tar.gz

installdirs : $(top_srcdir)/mkinstalldirs
	$(SHELL) $< $(DESTDIR)$(themedir)

uninstall :
	for d in $(THEMES); do \
	  rm -rf $(DESTDIR)$(themedir)/$$d; \
	done

clean :
	for d in $(THEMES); do \
	  rm -f $(srcdir)$$d/*.jlc $(srcdir)/$$d/*~; \
	done
	rm -f *.jlc *.jld *~

distclean : clean
	rm -f Makefile

gitclean : distclean
	rm -f *.gz

.PHONY : all lisp install uninstall clean gitclean
