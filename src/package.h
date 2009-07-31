//-*-c++-*-
/* package.h
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
#ifndef PACKAGE_H_
#define PACKAGE_H_

#include<string>
#include<map>
#include"control-system.h"
#include"card.h"

class Package {
public:
  class BadIndexCardsException {};
  class BeginPackageException {};
  class EndPackageException {};
  class NotFoundPackageException {};
  typedef std::map<unsigned int, Card> Cards;
  Package (const std::string&) throw ();
  Package (const std::string&, bool) 
    throw (NotFoundPackageException);
  void addCard () throw ();
  void showInitCard ()
    throw (BadIndexCardsException);
  void showNextCard () 
    throw (EndPackageException);
  void showPrevCard ()
    throw (BeginPackageException);
  const std::string& name () const throw ();
  void serialization (const std::string&) throw ();
private:
  unsigned int num_cards_;
  unsigned int index_cards_;
  Cards cards;
  std::string name_;
};

inline Package::Package (const std::string& str) throw ():
  num_cards_(0), index_cards_(0), name_(str) {}

inline const std::string& Package::name() const throw ()
{
  return name_;
}

#endif
