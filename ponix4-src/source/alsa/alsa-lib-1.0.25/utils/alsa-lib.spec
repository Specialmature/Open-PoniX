%define ver      1.0.25
%define rel      1

Summary: Advanced Linux Sound Architecture (ALSA) - Library
Name: alsa-lib
Version: %ver
Release: %rel
License: LGPL
Group: System/Libraries
Source: ftp://ftp.alsa-project.org/pub/lib/alsa-lib-%{ver}.tar.bz2
BuildRoot: %{_tmppath}/%{name}-%{version}-root
URL: http://www.alsa-project.org

%description

Advanced Linux Sound Architecture (ALSA) - Library

%package -n alsa-lib-devel
Summary: ALSA Libraries Development Files
Group: Development/Libraries
Requires: %{name} = %{version}-%{release}

%description -n alsa-lib-devel
Development files for building applications which use the ALSA libraries.

%changelog
* Sat Feb 22 2003 Ronny V. Vindenes <sublett@dc-s.com>
- split alsa-lib into alsa-lib and alsa-lib-devel
- changed which files are installed (now includes alsa.pc)
- use standard rpm macros for build and install
- changed BuildRoot from /var/tmp to %{_tmppath}

* Tue Nov 20 2001 Jaroslav Kysela <perex@perex.cz>

- changed BuildRoot from /tmp to /var/tmp
- use the standard RPM macros for prefix and paths
- added DESTDIR for make install

* Sun Nov 11 2001 Miroslav Benes <mbenes@tenez.cz>

- dangerous command "rpm -rf $RPM_BUILD_ROOT" checks $RPM_BUILD_ROOT variable
- unset key "Docdir" - on some new systems are documentation in /usr/share/doc

* Mon May 28 1998 Helge Jensen <slog@slog.dk>

- Made SPEC file

%prep
%setup
%build
%configure
make

%install
[ "$RPM_BUILD_ROOT" != "/" ] && rm -rf $RPM_BUILD_ROOT
%makeinstall

%clean
[ "$RPM_BUILD_ROOT" != "/" ] && rm -rf $RPM_BUILD_ROOT

%files
%defattr(-, root, root)
%{_bindir}/*
%{_libdir}/*.so.*
%{_datadir}/alsa
%doc doc/*.txt

%files -n alsa-lib-devel
%defattr(-,root,root)
%{_includedir}/alsa
%{_includedir}/sys/*
%{_libdir}/*.la
%{_libdir}/*.so
%{_datadir}/aclocal/*
%{_libdir}/pkgconfig/*
