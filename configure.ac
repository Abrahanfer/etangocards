dnl 
AC_INIT([etangocards], [0.0.1], [abrahanfer@gmail.com])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([-Wall -Werror])
dnl Checking for libxml++2.6
PKG_CHECK_MODULES(LIBXMLPP, libxml++-2.6 >= 2.10.0)
AC_SUBST(LIBXMLPP_CFLAGS, [`pkg-config --cflags libxml++-2.6`])
AC_SUBST(LIBXMLPP_LIBS, [`pkg-config --libs libxml++-2.6`])
dnl Checking for gtkmm2.4
PKG_CHECK_MODULES(GTKMM, gtkmm-2.4 >= 2.8.0)
AC_SUBST(GTKMM_CFLAGS, [`pkg-config --cflags gtkmm-2.4`])
AC_SUBST(GTKMM_LIBS, [`pkg-config --libs gtkmm-2.4`])
dnl Checking for libbonobo-2.0
dnl PKG_CHECK_MODULES(GTKMM, gtkmm-2.4 >= 2.8.0)
AC_SUBST(LIBBONOBO_CFLAGS, [`pkg-config --cflags libonobo-2.0`])
AC_SUBST(LIBBONOBO_LIBS, [`pkg-config --libs libbonobo-2.0`])
dnl Checking for libpanelapplet-2.6
dnl PKG_CHECK_MODULES(GTKMM, gtkmm-2.4 >= 2.8.0)
AC_SUBST(LIBPANELAPPLETMM_CFLAGS, [`pkg-config --cflags libpanelappletmm-2.6`])
AC_SUBST(LIBPANELAPPLETMM_LIBS, [`pkg-config --libs libpanelappletmm-2.6`])

dnl Para la pruebas
dnl AC_SUBST(target_abbrev, [unix])

AC_PROG_CXX
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SRCDIR([src])

AM_MAINTAINER_MODE

AC_CONFIG_FILES([
	Makefile
	src/Makefile
	doc/Makefile
	])
AC_OUTPUT