/* dialog-alert-package.cpp
 *
 * Copyright (C) 2010 Abrahán Fernández Nieto
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
