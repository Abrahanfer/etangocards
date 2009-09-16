//-*-c++-*-
#ifndef DIALOG_QUIZ_FRONT_H_
#define DIALOG_QUIZ_FRONT_H_

#include<gtkmm/builder.h>
#include<gtkmm/window.h>
#include<gtkmm/toolbutton.h>
#include<gtkmm/textview.h>
#include<gtkmm/textbuffer.h>
#include"quiz.h"
#include"main.h"
#include"dialog-quiz-answer.h"

class DialogQuizFront {
public:
  DialogQuizFront (const Quiz*) throw ();
  void dialog_quiz_front_question (void) throw ();
  void hide (void) const throw ();
private:
  const Quiz* quiz_;
  Glib::RefPtr<Gtk::Builder> pdialog_quiz_front_;
  Gtk::Window* pdialog_quiz_front_window_;
  Gtk::ToolButton* pdialog_quiz_front_question_;
  Gtk::Label* pdialog_quiz_front_lbl1_;
  Gtk::Label* pdialog_quiz_front_lbl2_;
  Gtk::Label* pdialog_quiz_front_lbl3_;
  Glib::RefPtr<Gtk::TextBuffer> ptextbuffer;
  Glib::RefPtr<Gtk::TextBuffer::Tag> tagFront;
  Gtk::TextView* pdialog_quiz_front_textview_;
};

inline void
DialogQuizFront::dialog_quiz_front_question (void) throw ()
{
  new DialogQuizAnswer(quiz_, this);
}

inline void
DialogQuizFront::hide (void) const throw ()
{
  pdialog_quiz_front_window_->hide ();
}

#endif //DIALOG_QUIZ_FRONT_H_
