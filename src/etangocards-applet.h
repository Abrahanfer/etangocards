//-*-c++-*-

#ifndef ETANGOCARDS_APPLET_H_
#define ETANGOCARDS_APPLET_H_

#include<libpanelappletmm.h>
#include<libbonobo.h>
#include"dialog-package.h"
#include"dialog-creation-package.h"

class ETangoCardsApplet : public Gnome::Panel::Applet {
public:
  explicit ETangoCardsApplet (PanelApplet *);
  virtual ~ETangoCardsApplet ();
  static void applet_load_package (BonoboUIComponent *, void *applet,
				   const char *);
  static void applet_new_package (BonoboUIComponent *, void *applet,
				  const char *);
  static void applet_hide_packages (BonoboUIComponent *, 
				    void *applet, const char *);
  static void applet_show_packages (BonoboUIComponent *, 
				    void *applet, const char *);
};

inline void
ETangoCardsApplet::applet_hide_packages (BonoboUIComponent *, 
					 void *applet, const char *)
{
  DialogPackage::dialog_package_hide_windows ();
}

inline void
ETangoCardsApplet::applet_new_package (BonoboUIComponent *, 
				       void *applet, const char *)
{
  new DialogCreationPackage ();
}

inline void
ETangoCardsApplet::applet_show_packages (BonoboUIComponent *, 
					 void *applet, const char *)
{
  DialogPackage::dialog_package_show_windows ();
}

#endif //ETANGOCARDS_APPLET_H_
