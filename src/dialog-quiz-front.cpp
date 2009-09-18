/* dialog-quiz-front.cpp
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
#include"dialog-quiz-front.h"
#include"quiz.h"
#include"package.h"

DialogQuizFront::DialogQuizFront (const Quiz* quiz)
  throw ():
  quiz_ (quiz)
{
  pdialog_quiz_front_ = 
    Gtk::Builder::create_from_file (FILE_UI_DIALOG_QUIZ_FRONT);


  pdialog_quiz_front_lbl1_ = 0;
  pdialog_quiz_front_->get_widget ("dialog_quiz_front_lbl1",
				   pdialog_quiz_front_lbl1_);

  std::ostringstream oss1;

  oss1 << quiz_->index_row_number ();
  pdialog_quiz_front_lbl1_->set_label (oss1.str ());

  pdialog_quiz_front_lbl2_ = 0;
  pdialog_quiz_front_->get_widget ("dialog_quiz_front_lbl2",
				   pdialog_quiz_front_lbl2_);
  pdialog_quiz_front_lbl2_->set_label (" of ");


  pdialog_quiz_front_lbl3_ = 0;
  pdialog_quiz_front_->get_widget ("dialog_quiz_front_lbl3",
				   pdialog_quiz_front_lbl3_);

  std::ostringstream oss2;

  oss2 << quiz_->total ();
  pdialog_quiz_front_lbl3_->set_label (oss2.str ());

  pdialog_quiz_front_->get_widget ("dialog_quiz_front_question",
				   pdialog_quiz_front_question_);

  pdialog_quiz_front_question_->signal_clicked (). connect
    (sigc::mem_fun (
		    *this,
		    &DialogQuizFront::dialog_quiz_front_question));
  ptextbuffer =
    Gtk::TextBuffer::create ();
  
  tagFront = ptextbuffer->create_tag ();
  
  tagFront->property_size_points () = 16;
  try
    {
      ptextbuffer->set_text ("\n" + quiz_->quiz_card ().front ());
    }
  catch (Package::BadIndexCardsException bice)
    {//TODO, exception in dialog
    }
  ptextbuffer->apply_tag (tagFront, ptextbuffer->begin (), 
			  ptextbuffer->end ());

  pdialog_quiz_front_->get_widget ("dialog_quiz_front_textview",
				   pdialog_quiz_front_textview_);
  pdialog_quiz_front_textview_->set_buffer (ptextbuffer);

  pdialog_quiz_front_->get_widget ("dialog_quiz_front_window",
				   pdialog_quiz_front_window_);

  //icon
  Glib::RefPtr<Gdk::Pixbuf> icon = Gdk::Pixbuf::create_from_file 
    (ICONS_ETANGOCARDS_32);
  pdialog_quiz_front_window_->set_icon (icon);

  pdialog_quiz_front_window_->show ();
}
