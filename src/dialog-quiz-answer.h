//-*-c++-*-
/* dialog-quiz-answer.h
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
#ifndef DIALOG_QUIZ_ANSWER_H_
#define DIALOG_QUIZ_ANSWER_H_

#include<gtkmm/builder.h>
#include<gtkmm/window.h>
#include<gtkmm/textview.h>
#include<gtkmm/textbuffer.h>
#include"quiz.h"
#include"main.h"

class DialogQuizFront;

/**
 * This class is part of Quiz mode feature. Manage the windows 
 * of quiz's answer.
 *
 *
 * @author Abrahán Fernández Nieto
 * @version 1.0
 */
class DialogQuizAnswer {
public:

  /**
   * Contructor which receive two parameters.
   *
   * @param quiz pointer to Quiz object.
   * @param dialog_quiz_front pointer to DialogQuizFront 
   * object which call to this contructor.
   */
  DialogQuizAnswer (const Quiz*, const DialogQuizFront*) throw ();

  /**
   * Method hand the signal cancel button clicked.
   */
  void dialog_quiz_answer_cancel (void) throw ();

  /**
   * Method hand the signal accept button clicked.
   */
  void dialog_quiz_answer_accept (void) throw ();

  /**
   * Method which return the user's answer.
   *
   * @return the user's answer.
   */
  Glib::RefPtr<Gtk::TextBuffer> user_answer (void) const throw ();
private:
  const Quiz* quiz_;
  const DialogQuizFront* dialog_quiz_front_;
  Glib::RefPtr<Gtk::Builder> pdialog_quiz_answer_;
  Gtk::Window* pdialog_quiz_answer_window_;
  Glib::RefPtr<Gtk::TextBuffer> ptextbuffer;
  Gtk::TextView* pdialog_quiz_answer_textview_;
  Gtk::Button* pdialog_quiz_answer_cancel_;
  Gtk::Button* pdialog_quiz_answer_accept_;
};

inline Glib::RefPtr<Gtk::TextBuffer>
DialogQuizAnswer::user_answer (void) const throw ()
{
  return pdialog_quiz_answer_textview_->get_buffer ();
}

#endif //DIALOG_QUIZ_ANSWER_H_
