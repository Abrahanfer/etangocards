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

class Card {
public:
  Card (void);
  Card (Glib::ustring, Glib::ustring);
  const Glib::ustring& show (void) const;
  const Glib::ustring& front (void) const;
  const Glib::ustring& back (void) const;
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
#endif
