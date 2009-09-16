#include<sstream>
#include"dialog-quiz-back.h"
#include"package.h"

DialogQuizBack::DialogQuizBack (const Quiz* quiz,
				const DialogQuizAnswer* dialog_quiz_answer)
  throw ():
  quiz_ (quiz), dialog_quiz_answer_ (dialog_quiz_answer)
{
  pdialog_quiz_back_ = Gtk::Builder::create_from_file 
    (FILE_UI_DIALOG_QUIZ_BACK);

  pdialog_quiz_back_->get_widget ("dialog_quiz_back_lbl_choose",
				  pdialog_quiz_back_lbl_choose_);
  pdialog_quiz_back_lbl_choose_->set_label ("It's your answer correct? ");
 
  pdialog_quiz_back_->get_widget ("dialog_quiz_back_lbl1",
				  pdialog_quiz_back_lbl1_);
  std::ostringstream oss1;
  
  oss1 << quiz_->index_row_number ();
  pdialog_quiz_back_lbl1_->set_label (oss1.str ());
  
  pdialog_quiz_back_->get_widget ("dialog_quiz_back_lbl2",
				  pdialog_quiz_back_lbl2_);
  pdialog_quiz_back_lbl2_->set_label (" of ");

  pdialog_quiz_back_->get_widget ("dialog_quiz_back_lbl3",
				  pdialog_quiz_back_lbl3_);
  std::ostringstream oss2;
  
  oss2 << quiz_->total ();
  pdialog_quiz_back_lbl3_->set_label (oss2.str ());
 
  Glib::ustring user_answer_ 
    (dialog_quiz_answer_->user_answer ()->get_text ());

  ptextbuffer =
    Gtk::TextBuffer::create ();
  
  tagBack = ptextbuffer->create_tag ();
  
  tagBack->property_size_points () = 12;
  try
    {
      ptextbuffer->set_text ("\nCorrect answer:\n" + 
			     quiz_->quiz_card ().back () + 
			     "\nYour answer:\n" + user_answer_);
    }
  catch (Package::BadIndexCardsException bice)
    {//TODO, exception in dialog
    }
  ptextbuffer->apply_tag (tagBack, ptextbuffer->begin (), 
			  ptextbuffer->end ());

  pdialog_quiz_back_->get_widget ("dialog_quiz_back_textview",
				   pdialog_quiz_back_textview_);
  pdialog_quiz_back_textview_->set_buffer (ptextbuffer);

  pdialog_quiz_back_->get_widget ("dialog_quiz_back_button_no",
				    pdialog_quiz_back_no_);

  pdialog_quiz_back_no_->signal_clicked ().connect
    (sigc::mem_fun(
		   *this,
		   &DialogQuizBack::dialog_quiz_back_no));

  pdialog_quiz_back_->get_widget ("dialog_quiz_back_button_yes",
				    pdialog_quiz_back_yes_);

  pdialog_quiz_back_yes_->signal_clicked ().connect
    (sigc::mem_fun(
		   *this,
		   &DialogQuizBack::dialog_quiz_back_yes));

  pdialog_quiz_back_->get_widget ("dialog_quiz_back_window",
				   pdialog_quiz_back_window_);

  pdialog_quiz_back_window_->show ();
}

void
DialogQuizBack::dialog_quiz_back_no (void) throw ()
{
  quiz_->card_wrong ();
  quiz_->increse_index ();
  pdialog_quiz_back_window_->hide ();
  if (quiz_->has_next_card ())
    quiz_->next_card ();
  else
    quiz_->result ();
} 

void
DialogQuizBack::dialog_quiz_back_yes (void) throw ()
{
  quiz_->card_right ();
  quiz_->increse_index ();
  pdialog_quiz_back_window_->hide ();
  if (quiz_->has_next_card ())
    quiz_->next_card ();
  else
    quiz_->result ();
} 
