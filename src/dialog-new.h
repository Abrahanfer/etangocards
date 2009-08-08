//-*-c++-*-

#ifndef DIALOG_NEW_H_
#define DIALOG_NEW_H_

#include<gtkmm/builder.h>
#include<gtkmm/window.h>
#include<gtkmm/toolbutton.h>
#include<gtkmm/textview.h>
#include"package.h"

class DialogPackage;

class DialogNew {
public:
  DialogNew (Package*, const DialogPackage*);
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
};

#endif
