//-*-c++-*-
#ifndef DIALOG_PREFERENCES_H_
#define DIALOG_PREFERENCES_H_

#include<gtkmm/builder.h>
#include<gtkmm/window.h>
#include<gtkmm/button.h>
#include<gtkmm/label.h>
#include<gtkmm/combobox.h>
#include<gtkmm/liststore.h>

class ETangoCardsApplet;

class DialogPreferences {
public:
  DialogPreferences (void) throw ();
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
