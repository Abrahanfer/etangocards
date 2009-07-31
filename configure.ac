dnl 
AC_INIT([etangocards], [0.0.1], [abrahanfer@gmail.com])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([-Wall -Werror])
dnl Checking for libxml++2.6
PKG_CHECK_MODULES(LIBXMLPP, libxml++-2.6 >= 2.10.0)
AC_SUBST(LIBXMLPP_CFLAGS, [`pkg-config --cflags libxml++-2.6`])
AC_SUBST(LIBXMLPP_LIBS, [`pkg-config --libs libxml++-2.6`])

dnl Para la pruebas
AC_SUBST(target_abbrev, [unix])

AC_PROG_CXX
AC_CONFIG_HEADERS([config.h])

AM_MAINTAINER_MODE

AC_CONFIG_FILES([
	Makefile
	src/Makefile
	])
AC_OUTPUT