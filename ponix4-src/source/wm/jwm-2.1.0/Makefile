
SYSCONF = /usr/etc
MANDIR = /usr/share/man
VERSION ?= 2.1.0

all:
	cd src ; $(MAKE) all

install: all
	cd src ; $(MAKE) install ; cd ..
	install -d $(SYSCONF)
	install -m 644 example.jwmrc $(SYSCONF)/system.jwmrc
	install -d $(MANDIR)/man1
	install -m 644 jwm.1 $(MANDIR)/man1/jwm.1

depend:
	cd src ; $(MAKE) depend

tarball:
	rm -f ../jwm-$(VERSION).tar.bz2 ;
	rm -fr ../jwm-$(VERSION) ;
	cp -r ../jwm ../jwm-$(VERSION) ;
	(cd ../jwm-$(VERSION) && $(MAKE) distclean) ;
	(cd .. && tar -cf jwm-$(VERSION).tar jwm-$(VERSION));
	rm -fr ../jwm-$(VERSION) ;
	(cd .. && bzip2 jwm-$(VERSION).tar)

clean:
	(cd src && $(MAKE) clean)
	rm -rf doc

distclean: clean
	rm -f *~ config.cache config.log config.status config.h ;
	rm -f Makefile src/Makefile jwm.tardist jwm.1 ;
	rm -f Makefile.bak src/Makefile.bak ;
	rm -fr autom4te.cache ;
	rm -fr `find . \( -name .svn -o -name .gdb_history \) -print` ;

