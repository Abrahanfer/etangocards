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

/**
 * Class which control the Quiz mode.
 *
 * @author Abrahán Fernández Nieto
 * @version 1.0
 */
class Quiz {
public:

  /**
   * Constructor which create a quiz 
   *
   * @param filename path of package which be tested 
   */
  Quiz (const Glib::ustring&) throw ();

  /**
   * Method which hand callback for next card
   */
  void next_card (void) const throw ();

  /**
   * Method which return true if the quiz has more cards, 
   * else return false
   *
   * @return true if has cards, false else
   */
  bool has_next_card (void) const throw ();

  /**
   * Method which increase the quiz's index
   */
  void increse_index (void) const throw ();

  /**
   * Method which return the quiz's index as int
   *
   * @return quiz's index as int
   */
  int index_row_number (void) const throw ();

  /**
   * Method which return the card for quiz
   *
   * @return card for quiz
   */
  const Card& quiz_card (void) const throw ();

  /**
   * Method whiche return total cards in quiz
   *
   * @return total cards in quiz
   */
  int total (void) const throw ();

  /**
   * Method which increase the number for card 
   * correctly answered.
   */
  void card_right (void) const throw ();

  /**
   * Method which increase the number for card 
   * incorrectly answered.
   */
  void card_wrong (void) const throw ();

  /**
   * Method which show the results when the quiz finish
   */
  void result (void) const throw ();

  /**
   * Method which update the results for user.
   */
  void update_result (void) const throw ();

  /**
   * Method which return the score for this quiz
   *
   * @return score for this quiz
   */
  unsigned int quiz_score (void) const throw ();

  /**
   * Method which return the old user's score
   *
   * @return old user's score
   */
  unsigned int old_score (void) const throw ();

  /**
   * Method which return the category this quiz.
   *
   * @return category this quiz 
   */
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
