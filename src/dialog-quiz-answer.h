//-*-c++-*-
#ifndef DIALOG_QUIZ_ANSWER_H_
#define DIALOG_QUIZ_ANSWER_H_

#include<gtkmm/builder.h>
#include<gtkmm/window.h>
#include<gtkmm/textview.h>
#include<gtkmm/textbuffer.h>
#include"quiz.h"
#include"main.h"

class DialogQuizFront;

class DialogQuizAnswer {
public:
  DialogQuizAnswer (const Quiz*, const DialogQuizFront*) throw ();
  void dialog_quiz_answer_cancel (void) throw ();
  void dialog_quiz_answer_accept (void) throw ();
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
