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

#include<gtkmm/window.h>
#include<gtkmm/button.h>
#include"main.h"

class DialogCreationPackage {
public:
  DialogCreationPackage (void);
  ~DialogCreationPackage (void);
private:
  void dialog_creation_package_cancel (void) throw();
  void dialog_creation_package_save (void) throw();
  Gtk::Window* pdialog_creation_package_window_;
  Gtk::Button* pdialog_creation_package_btn_cancel_;
  Gtk::Button* pdialog_creation_package_btn_save_;
  Gtk::Entry* pdialog_creation_package_entry_;
};

#endif //DIALOG_CREATION_PACKAGE_H_
