//-*-c++-*-
/* quiz.h
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
#ifndef QUIZ_H_
#define QUIZ_H_

#include<glibmm/ustring.h>
#include<map>
#include"card.h"
#include"dialog-quiz-result.h"
#include"package.h"

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
  unsigned int quiz_score (void) const throw ();
  unsigned int old_score (void) const throw ();
  const Glib::ustring& category (void) const throw ();
private:
  typedef std::map<unsigned int, Card> Quiz_cards;
  Quiz_cards quiz_cards;
  mutable Quiz_cards::const_iterator index;
  Quiz_cards::const_iterator end;
  Package* pkg_;
  mutable unsigned int old_score_;
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
  update_result ();
  new DialogQuizResult (this);
}

inline unsigned int
Quiz::quiz_score (void) const throw ()
{
  return right_ * (pkg_->score () / pkg_->num_cards ());
}

inline unsigned int
Quiz::old_score (void) const throw ()
{
  return old_score_;
}

inline const Glib::ustring&
Quiz::category (void) const throw ()
{
  return pkg_->category ();
}

#endif //QUIZ_H_
