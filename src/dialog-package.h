//-*-c++-*-
/* dialog-package.h
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

#ifndef DIALOG_PACKAGE_H_
#define DIALOG_PACKAGE_H_

#include<gtkmm/builder.h>
#include<gtkmm/window.h>
#include<gtkmm/toolbutton.h>
#include<gtkmm/label.h>
#include<gtkmm/textview.h>
#include<gtkmm/textbuffer.h>
#include"package.h"
#include"dialog-new.h"

class DialogPackage {
public:
  DialogPackage (Package *);
  ~DialogPackage (void);
  void refresh_num_cards (void) const throw ();
private:
  void dialog_package_new_card (void) throw ();
  void dialog_package_prev_card (void) throw ();
  void dialog_package_next_card (void) throw ();
  void dialog_package_show (void) throw ();
  void dialog_package_hide (void) throw ();
  Package *pkg_;
  Glib::RefPtr<Gtk::Builder> pdialog_package_;
  Gtk::Window* pdialog_package_window_;
  Gtk::ToolButton* pdialog_package_new_;
  Gtk::ToolButton* pdialog_package_prev_;
  Gtk::ToolButton* pdialog_package_next_;
  Gtk::ToolButton* pdialog_package_show_;
  Gtk::Label* pdialog_package_lbl1_;
  mutable Gtk::Label* pdialog_package_lbl3_;
  Glib::RefPtr<Gtk::TextBuffer> ptextbuffer;
  Gtk::TextView* pdialog_package_textview_;
};

inline void
DialogPackage::dialog_package_new_card (void) throw ()
{
  new DialogNew(pkg_, this);
}

#endif //DIALOG_PACKAGE_H_