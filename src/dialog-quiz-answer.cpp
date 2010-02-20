/* dialog-quiz-answer.cpp
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
#include"dialog-quiz-answer.h"
#include"dialog-quiz-front.h"
#include"dialog-quiz-back.h"

DialogQuizAnswer::DialogQuizAnswer (const Quiz* quiz,
				    const DialogQuizFront* dialog_quiz_front)
  throw ():
  quiz_ (quiz), dialog_quiz_front_ (dialog_quiz_front)
{
  pdialog_quiz_answer_ = 
    Gtk::Builder::create_from_file (FILE_UI_DIALOG_QUIZ_ANSWER);

  Glib::RefPtr<Gtk::TextBuffer> ptextbuffer = 
    Gtk::TextBuffer::create ();

  pdialog_quiz_answer_->get_widget ("dialog_quiz_answer_textview",
				    pdialog_quiz_answer_textview_);

  pdialog_quiz_answer_textview_->set_buffer 
    (ptextbuffer);

  pdialog_quiz_answer_->get_widget ("dialog_quiz_answer_button_cancel",
				    pdialog_quiz_answer_cancel_);

  pdialog_quiz_answer_cancel_->signal_clicked ().connect
    (sigc::mem_fun(
		   *this,
		   &DialogQuizAnswer::dialog_quiz_answer_cancel));

  pdialog_quiz_answer_->get_widget ("dialog_quiz_answer_button_accept",
				    pdialog_quiz_answer_accept_);

  pdialog_quiz_answer_accept_->signal_clicked ().connect
    (sigc::mem_fun(
		   *this,
		   &DialogQuizAnswer::dialog_quiz_answer_accept));

  pdialog_quiz_answer_->get_widget ("dialog_quiz_answer_window",
				    pdialog_quiz_answer_window_);

  //icon
  Glib::RefPtr<Gdk::Pixbuf> icon = Gdk::Pixbuf::create_from_file 
    (ICONS_ETANGOCARDS_32);
  pdialog_quiz_answer_window_->set_icon (icon);

  pdialog_quiz_answer_window_->show ();
}

void
DialogQuizAnswer::dialog_quiz_answer_cancel (void) throw ()
{
  pdialog_quiz_answer_window_->hide ();
}

void
DialogQuizAnswer::dialog_quiz_answer_accept (void) throw ()
{
  new DialogQuizBack (quiz_, this);
  dialog_quiz_front_->hide ();
  pdialog_quiz_answer_window_->hide ();
  delete dialog_quiz_front_; 
}

