
SUBDIRS = po src

uidir   = $(datadir)/$(PACKAGE)/ui

ui_DATA = data/ui/dialog_package.ui \
	  data/ui/dialog_new.ui	    \
	  data/ui/dialog_creation_package.ui\
	  data/ui/dialog_preferences.ui\
	  data/ui/dialog_quiz_front.ui\
	  data/ui/dialog_quiz_answer.ui\
	  data/ui/dialog_quiz_back.ui\
	  data/ui/dialog_quiz_result.ui\
          data/ui/dialog_alert_package.ui	

iconsdir = $(datadir)/$(PACKAGE)/icons

icons_DATA = data/icons/etangocards.32.png \
	     data/icons/etangocards.48.png

serverdir = /usr/lib/bonobo/servers

server_DATA = src/ETangoCards_Applet.server

INTLTOOL_FILES = intltool-extract.in \
                 intltool-merge.in \
                 intltool-update.in

EXTRA_DIST = build-aux/config.rpath m4/ChangeLog  $(ui_DATA) \
	     $(server_DATA)\
	     $(icons_DATA)\
	     $(INTLTOOL_FILES)
ACLOCAL_AMFLAGS = -I m4
