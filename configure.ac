dnl 
AC_INIT([etangocards], [0.0.2], [abrahanfer@gmail.com])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([-Wall -Werror])
IT_PROG_INTLTOOL([0.35.0])

GETTEXT_PACKAGE=etangocards
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED([GETTEXT_PACKAGE], ["$GETTEXT_PACKAGE"],
                   [The domain to use with gettext])
AM_GLIB_GNU_GETTEXT

PROGRAMNAME_LOCALEDIR=[${datadir}/locale]
AC_SUBST(PROGRAMNAME_LOCALEDIR)

GNOME_COMMON_INIT
GNOME_MAINTAINER_MODE_DEFINES
GNOME_COMPILE_WARNINGS

dnl Checking for libxml++-2.6
PKG_CHECK_MODULES(LIBXMLPP, libxml++-2.6 >= 2.10.0)
AC_SUBST(LIBXMLPP_CFLAGS, [`pkg-config --cflags libxml++-2.6`])
AC_SUBST(LIBXMLPP_LIBS, [`pkg-config --libs libxml++-2.6`])
dnl Checking for gtkmm-2.4
PKG_CHECK_MODULES(GTKMM, gtkmm-2.4 >= 2.8.0)
AC_SUBST(GTKMM_CFLAGS, [`pkg-config --cflags gtkmm-2.4`])
AC_SUBST(GTKMM_LIBS, [`pkg-config --libs gtkmm-2.4`])
dnl Checking for libbonobo-2.0
PKG_CHECK_MODULES(LIBBONOBO, libbonobo-2.0 >= 2.22.0)
AC_SUBST(LIBBONOBO_CFLAGS, [`pkg-config --cflags libbonobo-2.0`])
AC_SUBST(LIBBONOBO_LIBS, [`pkg-config --libs libbonobo-2.0`])
dnl Checking for libpanelapplet-2.6
PKG_CHECK_MODULES(LIBPANELAPPLETMM, libpanelappletmm-2.6 >= 2.22.0)
AC_SUBST(LIBPANELAPPLETMM_CFLAGS, [`pkg-config --cflags libpanelappletmm-2.6`])
AC_SUBST(LIBPANELAPPLETMM_LIBS, [`pkg-config --libs libpanelappletmm-2.6`])

AC_PROG_CXX
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SRCDIR([src])

AM_MAINTAINER_MODE

AC_CONFIG_FILES([ 
	po/Makefile.in
	Makefile
	src/Makefile
	])
AC_OUTPUT