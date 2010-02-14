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
#include<iostream>
#include<sstream>
#include<gtkmm/main.h>
#include<gtkmm/builder.h>
#include<gtkmm/window.h>
#include<gtkmm/button.h>
#include<gtkmm/textview.h>
#include<gtkmm/textbuffer.h>
#include"control-system.h"
#include"dialog-package.h"
#include"dialog-new.h"

DialogPackage::DialogPackages DialogPackage::dialogPackages;

bool DialogPackage::allWindowsHide = false;

DialogPackage::DialogPackage (Package *pkg):
  pkg_(pkg)
{
  pdialog_package_ = 
    Gtk::Builder::create_from_file (FILE_UI_DIALOG_PACKAGE);


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

  tagFront = ptextbuffer->create_tag ();
  tagBack = ptextbuffer->create_tag ();

  tagFront->property_size_points () = 16;
  tagBack->property_size_points () = 12;
  try
    {
      ptextbuffer->set_text ("\n" + pkg_->showInitCard ().front ());
    }
  catch (Package::BadIndexCardsException bice)
    {//TODO, exception in dialog
    }
  ptextbuffer->apply_tag (tagFront, ptextbuffer->begin (), 
			  ptextbuffer->end ());
  tagTable =  ptextbuffer->get_tag_table ();
  pdialog_package_textview_ = 0;
  pdialog_package_->get_widget ("dialog_package_textview",
				pdialog_package_textview_);
  pdialog_package_textview_->set_buffer (ptextbuffer);

  pdialog_package_window_ = 0;
  pdialog_package_->get_widget ("dialog_package_window",
				pdialog_package_window_);
  pdialog_package_window_->signal_delete_event ().connect
    (sigc::mem_fun(
		   *this,
		   &DialogPackage::dialog_package_close));
  //icon
  Glib::RefPtr<Gdk::Pixbuf> icon = Gdk::Pixbuf::create_from_file 
    (ICONS_ETANGOCARDS_32);
  pdialog_package_window_->set_icon (icon);

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
      ptextbuffer->set_text ("\n" + pkg_->showPrevCard ().front ());
    }
  catch (Package::BeginPackageException bpe) 
    {
      return;
    }
  ptextbuffer->apply_tag (tagFront, ptextbuffer->begin (), 
			  ptextbuffer->end ());
  std::ostringstream oss1;

  oss1 << pkg_->index_cards ();
  pdialog_package_lbl1_->set_text (oss1.str ());
}

void
DialogPackage::dialog_package_next_card (void) throw ()
{
  try
    {
      ptextbuffer->set_text ("\n" + pkg_->showNextCard ().front ());
    }
  catch (Package::EndPackageException epe) 
    {
      return;
    }
  ptextbuffer->apply_tag (tagFront, ptextbuffer->begin (), 
			  ptextbuffer->end ());
  std::ostringstream oss1;

  oss1 << pkg_->index_cards ();
  pdialog_package_lbl1_->set_text (oss1.str ());
}

void
DialogPackage::dialog_package_show (void) throw ()
{
  ptextbuffer->set_text ("\n" + pkg_->showThisCard ().show ());

  if (pkg_->showThisCard ().is_front ())
    {
      ptextbuffer->apply_tag (tagFront, ptextbuffer->begin (), 
			      ptextbuffer->end ());
    }
  else
    {
      ptextbuffer->apply_tag (tagBack, ptextbuffer->begin (), 
			      ptextbuffer->end ());
    }
}

void
DialogPackage::refresh_num_cards (void) const throw ()
{
  std::ostringstream oss;

  oss << pkg_->num_cards ();
  pdialog_package_lbl3_->set_text (oss.str ());
}

bool
DialogPackage::dialog_package_close (GdkEventAny *) throw ()
{
  pdialog_package_window_->hide ();
  pkg_->serialization ();
  ControlSystem::eliminatePackage (pkg_);
  dialogPackages.erase (this);
  ControlSystem::serializeSystem ();

  return true;
}

void
DialogPackage::dialog_package_hide_windows (void) throw ()
{
  DialogPackages::iterator i;
  for (i = dialogPackages.begin (); i != dialogPackages.end (); ++i)
    (*i)->hide ();

}

void
DialogPackage::dialog_package_show_windows (void) throw ()
{
      DialogPackages::iterator i;
      for (i = dialogPackages.begin (); i != dialogPackages.end (); ++i)
	(*i)->show ();
}
