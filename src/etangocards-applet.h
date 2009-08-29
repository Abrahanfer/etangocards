//-*-c++-*-
/* etangocards-applet.h
 *
 * Copyright (C) 2009 Abrahán Fernández Nieto
 *
 * Email: <abrahanfer@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

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
