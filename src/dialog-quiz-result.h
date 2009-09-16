//-*-c++-*-
#ifndef DIALOG_QUIZ_RESULT_H_
#define DIALOG_QUIZ_RESULT_H_

#include<gtkmm/builder.h>
#include<gtkmm/window.h>
#include<gtkmm/label.h>
#include<gtkmm/button.h>

class Quiz;

class DialogQuizResult {
public:
  DialogQuizResult (const Quiz*) throw ();
  void dialog_quiz_result_accept (void) throw ();
private:
  const Quiz* quiz_;
  Glib::RefPtr<Gtk::Builder> pdialog_quiz_result_;
  Gtk::Window* pdialog_quiz_result_window_;
  Gtk::Label* pdialog_quiz_result_lbl_name_;
  Gtk::Label* pdialog_quiz_result_lbl_score_;
  Gtk::Label* pdialog_quiz_result_lbl_total_;
  Gtk::Button* pdialog_quiz_result_accept_;
};

#endif //DIALOG_QUIZ_RESULT_H_
