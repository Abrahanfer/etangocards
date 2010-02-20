//-*-c++-*-
/* dialog-new.h
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

#ifndef DIALOG_NEW_H_
#define DIALOG_NEW_H_

#include<gtkmm/builder.h>
#include<gtkmm/window.h>
#include<gtkmm/toolbutton.h>
#include<gtkmm/textview.h>
#include<gtkmm/label.h>
#include"package.h"
#include"main.h"

class DialogPackage;

/**
 * <p>This class manage the window for news cards.</p>
 *
 * @author Abrahán Fernández Nieto
 * @version 1.0
 */
class DialogNew {
public:

  /**
   * Constructor with two parameters.
   *
   * @param pkg pointer to package
   * @param d_pkg pointer to window for package <code>pkg</code>
   */
  DialogNew (Package*, const DialogPackage*);

  /**
   * Destructor
   */
  ~DialogNew (void);
private:
  void dialog_new_save_card (void);
  void dialog_new_information (void);
  Glib::ustring front_;
  Glib::ustring back_;
  Package* pkg_;
  bool is_front_;
  const DialogPackage* d_pkg_;
  Glib::RefPtr<Gtk::Builder> pdialog_new_;
  Gtk::Window* pdialog_new_window_;
  Gtk::ToolButton* pdialog_new_save_button_;
  Gtk::ToolButton* pdialog_new_information_button_;
  Gtk::TextView* pdialog_new_textview_;
  Gtk::Label* pdialog_new_lbl_; 
};

#endif //DIALOG_NEW_H_
