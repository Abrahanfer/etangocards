//-*-c++-*-
/* dialog-quiz-front.h
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
#ifndef DIALOG_QUIZ_FRONT_H_
#define DIALOG_QUIZ_FRONT_H_

#include<gtkmm/builder.h>
#include<gtkmm/window.h>
#include<gtkmm/toolbutton.h>
#include<gtkmm/textview.h>
#include<gtkmm/textbuffer.h>
#include"quiz.h"
#include"main.h"
#include"dialog-quiz-answer.h"

class DialogQuizFront {
public:
  DialogQuizFront (const Quiz*) throw ();
  void dialog_quiz_front_question (void) throw ();
  void hide (void) const throw ();
private:
  const Quiz* quiz_;
  Glib::RefPtr<Gtk::Builder> pdialog_quiz_front_;
  Gtk::Window* pdialog_quiz_front_window_;
  Gtk::ToolButton* pdialog_quiz_front_question_;
  Gtk::Label* pdialog_quiz_front_lbl1_;
  Gtk::Label* pdialog_quiz_front_lbl2_;
  Gtk::Label* pdialog_quiz_front_lbl3_;
  Glib::RefPtr<Gtk::TextBuffer> ptextbuffer;
  Glib::RefPtr<Gtk::TextBuffer::Tag> tagFront;
  Gtk::TextView* pdialog_quiz_front_textview_;
};

inline void
DialogQuizFront::dialog_quiz_front_question (void) throw ()
{
  new DialogQuizAnswer(quiz_, this);
}

inline void
DialogQuizFront::hide (void) const throw ()
{
  pdialog_quiz_front_window_->hide ();
}

#endif //DIALOG_QUIZ_FRONT_H_
