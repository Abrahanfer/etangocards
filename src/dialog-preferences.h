//-*-c++-*-
/* dialog-preferences.h
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
#ifndef DIALOG_PREFERENCES_H_
#define DIALOG_PREFERENCES_H_

#include<gtkmm/builder.h>
#include<gtkmm/window.h>
#include<gtkmm/button.h>
#include<gtkmm/label.h>
#include<gtkmm/combobox.h>
#include<gtkmm/liststore.h>

class ETangoCardsApplet;

/**
 * This class manage the dialog preferences.
 *
 * @author Abrahán Fernández Nieto
 * @version 1.0
 */
class DialogPreferences {
public:

  /**
   * Default contructor.
   */
  DialogPreferences (void) throw ();

  /**
   * Method which return the comoboBox's active state.
   *
   * @return the active state in a int.
   */
  int get_active (void) throw ();

  /// Attribute which is a relation between comboBox's 
  /// active state and timeouts.
  static int vec[7];
private:
  void dialog_preferences_close (void) throw ();
  void dialog_preferences_changed (void) throw ();
  Glib::RefPtr<Gtk::Builder> pdialog_preferences_;
  Gtk::Window* pdialog_preferences_window_;
  Gtk::Label* pdialog_preferences_lbl_;
  Gtk::ComboBox* pdialog_preferences_comboBox_;
  Gtk::TreeModel::ColumnRecord* pdialog_preferences_treeModel_;
  Gtk::Button* pdialog_preferences_close_;
  Glib::RefPtr<Gtk::ListStore> ref_treeModel_; 
};

inline void
DialogPreferences::dialog_preferences_close (void) throw ()
{
  pdialog_preferences_window_->hide ();
}

#endif //DIALOG_PREFERENCES_H_
