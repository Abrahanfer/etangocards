//-*-c++-*-

#ifndef DIALOG_CREATION_PACKAGE_H_
#define DIALOG_CREATION_PACKAGE_H_

#include<gtkmm/window.h>
#include<gtkmm/button.h>

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
