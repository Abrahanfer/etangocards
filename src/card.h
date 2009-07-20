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

#include<string>

class Card {
public:
  Card(void);
  Card(std::string, std::string);
  void show(void) const;
private:
  std::string front_;
  std::string back_;
};

inline 
Card::Card (void) 
{}

inline 
Card::Card(std::string f, std::string b):
  front_(f), back_(b) 
{}

#endif
