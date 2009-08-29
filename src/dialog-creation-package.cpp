/* dialog-creation-package.cpp
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

#include<gtkmm/builder.h>
#include<gtkmm/window.h>
#include<gtkmm/entry.h>
#include<gtkmm/button.h>
#include<gtkmm/filechooserdialog.h>
#include<gtkmm/stock.h>
#include"dialog-creation-package.h"
#include"control-system.h"
#include"dialog-package.h"

DialogCreationPackage::DialogCreationPackage (void)
{
  Glib::RefPtr<Gtk::Builder> pdialog_creation_package_ =
    Gtk::Builder::create_from_file (FILE_UI_DIALOG_CREATION_PACKAGE);

  pdialog_creation_package_->get_widget 
    ("dialog_creation_package_window", pdialog_creation_package_window_);

  pdialog_creation_package_->get_widget 
    ("dialog_creation_package_btn_cancel", 
     pdialog_creation_package_btn_cancel_);
  pdialog_creation_package_btn_cancel_->signal_clicked ().connect
    (sigc::mem_fun (
		    *this,
		    &DialogCreationPackage::dialog_creation_package_cancel));


  pdialog_creation_package_->get_widget 
    ("dialog_creation_package_btn_save", pdialog_creation_package_btn_save_);
  pdialog_creation_package_btn_save_->signal_clicked ().connect
    (sigc::mem_fun (
		    *this,
		    &DialogCreationPackage::dialog_creation_package_save));

  pdialog_creation_package_->get_widget ("dialog_creation_package_entry",
					 pdialog_creation_package_entry_);
  //icon
  Glib::RefPtr<Gdk::Pixbuf> icon = Gdk::Pixbuf::create_from_file 
    (ICONS_ETANGOCARDS_32);
  pdialog_creation_package_window_->set_icon (icon);

  pdialog_creation_package_window_->show ();
}

DialogCreationPackage::~DialogCreationPackage (void)
{
  delete pdialog_creation_package_btn_cancel_;
  delete pdialog_creation_package_btn_save_;
  delete pdialog_creation_package_entry_;
  delete pdialog_creation_package_window_;
}

void
DialogCreationPackage::dialog_creation_package_cancel (void)
  throw ()
{
  pdialog_creation_package_window_->hide ();
}

void
DialogCreationPackage::dialog_creation_package_save (void)
  throw ()
{
  Glib::ustring pkg_name = pdialog_creation_package_entry_->get_text ();

  Gtk::FileChooserDialog dialog("Please choose a folder for save",
				Gtk::FILE_CHOOSER_ACTION_SAVE);
  

  //Add response buttons the the dialog:
  dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dialog.add_button(Gtk::Stock::SAVE, Gtk::RESPONSE_OK);

 int result = dialog.run();

 //Handle the response:
  switch(result)
    {
    case(Gtk::RESPONSE_OK):
      {

	//Notice that this is a std::string, not a Glib::ustring.
	Glib::ustring filename = dialog.get_filename ();
	Package *pkg = new Package (pkg_name, filename);
	ControlSystem::associate (pkg_name, pkg);
	pdialog_creation_package_window_->hide ();
	DialogPackage *pdpkg = new DialogPackage (pkg);
	DialogPackage::insertDialogPackage (pdpkg);
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
