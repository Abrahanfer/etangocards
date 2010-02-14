#include"dialog-alert-package.h"

DialogAlertPackage::DialogAlertPackage ()
  throw ()
{
  pdialog_alert_package_ = Gtk::Builder::create_from_file
    (FILE_UI_DIALOG_ALERT_PACKAGE);

  pdialog_alert_package_->get_widget ("dialog_alert_package_window",
				      pdialog_alert_package_window_);
  

  //pdialog_alert_package_window_-> signal_response (). connect 
  //(sigc::mem_fun(*this,
  //		   &pdialog_alert_package_window_->close));

    //pdialog_alert_package_window_-> show ();
  
  //Icon
  Glib::RefPtr<Gdk::Pixbuf> icon = Gdk::Pixbuf::create_from_file 
    (ICONS_ETANGOCARDS_32);
  pdialog_alert_package_window_->set_icon (icon);

}

int
DialogAlertPackage::showDialogAlertPackage (void)
  throw ()
{
  int result = pdialog_alert_package_window_->run ();

  switch (result) 
    {
    default:
      {
	return 0;
      }
      break;
    }
}
