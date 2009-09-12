
AM_CPPFLAGS = \
	-DPREFIX=\""$(prefix)"\" \
	-DDATADIR=\""$(datadir)"\" \
	-DLIBDIR=\""$(libdir)"\" \
	-DLOCALEDIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE=\""$(PACKAGE)"\"


bin_PROGRAMS = etangocards
etangocards_SOURCES = main.cpp main.h card.cpp card.h package.cpp \
	package.h control-system.cpp control-system.h dialog-package.h \
	dialog-package.cpp dialog-new.h dialog-new.cpp \
	etangocards-applet.h etangocards-applet.cpp \
	dialog-creation-package.h dialog-creation-package.cpp \
	dialog-preferences.h dialog-preferences.cpp
etangocards_LDFLAGS = @LIBXMLPP_LIBS@ @GTKMM_LIBS@ @LIBBONOBO_LIBS@ \
	@LIBPANELAPPLETMM_LIBS@ 
etangocards_CXXFLAGS = @LIBXMLPP_CFLAGS@ @GTKMM_CFLAGS@ \
	@LIBBONOBO_CFLAGS@ @LIBPANELAPPLETMM_CFLAGS@ -Wall -pedantic


