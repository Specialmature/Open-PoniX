%define name directfb
%define version 1.6.0
%define oname DirectFB
%define libname lib%name

Summary:	Hardware graphics acceleration library
Name:		%name
Version:	%version
Release:	1
License:	LGPL
Group:		System/Libraries
Source0:        http://www.directfb.org/download/%{name}/%{oname}-%{version}.tar.gz
URL:		http://www.directfb.org/
BuildRequires:	libpng-devel >= 1.2.0
BuildRequires:	zlib-devel >= 1.1.3
BuildRequires:	libjpeg-devel >= 6b
BuildRequires:	freetype2-devel >= 2.0.2
BuildRoot:	%{_tmppath}/%{name}-%{version}

%description
%oname - A hardware-accelerated graphics library on top of the Linux frame buffer device.

%package -n %libname
Summary:        Shared library part of %oname
Group:		System/Libraries

%description -n %libname
%oname - A hardware-accelerated graphics library on top of the Linux frame buffer device.

%oname is a thin library that provides developers with hardware graphics
acceleration, input device handling and abstraction, an integrated windowing
system with support for translucent windows and multiple display layers on top
of the Linux frame buffer device. It is a complete hardware abstraction layer
with software fallbacks for every graphics operation that is not supported by
the underlying hardware.

%package -n %libname-devel
Group:		Development/C
Summary:	Header files for compiling %oname applications
Requires:	%{libname} = %{version}-%release
Provides:	lib%name-devel = %version-%release
Provides:	%oname-devel = %version-%release

%description -n %libname-devel
%oname header files needed for building applications based on %oname. 

%package doc
Summary:	%oname documentation
Group:		Development/Other

%description doc
%oname documentation in html format.

%prep
%setup  -q -n %oname-%version

%build
%configure \
        --enable-fbdev \
	--disable-maintainer-mode \
	--enable-shared \
	--disable-fast-install \
	--disable-debug \
	--program-transform-name=""  # is this hack needed?

%make

%install
rm -rf $RPM_BUILD_ROOT
%makeinstall_std

%clean
rm -rf $RPM_BUILD_ROOT

%post -n %libname -p /sbin/ldconfig
%postun -n %libname -p /sbin/ldconfig

%files -n %libname
%defattr(644,root,root,755)
%doc README* AUTHORS ChangeLog NEWS TODO
%attr(755,root,root) %{_libdir}/lib*.so.*
%{_libdir}/directfb-%version
%{_datadir}/directfb-%version
%{_mandir}/man5/*directfbrc.5*

%files -n %libname-devel
%defattr(644,root,root,755)
%attr(755,root,root) %{_bindir}/*directfb-config
%attr(755,root,root) %{_bindir}/*directfb-csource
%attr(755,root,root) %{_bindir}/*dfbg
%{_includedir}/directfb
%{_includedir}/directfb-internal
%{_mandir}/man1/*directfb-csource.1*
%{_mandir}/man1/*dfbg.1*
%{_libdir}/pkgconfig/*
%{_libdir}/*.la
%{_libdir}/*.so

%files doc
%defattr(644,root,root,755)
%doc docs/html/*

%changelog
* Mon Jan 13 2003 Sven Neumann <neo@directfb.org> 0.9.16
- removed reference to avifile
- added rules for dfbg and its man-page

%changelog
* Sun Oct 27 2002 Sven Neumann <neo@directfb.org> 0.9.14
- added this file as directfb.spec.in to the DirectFB source tree
- moved directfbrc manpage to the main package

* Fri Aug 23 2002 G�tz Waschk <waschk@linux-mandrake.com> 0.9.13-1mdk
- add directfb-csource and man page
- 0.9.13

* Thu Jul 11 2002 G�tz Waschk <waschk@linux-mandrake.com> 0.9.12-1mdk
- initial package based on PLD effort
