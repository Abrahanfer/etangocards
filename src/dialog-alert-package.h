//-*-mode:c++-*-
/* dialog-alert-package.h
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

#ifndef DIALOG_ALERT_PACKAGE_
#define DIALOG_ALERT_PACKAGE_

#include<gtkmm/builder.h>
#include<gtkmm/dialog.h>
#include"main.h"

/**
 * <p>This class construct a dialog for alert to users over a invalid
 * file package.</p>
 *
 * @author Abrahán Fernández Nieto
 * @version 1.0
 */
class DialogAlertPackage {
public:
  /**
   * Constructor for alert dialog.
   */
  DialogAlertPackage (void) throw ();

  /**
   * Method for show alert dialog.
   *
   * @return 0 all green, otherwise error
   */
  int showDialogAlertPackage (void) throw ();
private:
  Glib::RefPtr<Gtk::Builder> pdialog_alert_package_;
  Gtk::Dialog* pdialog_alert_package_window_;
};

#endif // DIALOG_ALERT_PACKAGE_
