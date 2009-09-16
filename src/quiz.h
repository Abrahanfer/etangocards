//-*-c++-*-

#ifndef QUIZ_H_
#define QUIZ_H_

#include<glibmm/ustring.h>
#include<map>
#include"card.h"
#include"dialog-quiz-result.h"

class Package;

class Quiz {
public:
  Quiz (const Glib::ustring&) throw ();
  void next_card (void) const throw ();
  bool has_next_card (void) const throw ();
  void increse_index (void) const throw ();
  int index_row_number (void) const throw ();
  const Card& quiz_card (void) const throw ();
  int total (void) const throw ();
  void card_right (void) const throw ();
  void card_wrong (void) const throw ();
  void result (void) const throw ();
  void update_result (void) const throw ();
private:
  typedef std::map<unsigned int, Card> Quiz_cards;
  Quiz_cards quiz_cards;
  mutable Quiz_cards::const_iterator index;
  Quiz_cards::const_iterator end;
  Package* pkg_;
  mutable unsigned int index_row_number_;
  mutable unsigned int total_;
  mutable unsigned int right_;
  mutable unsigned int wrong_;
};

inline bool
Quiz::has_next_card (void) const throw ()
{
  return index != end;
}

inline void
Quiz::increse_index (void) const throw ()
{
  ++index;
  index_row_number_++;
}

inline int
Quiz::index_row_number (void) const throw ()
{
  return index_row_number_;
}

inline int
Quiz::total (void) const throw ()
{
  return total_;
}

inline const Card&
Quiz::quiz_card (void) const throw ()
{
  return index->second;
}

inline void
Quiz::card_right (void) const throw ()
{
  right_++;
}

inline void
Quiz::card_wrong (void) const throw ()
{
  wrong_++;
}

inline void
Quiz::result (void) const throw ()
{
  new DialogQuizResult (this);
  update_result ();
}

#endif //QUIZ_H_
