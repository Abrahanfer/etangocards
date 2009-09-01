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
      BONOBO_UI_VERB_END
    };

  setup_menu (xml_popup, menu_verb, this);
  
  //  Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_file 
  //(ICONS_ETANGOCARDS_32);

  Gtk::Image *picon = new Gtk::Image(ICONS_ETANGOCARDS_32);
  add(*picon);

  //  set_flags (Gnome::Panel::APPLET_EXPAND_MINOR);
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

  Gtk::FileFilter filter_text;
  filter_text.set_name("Text files");
  filter_text.add_mime_type("text/plain");
  dialog.add_filter(filter_text);

  Gtk::FileFilter filter_cpp;
  filter_cpp.set_name("C/C++ files");
  filter_cpp.add_mime_type("text/x-c");
  filter_cpp.add_mime_type("text/x-c++");
  filter_cpp.add_mime_type("text/x-c-header");
  dialog.add_filter(filter_cpp);

  Gtk::FileFilter filter_any;
  filter_any.set_name("Any files");
  filter_any.add_pattern("*");
  dialog.add_filter(filter_any);

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

