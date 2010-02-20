//-*-c++-*-
/* dialog-creation-package.h
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

#ifndef DIALOG_CREATION_PACKAGE_H_
#define DIALOG_CREATION_PACKAGE_H_

#include<gtkmm/builder.h>
#include<gtkmm/window.h>
#include<gtkmm/entry.h>
#include<gtkmm/combobox.h>
#include<gtkmm/liststore.h>
#include<gtkmm/button.h>
#include"main.h"

/**
 * <p>This class construct and manage the window for 
 * creation packages.</p>
 *
 * @author Abrahán Fernández Nieto
 * @version 1.0
 */
class DialogCreationPackage {
public:

  /**
   * Default contructor
   */
  DialogCreationPackage (void);

  /**
   * Destructor
   */
  ~DialogCreationPackage (void);
private:
  void dialog_creation_package_cancel (void) throw();
  void dialog_creation_package_save (void) throw();
  Gtk::Window* pdialog_creation_package_window_;
  Gtk::Button* pdialog_creation_package_btn_cancel_;
  Gtk::Button* pdialog_creation_package_btn_save_;
  Gtk::Entry* pdialog_creation_package_entry_;
  Gtk::Entry* pdialog_creation_package_category_;
  Gtk::Entry* pdialog_creation_package_score_;
  Gtk::ComboBox* pdialog_creation_package_comboBox1_;
  Gtk::TreeModel::ColumnRecord* pdialog_creation_package_treeModel1_;
  Glib::RefPtr<Gtk::ListStore> ref_treeModel1_; 
  Gtk::ComboBox* pdialog_creation_package_comboBox2_;
  Gtk::TreeModel::ColumnRecord* pdialog_creation_package_treeModel2_;
  Glib::RefPtr<Gtk::ListStore> ref_treeModel2_; 
};

#endif //DIALOG_CREATION_PACKAGE_H_
