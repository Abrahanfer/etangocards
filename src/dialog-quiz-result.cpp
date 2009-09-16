#include"dialog-quiz-result.h"
#include"main.h"

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
				    pdialog_quiz_result_lbl_name_);

  pdialog_quiz_result_lbl_name_->set_label ("0");

  pdialog_quiz_result_->get_widget ("dialog_quiz_result_lbl_total",
				    pdialog_quiz_result_lbl_name_);

  pdialog_quiz_result_lbl_name_->set_label ("0");

  pdialog_quiz_result_->get_widget ("dialog_quiz_result_accept",
				    pdialog_quiz_result_accept_);

  pdialog_quiz_result_accept_->signal_clicked ().connect
    (sigc::mem_fun(
		   *this,
		   &DialogQuizResult::dialog_quiz_result_accept));

  pdialog_quiz_result_->get_widget ("dialog_quiz_result_window",
				    pdialog_quiz_result_window_);

  pdialog_quiz_result_window_->show ();
}

void
DialogQuizResult::dialog_quiz_result_accept (void) throw ()
{
  pdialog_quiz_result_window_->hide ();
}
