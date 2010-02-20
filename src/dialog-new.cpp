/* dialog-new.cpp
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

#include<gtkmm/builder.h>
#include<gtkmm/toolbutton.h>
#include<gtkmm/textbuffer.h>
#include<gtkmm/textview.h>
#include<gtkmm/window.h>
#include"package.h"
#include"dialog-new.h"
#include"dialog-package.h"
#include"main.h"


DialogNew::DialogNew (Package* pkg, const DialogPackage* d_pkg):
  front_ (""), back_ (""), pkg_ (pkg), is_front_ (true), d_pkg_ (d_pkg)
{
  pdialog_new_ =
    Gtk::Builder::create_from_file (FILE_UI_DIALOG_NEW);
    
    
  pdialog_new_save_button_ = 0;
  pdialog_new_->get_widget ("dialog_new_save_button",
			    pdialog_new_save_button_);
  
  pdialog_new_save_button_->signal_clicked ().connect
    (sigc::mem_fun(
		   *this,
		   &DialogNew::dialog_new_save_card));
  
  pdialog_new_information_button_ = 0;
  pdialog_new_->get_widget ("dialog_new_information_button",
			    pdialog_new_information_button_);

  pdialog_new_information_button_->signal_clicked ().connect
    (sigc::mem_fun(
		   *this,
		   &DialogNew::dialog_new_information));

  pdialog_new_->get_widget ("dialog_new_lbl",
			    pdialog_new_lbl_);
  pdialog_new_lbl_->set_label ("front");

  Glib::RefPtr<Gtk::TextBuffer> pdialog_new_textbuffer_ = 
    Gtk::TextBuffer::create ();

  pdialog_new_textview_ = 0;
  pdialog_new_->get_widget ("dialog_new_textview",
			    pdialog_new_textview_);

  pdialog_new_textview_->set_buffer (pdialog_new_textbuffer_);

  pdialog_new_window_ = 0;
  pdialog_new_->get_widget ("dialog_new_window",
			    pdialog_new_window_);
  //show icons
  Glib::RefPtr<Gdk::Pixbuf> icon = Gdk::Pixbuf::create_from_file 
    (ICONS_ETANGOCARDS_32);
  pdialog_new_window_->set_icon (icon);
  pdialog_new_window_->show ();
  
}

void
DialogNew::dialog_new_save_card (void)
{
  Glib::RefPtr<Gtk::TextBuffer> pdialog_new_textbuffer_ = 
    pdialog_new_textview_->get_buffer ();

  if (is_front_)
    front_ = pdialog_new_textbuffer_->get_text ();
  else
    back_ = pdialog_new_textbuffer_->get_text ();

  pkg_->addCard (front_, back_);

  pdialog_new_window_->hide ();

  d_pkg_->refresh_num_cards ();
}

void
DialogNew::dialog_new_information (void)
{
  Glib::RefPtr<Gtk::TextBuffer> pdialog_new_textbuffer_ = 
    pdialog_new_textview_->get_buffer ();

  if (is_front_)
    {
      front_ = pdialog_new_textbuffer_->get_text ();
      pdialog_new_lbl_->set_label ("back");
      is_front_ = false;
      pdialog_new_textbuffer_->set_text (back_);
      pdialog_new_textview_->set_buffer (pdialog_new_textbuffer_);
    }
  else
    {
      back_ = pdialog_new_textbuffer_->get_text ();
     pdialog_new_lbl_->set_label ("front");
      is_front_ = true;
      pdialog_new_textbuffer_->set_text (front_);
      pdialog_new_textview_->set_buffer (pdialog_new_textbuffer_);
    }
}

DialogNew::~DialogNew (void)
{
  delete pdialog_new_save_button_;
  delete pdialog_new_information_button_;
  delete pdialog_new_textview_;
  delete pdialog_new_window_;
}
