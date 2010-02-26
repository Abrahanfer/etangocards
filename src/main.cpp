/* main.cpp
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
#include<iostream>
#include<string>
#include<cstdlib>
#include<gtkmm/main.h>
#include<pthread.h>
#include<libpanelappletmm.h>
#include<libbonobo.h>
#include<config.h>
#include<locale.h>
#include"gettext.h"
#include"control-system.h"
#include"package.h"
#include"dialog-package.h"
#include"dialog-new.h"
#include"etangocards-applet.h"

using namespace std;


int
main (int argc, char* argv[]) 
{
  //Configuration for i18n
  bindtextdomain(GETTEXT_PACKAGE, PROGRAMNAME_LOCALEDIR);
  bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
  textdomain(GETTEXT_PACKAGE);

  Gnome::Panel::init("EtangoCards", "0.0.2", argc, argv);
  
  try
    {
      int returncode = Gnome::Panel::factory_main<ETangoCardsApplet>("OAFIID:ETangoCardsApplet_Factory");
      return returncode;
    }
  catch(const Glib::Error& ex)
    {
      std::cout << ex.what() << std::endl;
      return 0;
    }

}
