//-*-c++-*-
#ifndef DIALOG_QUIZ_BACK_H_
#define DIALOG_QUIZ_BACK_H_

#include<gtkmm/builder.h>
#include<gtkmm/window.h>
#include<gtkmm/toolbutton.h>
#include<gtkmm/textview.h>
#include<gtkmm/textbuffer.h>
#include"quiz.h"
#include"dialog-quiz-answer.h"

class DialogQuizBack {
public:
  DialogQuizBack (const Quiz*, const DialogQuizAnswer*) throw ();
  void dialog_quiz_back_no (void) throw ();
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
