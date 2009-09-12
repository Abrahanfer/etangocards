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

  pdialog_preferences_comboBox_->signal_changed ().connect
    (sigc::mem_fun (
		    *this,
		    &DialogPreferences::dialog_preferences_changed));

  pdialog_preferences_comboBox_->set_active (0);

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
