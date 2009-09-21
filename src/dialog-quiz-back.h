//-*-c++-*-
/* dialog-quiz-back.h
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
#ifndef DIALOG_QUIZ_BACK_H_
#define DIALOG_QUIZ_BACK_H_

#include<gtkmm/builder.h>
#include<gtkmm/window.h>
#include<gtkmm/toolbutton.h>
#include<gtkmm/textview.h>
#include<gtkmm/textbuffer.h>
#include"quiz.h"
#include"dialog-quiz-answer.h"

/**
 * Class which hand window for card's back in Quiz mode.
 *
 * @author Abrahán Fernández Nieto
 * @version 1.0
 */
class DialogQuizBack {
public:

  /**
   * Constructor which receive two parameters.
   *
   * @param quiz pointer to Quiz object
   * @param dialog_quiz_answer pointer to DialogQuizAnswer object.
   */
  DialogQuizBack (const Quiz*, const DialogQuizAnswer*) throw ();

  /**
   * Method hand the signal no button clicked.
   */
  void dialog_quiz_back_no (void) throw ();

  /**
   * Method hand the signal yes button clicked.
   */
  void dialog_quiz_back_yes (void) throw ();
private:
  const Quiz* quiz_;
  const DialogQuizAnswer* dialog_quiz_answer_;
  Glib::RefPtr<Gtk::Builder> pdialog_quiz_back_;
  Gtk::Window* pdialog_quiz_back_window_;
  Glib::RefPtr<Gtk::TextBuffer> ptextbuffer;
  Glib::RefPtr<Gtk::TextBuffer::Tag> tagBack;
  Gtk::TextView* pdialog_quiz_back_textview_;
  Gtk::Label* pdialog_quiz_back_lbl_choose_;
  Gtk::Label* pdialog_quiz_back_lbl1_;
  Gtk::Label* pdialog_quiz_back_lbl2_;
  Gtk::Label* pdialog_quiz_back_lbl3_;
  Gtk::ToolButton* pdialog_quiz_back_no_;
  Gtk::ToolButton* pdialog_quiz_back_yes_;
};

#endif //DIALOG_QUIZ_BACK_H_
