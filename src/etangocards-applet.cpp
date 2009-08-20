#include<iostream>
#include<gtkmm.h>
#include<libpanelappletmm.h>
#include<libbonobo.h>
#include<string>
#include"etangocards-applet.h"
#include"control-system.h"
#include"dialog-creation-package.h"

ETangoCardsApplet::ETangoCardsApplet (PanelApplet* castitem):
  Gnome::Panel::Applet (castitem)
{


  static const Glib::ustring xml_popup =
    "<popup name='button3'>\n"
    "   <menuitem name='Load Package Item'\n"
    "             verb='LoadPackage' _label='_Load Package...'\n"
    "             pixtype='stock' pixname='gtk-open'/>\n"
    "   <menuitem name='New Package Item'\n"
    "             verb='NewPackage' _label='_New Package...'\n"
    "             pixtype='stock' pixname='gtk-new'/>\n"
    "</popup>\n";

  static const BonoboUIVerb menu_verb[] = 
    {
      BONOBO_UI_VERB ("LoadPackage", 
		      &ETangoCardsApplet::applet_load_package),
      BONOBO_UI_VERB ("NewPackage", 
		      &ETangoCardsApplet::applet_new_package),
      BONOBO_UI_VERB_END
    };

  setup_menu (xml_popup, menu_verb, this);
  
  add (*Gtk::manage(new Gtk::Label ("ETangoCards Applet")));
  set_flags (Gnome::Panel::APPLET_EXPAND_MINOR);
  
  show_all ();
}

ETangoCardsApplet::~ETangoCardsApplet (void)
{
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
	cs->LoadPackage (filename);
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
ETangoCardsApplet::applet_new_package (BonoboUIComponent *, 
				       void *applet, const char *)
{
  new DialogCreationPackage ();
}
