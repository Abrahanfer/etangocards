//-*-c++-*-
/* card.h
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

#ifndef CARD_H_
#define CARD_H_

#include<glibmm.h>

/**
 * <p>This class simulate the package's cards.</p>
 *
 * @author Abrahán Fernández Nieto
 * @version 1.0
 */
class Card {
public:

  /**
   * Default contructor
   */
  Card (void);

  /**
   * This constructor receive two parameters.
   *
   * @param f is a Glib::ustring
   * @param b is a Glib::ustring
   */
  Card (Glib::ustring, Glib::ustring);

  /**
   * Method which show the card.
   *
   * @return const Glib::ustring&
   */
  const Glib::ustring& show (void) const;

  /**
   * Method which show the card's front.
   *
   * @return const Glib::ustring&
   */
  const Glib::ustring& front (void) const;


  /**
   * Method which show the card's back.
   *
   * @return const Glib::ustring&
   */
  const Glib::ustring& back (void) const;


  /**
   * Method which return true if the card show the front, 
   * else return false.
   *
   * @return bool
   */
  bool is_front (void) const;
private:
  mutable bool is_front_;
  Glib::ustring front_;
  Glib::ustring back_;
};

inline 
Card::Card (void):
  is_front_(true)
{}

inline 
Card::Card (Glib::ustring f, Glib::ustring b):
  is_front_(true), front_(f), back_(b) 
{}

inline
const Glib::ustring&
Card::front (void) const
{
  return front_;
}

inline
const Glib::ustring&
Card::back (void) const
{
  return back_;
}

inline
bool
Card::is_front (void) const
{
  return is_front_;
}
#endif
