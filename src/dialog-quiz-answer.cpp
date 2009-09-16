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
  dialog_quiz_front_->hide ();
  delete dialog_quiz_front_; 
  pdialog_quiz_answer_window_->hide ();
  new DialogQuizBack (quiz_, this);
}

