/* dialog-creation-package.cpp
 *
 * Copyright (C) 2009, 2010 Abrahán Fernández Nieto
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

#include<gtkmm/filechooserdialog.h>
#include<gtkmm/stock.h>
#include"dialog-creation-package.h"
#include"control-system.h"
#include"dialog-package.h"
#include"main.h"

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

  pdialog_creation_package_->get_widget ("dialog_creation_package_category",
					 pdialog_creation_package_category_);

  pdialog_creation_package_->get_widget ("dialog_creation_package_score",
					 pdialog_creation_package_score_);
  //Dialog Creation Package ComboBox1
  pdialog_creation_package_->get_widget ("dialog_creation_package_comboBox1",
					 pdialog_creation_package_comboBox1_);

  pdialog_creation_package_treeModel1_ = new Gtk::TreeModel::ColumnRecord ();
  Gtk::TreeModelColumn<Glib::ustring> m_col_times1;
  pdialog_creation_package_treeModel1_->add (m_col_times1);
  ref_treeModel1_ = Gtk::ListStore::create 
    (*pdialog_creation_package_treeModel1_);

  pdialog_creation_package_comboBox1_->set_model (ref_treeModel1_);

  //Fill the ComboBox1's TreeModel
  Gtk::TreeModel::Row row1 = *(ref_treeModel1_->append());
  row1[m_col_times1] = "Range H";

  row1 = *(ref_treeModel1_->append());
  row1[m_col_times1] = "Range G";

  row1 = *(ref_treeModel1_->append());
  row1[m_col_times1] = "Range F";

  row1 = *(ref_treeModel1_->append());
  row1[m_col_times1] = "Range E";

  row1 = *(ref_treeModel1_->append());
  row1[m_col_times1] = "Range D";

  row1 = *(ref_treeModel1_->append());
  row1[m_col_times1] = "Range C";

  row1 = *(ref_treeModel1_->append());
  row1[m_col_times1] = "Range B";

  row1 = *(ref_treeModel1_->append());
  row1[m_col_times1] = "Range A";

  row1 = *(ref_treeModel1_->append());
  row1[m_col_times1] = "Range S";

  pdialog_creation_package_comboBox1_->pack_start (m_col_times1);

  pdialog_creation_package_comboBox1_->set_active (0);

  //Dialog Creation Package ComboBox2
  pdialog_creation_package_->get_widget ("dialog_creation_package_comboBox2",
					 pdialog_creation_package_comboBox2_);

  pdialog_creation_package_treeModel2_ = new Gtk::TreeModel::ColumnRecord ();
  Gtk::TreeModelColumn<Glib::ustring> m_col_times2;
  pdialog_creation_package_treeModel2_->add (m_col_times2);
  ref_treeModel2_ = Gtk::ListStore::create 
    (*pdialog_creation_package_treeModel2_);

  pdialog_creation_package_comboBox2_->set_model (ref_treeModel2_);

  //Fill the ComboBox2's TreeModel
  Gtk::TreeModel::Row row2 = *(ref_treeModel2_->append());
  row2[m_col_times2] = "Basic Type";

  pdialog_creation_package_comboBox2_->pack_start (m_col_times2);

  pdialog_creation_package_comboBox2_->set_active (0);

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
  Glib::ustring pkg_category = 
    pdialog_creation_package_category_->get_text ();
  Glib::ustring pkg_score = pdialog_creation_package_score_->get_text ();
  int num_range = 
    pdialog_creation_package_comboBox1_->get_active_row_number ();
  /*int num_type = 
    pdialog_creation_package_comboBox2_->get_active_row_number ();*/

  Gtk::FileChooserDialog dialog("Please choose a folder for save",
				Gtk::FILE_CHOOSER_ACTION_SAVE);
  

  //Add response buttons the the dialog:
  dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dialog.add_button(Gtk::Stock::SAVE, Gtk::RESPONSE_OK);

  //Icon
  Glib::RefPtr<Gdk::Pixbuf> icon = Gdk::Pixbuf::create_from_file 
    (ICONS_ETANGOCARDS_32);
  dialog.set_icon (icon);

//Add filters, so that only certain file types can be selected:

  Gtk::FileFilter filter_xml;
  filter_xml.set_name("Xml files");
  filter_xml.add_mime_type("application/xml");
  dialog.add_filter(filter_xml);


  Gtk::FileFilter filter_any;
  filter_any.set_name("Any files");
  filter_any.add_pattern("*");
  dialog.add_filter(filter_any);

  dialog.set_current_folder (Glib::get_home_dir ());

 int result = dialog.run();

 //Handle the response:
  switch(result)
    {
    case(Gtk::RESPONSE_OK):
      {

	//Notice that this is a std::string, not a Glib::ustring.
	Glib::ustring filename = dialog.get_filename ();
	Package *pkg = new Package (pkg_name, filename, 
				    pkg_category, pkg_score, num_range);
	ControlSystem::associate (pkg);
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
