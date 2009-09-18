/* dialog-preferences.cpp
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
#include"dialog-preferences.h"
#include"main.h"
#include"etangocards-applet.h"

int DialogPreferences::vec[7] = {15, 20, 25, 30, 45, 60, 0};

DialogPreferences::DialogPreferences (void) 
  throw ()
{
  pdialog_preferences_ = 
    Gtk::Builder::create_from_file (FILE_UI_DIALOG_PREFERENCES);

  pdialog_preferences_->get_widget ("dialog_preferences_lbl",
				    pdialog_preferences_lbl_);
  pdialog_preferences_lbl_->set_label ("Choose a option for timeout:");

  pdialog_preferences_->get_widget ("dialog_preferences_button_close",
				    pdialog_preferences_close_);

   pdialog_preferences_close_->signal_clicked ().connect
    (sigc::mem_fun (
		    *this,
		    &DialogPreferences::dialog_preferences_close));

  pdialog_preferences_->get_widget ("dialog_preferences_combobox",
				    pdialog_preferences_comboBox_);

  pdialog_preferences_treeModel_ = new Gtk::TreeModel::ColumnRecord ();
  Gtk::TreeModelColumn<Glib::ustring> m_col_times;
  pdialog_preferences_treeModel_->add (m_col_times);
  ref_treeModel_ = Gtk::ListStore::create 
    (*pdialog_preferences_treeModel_);

  pdialog_preferences_comboBox_->set_model (ref_treeModel_);

  //Fill the ComboBox's TreeModel
  Gtk::TreeModel::Row row = *(ref_treeModel_->append());
  row[m_col_times] = "15 Minutes";

  row = *(ref_treeModel_->append());
  row[m_col_times] = "20 Minutes";

  row = *(ref_treeModel_->append());
  row[m_col_times] = "25 Minutes";

  row = *(ref_treeModel_->append());
  row[m_col_times] = "30 Minutes";

  row = *(ref_treeModel_->append());
  row[m_col_times] = "45 Minutes";

  row = *(ref_treeModel_->append());
  row[m_col_times] = "60 Minutes";

  row = *(ref_treeModel_->append());
  row[m_col_times] = "No Timeout";

  pdialog_preferences_comboBox_->pack_start (m_col_times);

  pdialog_preferences_comboBox_->set_active (get_active ());
  pdialog_preferences_comboBox_->signal_changed ().connect
    (sigc::mem_fun (
		    *this,
		    &DialogPreferences::dialog_preferences_changed));


  pdialog_preferences_->get_widget ("dialog_preferences_window",
				    pdialog_preferences_window_);

  //icon
  Glib::RefPtr<Gdk::Pixbuf> icon = Gdk::Pixbuf::create_from_file 
    (ICONS_ETANGOCARDS_32);
  pdialog_preferences_window_->set_icon (icon);

  pdialog_preferences_window_->show ();
}

void
DialogPreferences::dialog_preferences_changed (void) throw ()
{
  ETangoCardsApplet::applet_timeout
    (vec[pdialog_preferences_comboBox_->get_active_row_number ()]);

  ETangoCardsApplet::set_timeout 
    (vec[pdialog_preferences_comboBox_->get_active_row_number ()]);
}

int
DialogPreferences::get_active (void) throw ()
{
  std::map<int, int> map_timeout;
  map_timeout.insert (std::make_pair (15, 0));
  map_timeout.insert (std::make_pair (20, 1));
  map_timeout.insert (std::make_pair (25, 2));
  map_timeout.insert (std::make_pair (30, 3));
  map_timeout.insert (std::make_pair (45, 4));
  map_timeout.insert (std::make_pair (60, 5));
  map_timeout.insert (std::make_pair (0, 6));

  return map_timeout[ETangoCardsApplet::get_timeout ()];
}
