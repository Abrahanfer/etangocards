//-*-c++-*-

#ifndef ETANGOCARDS_APPLET_H_
#define ETANGOCARDS_APPLET_H_

#include<libpanelappletmm.h>
#include<libbonobo.h>

class ETangoCardsApplet : public Gnome::Panel::Applet {
public:
  explicit ETangoCardsApplet (PanelApplet *);
  virtual ~ETangoCardsApplet ();
  static void applet_load_package (BonoboUIComponent *, void *applet,
				   const char *);
  static void applet_new_package (BonoboUIComponent *, void *applet,
				  const char *);
};

#endif //ETANGOCARDS_APPLET_H_
