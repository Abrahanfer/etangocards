/* dialog-package.cpp
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
#include<sstream>
#include<gtkmm/main.h>
#include<gtkmm/builder.h>
#include<gtkmm/window.h>
#include<gtkmm/button.h>
#include<gtkmm/textview.h>
#include<gtkmm/textbuffer.h>
#include"dialog-package.h"
#include"dialog-new.h"

DialogPackage::DialogPackage (Package *pkg):
  pkg_(pkg)
{
  pdialog_package_ = 
    Gtk::Builder::create_from_file ("../data/ui/dialog_package.ui");

  pdialog_package_lbl1_ = 0;
  pdialog_package_->get_widget ("dialog_package_lbl1",
				 pdialog_package_lbl1_);

  std::ostringstream oss1;

  oss1 << pkg_->index_cards ();
  pdialog_package_lbl1_->set_text (oss1.str ());

  pdialog_package_lbl3_ = 0;
  pdialog_package_->get_widget ("dialog_package_lbl3",
				 pdialog_package_lbl3_);

  std::ostringstream oss2;

  oss2 << pkg_->num_cards ();
  pdialog_package_lbl3_->set_text (oss2.str ());

  pdialog_package_new_ = 0;
  pdialog_package_->get_widget ("dialog_package_new",
				pdialog_package_new_);

  pdialog_package_new_->signal_clicked (). connect
    (sigc::mem_fun (
		    *this,
		    &DialogPackage::dialog_package_new_card));

  pdialog_package_prev_ = 0;
  pdialog_package_->get_widget ("dialog_package_prev",
				pdialog_package_prev_);


  pdialog_package_prev_->signal_clicked ().connect
    (sigc::mem_fun(
		   *this, 
		   &DialogPackage::dialog_package_prev_card));

  pdialog_package_next_ = 0;
  pdialog_package_->get_widget ("dialog_package_next",
				pdialog_package_next_);

  pdialog_package_next_->signal_clicked ().connect
    (sigc::mem_fun(
		   *this, 
		   &DialogPackage::dialog_package_next_card));

  pdialog_package_show_ = 0;
  pdialog_package_->get_widget ("dialog_package_show",
				pdialog_package_show_);

  pdialog_package_show_->signal_clicked ().connect
    (sigc::mem_fun(
		   *this, 
		   &DialogPackage::dialog_package_show));

  ptextbuffer =
    Gtk::TextBuffer::create ();
  try
    {
      ptextbuffer->set_text (pkg_->showInitCard ().front ());
    }
  catch (Package::BadIndexCardsException bice)
    {//TODO, exception in dialog
    }
  pdialog_package_textview_ = 0;
  pdialog_package_->get_widget ("dialog_package_textview",
				pdialog_package_textview_);
  pdialog_package_textview_->set_buffer (ptextbuffer);

  pdialog_package_window_ = 0;
  pdialog_package_->get_widget ("dialog_package_window",
				pdialog_package_window_);
 

  pdialog_package_window_->show ();
}

DialogPackage::~DialogPackage ()
{
  delete pdialog_package_prev_;
  delete pdialog_package_next_;
  delete pdialog_package_show_;
  delete pdialog_package_textview_;
  delete pdialog_package_window_;
}

void
DialogPackage::dialog_package_prev_card (void) throw ()
{
  try
    {
      ptextbuffer->set_text (pkg_->showPrevCard ().front ());
    }
  catch (Package::BeginPackageException bpe) 
    {
      return;
    }
  std::ostringstream oss1;

  oss1 << pkg_->index_cards ();
  pdialog_package_lbl1_->set_text (oss1.str ());
}

void
DialogPackage::dialog_package_next_card (void) throw ()
{
  try
    {
      ptextbuffer->set_text (pkg_->showNextCard ().front ());
    }
  catch (Package::EndPackageException epe) 
    {
      return;
    }
  std::ostringstream oss1;

  oss1 << pkg_->index_cards ();
  pdialog_package_lbl1_->set_text (oss1.str ());
}

void
DialogPackage::dialog_package_show (void) throw ()
{
  ptextbuffer->set_text (pkg_->showThisCard ().show ());
}

void
DialogPackage::refresh_num_cards (void) const throw ()
{
  std::ostringstream oss;

  oss << pkg_->num_cards ();
  pdialog_package_lbl3_->set_text (oss.str ());
}
