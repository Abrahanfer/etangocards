/* dialog-quiz-result.cpp
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
#include"dialog-quiz-result.h"
#include"main.h"
#include"quiz.h"
#include"control-system.h"

DialogQuizResult::DialogQuizResult (const Quiz* quiz) 
  throw ():
  quiz_ (quiz)
{
  pdialog_quiz_result_ = Gtk::Builder::create_from_file 
    (FILE_UI_DIALOG_QUIZ_RESULT);

  pdialog_quiz_result_->get_widget ("dialog_quiz_result_lbl_name",
				    pdialog_quiz_result_lbl_name_);

  pdialog_quiz_result_lbl_name_->set_label (Glib::get_user_name ());

  pdialog_quiz_result_->get_widget ("dialog_quiz_result_lbl_score",
				    pdialog_quiz_result_lbl_score_);

  std::ostringstream oss1;
  oss1 << quiz_->quiz_score ();
  pdialog_quiz_result_lbl_score_->set_label (oss1.str ());

  pdialog_quiz_result_->get_widget ("dialog_quiz_result_lbl_total",
				    pdialog_quiz_result_lbl_total_);

  std::ostringstream oss2;
  oss2 << (quiz_->quiz_score () + quiz_->old_score ());
  pdialog_quiz_result_lbl_total_->set_label (oss2.str ());

  pdialog_quiz_result_->get_widget ("dialog_quiz_result_lbl_category",
				    pdialog_quiz_result_lbl_category_);

  pdialog_quiz_result_lbl_category_->set_label (quiz_->category ());

  pdialog_quiz_result_->get_widget ("dialog_quiz_result_lbl_range",
				    pdialog_quiz_result_lbl_range_);
  
  pdialog_quiz_result_lbl_range_->set_label 
  (ControlSystem::range_category (quiz_->category ()));

  pdialog_quiz_result_->get_widget ("dialog_quiz_result_accept",
				    pdialog_quiz_result_accept_);

  pdialog_quiz_result_accept_->signal_clicked ().connect
    (sigc::mem_fun(
		   *this,
		   &DialogQuizResult::dialog_quiz_result_accept));

  pdialog_quiz_result_->get_widget ("dialog_quiz_result_window",
				    pdialog_quiz_result_window_);

  //icon
  Glib::RefPtr<Gdk::Pixbuf> icon = Gdk::Pixbuf::create_from_file 
    (ICONS_ETANGOCARDS_32);
  pdialog_quiz_result_window_->set_icon (icon);

  pdialog_quiz_result_window_->show ();
}

void
DialogQuizResult::dialog_quiz_result_accept (void) throw ()
{
  pdialog_quiz_result_window_->hide ();
}
