//-*-mode:c++-*-

#ifndef DIALOG_ALERT_PACKAGE_
#define DIALOG_ALERT_PACKAGE_

#include<gtkmm/builder.h>
//#include<gtkmm/window.h>
#include<gtkmm/dialog.h>
#include"main.h"

class DialogAlertPackage {
public:
  DialogAlertPackage (void) throw ();
  int showDialogAlertPackage (void) throw ();
private:
  Glib::RefPtr<Gtk::Builder> pdialog_alert_package_;
  Gtk::Dialog* pdialog_alert_package_window_;
};

#endif // DIALOG_ALERT_PACKAGE_
