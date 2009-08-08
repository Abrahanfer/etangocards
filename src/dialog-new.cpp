#include<iostream>
#include<gtkmm/builder.h>
#include<gtkmm/toolbutton.h>
#include<gtkmm/textbuffer.h>
#include<gtkmm/textview.h>
#include<gtkmm/window.h>
#include"package.h"
#include"dialog-new.h"
#include"dialog-package.h"


DialogNew::DialogNew (Package* pkg, const DialogPackage* d_pkg):
  front_ (""), back_ (""), pkg_ (pkg), is_front_ (true), d_pkg_ (d_pkg)
{
  pdialog_new_ =
    Gtk::Builder::create_from_file ("../data/ui/dialog_new.ui");
    
    
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

  Glib::RefPtr<Gtk::TextBuffer> pdialog_new_textbuffer_ = 
    Gtk::TextBuffer::create ();

  pdialog_new_textview_ = 0;
  pdialog_new_->get_widget ("dialog_new_textview",
			    pdialog_new_textview_);

  pdialog_new_textview_->set_buffer (pdialog_new_textbuffer_);

  pdialog_new_window_ = 0;
  pdialog_new_->get_widget ("dialog_new_window",
			    pdialog_new_window_);

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
      is_front_ = false;
      pdialog_new_textbuffer_->set_text (back_);
      pdialog_new_textview_->set_buffer (pdialog_new_textbuffer_);
    }
  else
    {
      back_ = pdialog_new_textbuffer_->get_text ();
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
