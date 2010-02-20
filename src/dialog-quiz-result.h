//-*-c++-*-
/* dialog-quiz-result.h
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
#ifndef DIALOG_QUIZ_RESULT_H_
#define DIALOG_QUIZ_RESULT_H_

#include<gtkmm/builder.h>
#include<gtkmm/window.h>
#include<gtkmm/label.h>
#include<gtkmm/button.h>

class Quiz;

/**
 * Class which hand window for results of quiz in Quiz mode.
 *
 * @author Abrahán Fernández Nieto
 * @version 1.0
 */
class DialogQuizResult {
public:

  /**
   * Contructor which receive one parameter.
   *
   * @param quiz is a pointer to Quiz object.
   */
  DialogQuizResult (const Quiz*) throw ();

  /**
   * Method hand the signal accept button clicked.
   */
  void dialog_quiz_result_accept (void) throw ();
private:
  const Quiz* quiz_;
  Glib::RefPtr<Gtk::Builder> pdialog_quiz_result_;
  Gtk::Window* pdialog_quiz_result_window_;
  Gtk::Label* pdialog_quiz_result_lbl_name_;
  Gtk::Label* pdialog_quiz_result_lbl_score_;
  Gtk::Label* pdialog_quiz_result_lbl_total_;
  Gtk::Label* pdialog_quiz_result_lbl_category_;
  Gtk::Label* pdialog_quiz_result_lbl_range_;
  Gtk::Button* pdialog_quiz_result_accept_;
};

#endif //DIALOG_QUIZ_RESULT_H_
