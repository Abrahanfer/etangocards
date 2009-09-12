/* etangocards-applet.cpp
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
#include<gtkmm.h>
#include<libpanelappletmm.h>
#include<libbonobo.h>
#include<string>
#include<libxml++/libxml++.h>
#include"etangocards-applet.h"
#include"control-system.h"
#include"dialog-creation-package.h"
#include"main.h"

sigc::slot<bool> ETangoCardsApplet::slot_timeout;
int ETangoCardsApplet::timeout_value = 15;

ETangoCardsApplet::ETangoCardsApplet (PanelApplet* castitem):
  Gnome::Panel::Applet (castitem)
{
  unsigned int index_cards;

  static const Glib::ustring xml_popup =
    "<popup name='button3'>\n"
    "   <menuitem name='Load Package Item'\n"
    "             verb='LoadPackage' _label='_Load Package...'\n"
    "             pixtype='stock' pixname='gtk-open'/>\n"
    "   <menuitem name='New Package Item'\n"
    "             verb='NewPackage' _label='_New Package...'\n"
    "             pixtype='stock' pixname='gtk-new'/>\n"
    "   <menuitem name='Hide Packages Item'\n"
    "             verb='HidePackages' _label='Hi_de Packages...'\n"
    "             />\n"
    "   <menuitem name='Show Packages Item'\n"
    "             verb='ShowPackages' _label='_Show Packages...'\n"
    "             />\n"
    "   <separator/>"
    "   <menuitem name='preferences' verb='preferences' _label='_Preferences'"
    "             pixtype='stock' pixname='gtk-preferences'\n"
    "             />\n"
    "</popup>\n";

  static const BonoboUIVerb menu_verb[] = 
    {
      BONOBO_UI_VERB ("LoadPackage", 
		      &ETangoCardsApplet::applet_load_package),
      BONOBO_UI_VERB ("NewPackage", 
		      &ETangoCardsApplet::applet_new_package),
      BONOBO_UI_VERB ("HidePackages", 
		      &ETangoCardsApplet::applet_hide_packages),
      BONOBO_UI_VERB ("ShowPackages", 
		      &ETangoCardsApplet::applet_show_packages),
      BONOBO_UI_VERB ("preferences",
		      &ETangoCardsApplet::applet_preferences),
      BONOBO_UI_VERB_END
    };

  setup_menu (xml_popup, menu_verb, this);

  Gtk::Image *picon = new Gtk::Image(ICONS_ETANGOCARDS_32);
  add (*picon);

  set_flags (Gnome::Panel::APPLET_EXPAND_MINOR);
  //Recuperation of lastest session
  xmlpp::DomParser parser;
  try
    {
      parser.parse_file (ControlSystem::path_);
    }
  catch (xmlpp::internal_error e)
    {
    }
  if (parser)
    {
      const xmlpp::Element* root = 
	parser.get_document ()->get_root_node ();
      std::istringstream iss 
	(root->get_attribute_value ("timeout"));
      iss >> timeout_value;
      xmlpp::Node::NodeList nodelist = root->get_children (); 
      xmlpp::Node::NodeList::const_iterator i;
      for(i = nodelist.begin (); i != nodelist.end (); ++i)
	{
	  xmlpp::Element *node = dynamic_cast<xmlpp::Element*>(*i);
	  if(node)
	    {
	      std::istringstream iss
		(node->get_attribute_value ("index_cards"));
	      iss >> index_cards;
	      Glib::ustring path(node->get_attribute_value ("path"));
	      ControlSystem::LoadPackage (path, index_cards);
	    }
	}
    }
  //Configure the timeout
  applet_timeout (timeout_value);

  show_all ();
}

ETangoCardsApplet::~ETangoCardsApplet (void)
{
  ControlSystem::serializeSystem ();
}

void 
ETangoCardsApplet::applet_load_package (BonoboUIComponent *, 
					void *applet, const char *)
{
  Gtk::FileChooserDialog dialog("Please choose a package",
				Gtk::FILE_CHOOSER_ACTION_OPEN);
  

  //Add response buttons the the dialog:
  dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

  //Add filters, so that only certain file types can be selected:

  Gtk::FileFilter filter_xml;
  filter_xml.set_name("Xml files");
  filter_xml.add_mime_type("application/xml");
  dialog.add_filter(filter_xml);


  Gtk::FileFilter filter_any;
  filter_any.set_name("Any files");
  filter_any.add_pattern("*");
  dialog.add_filter(filter_any);

  //Icon
  Glib::RefPtr<Gdk::Pixbuf> icon = Gdk::Pixbuf::create_from_file 
    (ICONS_ETANGOCARDS_32);
  dialog.set_icon (icon);

  dialog.set_current_folder (Glib::get_home_dir ());

  //Show the dialog and wait for a user response:
  int result = dialog.run();
   
  //Handle the response:
  switch(result)
    {
    case(Gtk::RESPONSE_OK):
      {

	//Notice that this is a std::string, not a Glib::ustring.
	std::string filename = dialog.get_filename();
	ControlSystem *cs = new ControlSystem();
	cs->LoadPackage (filename, 1);
	break;
      }
    case(Gtk::RESPONSE_CANCEL):
      {
	break;
      }
    default:
      {
	break;
      }
    }
}

void
ETangoCardsApplet::applet_timeout (int timeout_value) throw ()
{
  if (timeout_value != 0)
    {
      //	slot_timeout.disconnect ();
      sigc::slot<bool> slot = sigc::ptr_fun
	(&ETangoCardsApplet::show_packages_timeout);
      Glib::signal_timeout ().connect
	(slot_timeout, 1000 * 60 * timeout_value);
      slot_timeout = slot;
    }
  else
    {
      slot_timeout.disconnect ();
    }
}
