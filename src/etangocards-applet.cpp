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
#include"quiz.h"
#include"dialog-alert-package.h"

sigc::slot<bool> ETangoCardsApplet::slot_timeout;
int ETangoCardsApplet::timeout_value = 15;

ETangoCardsApplet::ETangoCardsApplet (PanelApplet* castitem):
  Gnome::Panel::Applet (castitem)
{
  unsigned int index_cards;
  bool configurationFile = true;

  static const Glib::ustring xml_popup =
    "<popup name='button3'>\n"
    "   <menuitem name='Load Package Item'\n"
    "             verb='LoadPackage' _label='_Load Package...'\n"
    "             pixtype='stock' pixname='gtk-open'/>\n"
    "   <menuitem name='New Package Item'\n"
    "             verb='NewPackage' _label='_New Package...'\n"
    "             pixtype='stock' pixname='gtk-new'/>\n"
    "   <menuitem name='Hide Packages Item'\n"
    "             verb='HidePackages' _label='Hi_de Packages'\n"
    "             />\n"
    "   <menuitem name='Show Packages Item'\n"
    "             verb='ShowPackages' _label='_Show Packages'\n"
    "             />\n"
    "   <menuitem name='Quiz Mode Item'\n"
    "             verb='QuizMode' _label='_Quiz Mode'\n" 
    "             pixtype='stock' pixname='gtk-execute'\n"
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
      BONOBO_UI_VERB ("QuizMode",
		      &ETangoCardsApplet::applet_quiz_mode),
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
  //parser.set_validate ();
  try
    {
      parser.parse_file (ControlSystem::path ());
    }
  catch (xmlpp::internal_error e)
    {//TODO: bad package
      configurationFile = false;
    }
  if (parser && configurationFile)
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
	  
	  if((*i)->get_name () == "Package")
	    {
	      xmlpp::Element *node = dynamic_cast<xmlpp::Element*>(*i);
	      std::istringstream iss
		(node->get_attribute_value ("index_cards"));
	      iss >> index_cards;
	      Glib::ustring path(node->get_attribute_value ("path"));
	      ControlSystem::LoadPackage (path, index_cards);
	    }
	  else
	    {
	      if ((*i)->get_name () == "Categories")
		{
		  xmlpp::Node::NodeList nodelist = (*i)->get_children (); 
		  xmlpp::Node::NodeList::const_iterator j;
		  for (j = nodelist.begin (); j != nodelist.end (); ++j)
		    {
		      xmlpp::Element *nodeCategory = 
			dynamic_cast<xmlpp::Element*>(*j);
		      if (nodeCategory)
			{
			  Glib::ustring name_category 
			    (nodeCategory->get_attribute_value ("category"));
			  std::istringstream iss
			    (nodeCategory->get_attribute_value ("score"));
			  double score;
			  iss >> score;
			  ControlSystem::categories[name_category] = score;
			  Glib::ustring range
			    (nodeCategory->get_attribute_value ("range"));
			  ControlSystem::range_categories_[name_category]
			    = range;
			}
		    }
		}
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
					void *, const char *)
{
  Gtk::FileChooserDialog dialog(_("Please choose a package"),
				Gtk::FILE_CHOOSER_ACTION_OPEN);
  

  //Add response buttons the the dialog:
  dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

  //Add filters, so that only certain file types can be selected:

  Gtk::FileFilter filter_xml;
  filter_xml.set_name(_("Xml files"));
  filter_xml.add_mime_type("application/xml");
  dialog.add_filter(filter_xml);


  Gtk::FileFilter filter_any;
  filter_any.set_name(_("Any files"));
  filter_any.add_pattern("*");
  dialog.add_filter(filter_any);

  //Icon
  Glib::RefPtr<Gdk::Pixbuf> icon = Gdk::Pixbuf::create_from_file 
    (ICONS_ETANGOCARDS_32);
  dialog.set_icon (icon);

  dialog.set_current_folder (Glib::get_home_dir ());

  //Show the dialog and wait for a user response:
  int loop = -1;
  do 
    {
      int result = dialog.run();

      //Handle the response:
      switch(result)
	{
	case(Gtk::RESPONSE_OK):
	  {
	
	    //Notice that this is a std::string, not a Glib::ustring.
	    std::string filename = dialog.get_filename();
	    ControlSystem *cs = new ControlSystem();
	    try
	      {
		cs->LoadPackage (filename, 1);
	      }
	    catch (Package::BadPackageFileException excep)
	      {
		DialogAlertPackage* pdialog_ = new DialogAlertPackage ();
		loop = pdialog_->showDialogAlertPackage ();
		delete pdialog_;
	      }
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
    }while (loop);
}

void
ETangoCardsApplet::applet_timeout (int timeout_value) throw ()
{
  sigc::slot<bool> slot = sigc::ptr_fun
    (&ETangoCardsApplet::show_packages_timeout);
  slot_timeout = slot;
  Glib::signal_timeout ().connect_seconds
    (slot_timeout, 
     60 * timeout_value);
}

void
ETangoCardsApplet::applet_quiz_mode (BonoboUIComponent *, 
				     void *, const char *)
{
  Gtk::FileChooserDialog dialog(_("Please choose a package"),
				Gtk::FILE_CHOOSER_ACTION_OPEN);
  

  //Add response buttons the the dialog:
  dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

  //Add filters, so that only certain file types can be selected:

  Gtk::FileFilter filter_xml;
  filter_xml.set_name(_("Xml files"));
  filter_xml.add_mime_type("application/xml");
  dialog.add_filter(filter_xml);


  Gtk::FileFilter filter_any;
  filter_any.set_name(_("Any files"));
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
	new Quiz(filename);
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
