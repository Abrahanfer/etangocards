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

#include<glibmm.h>
#include<map>
#include"control-system.h"
#include"card.h"

class Package {
public:
  class BadIndexCardsException {};
  class BeginPackageException {};
  class EndPackageException {};
  class NotFoundPackageException {
  public:
    NotFoundPackageException (const Glib::ustring&);
    const Glib::ustring& what (void) const;
  private:
    Glib::ustring pkg_name_;
  };
  class BadPackageFileException {
  public:
    BadPackageFileException (const Glib::ustring&);
    const Glib::ustring& what (void) const;
  private:
    Glib::ustring pkg_name_;
  };
  typedef std::map<unsigned int, Card> Cards;
  Package (const std::string&) throw ();
  Package (const std::string&, bool) 
    throw (NotFoundPackageException, BadPackageFileException);
  void addCard (const Glib::ustring&, const Glib::ustring&) 
    throw ();
  const Card& showInitCard ()
    throw (BadIndexCardsException);
  const Card& showNextCard () 
    throw (EndPackageException);
  const Card& showPrevCard ()
    throw (BeginPackageException);
  const Card& showThisCard () const throw ();
  const Glib::ustring& name () const throw ();
  unsigned int num_cards () const throw ();
  unsigned int index_cards () const throw ();
  void serialization (const std::string&) throw ();
private:
  unsigned int num_cards_;
  unsigned int index_cards_;
  Cards cards;
  Glib::ustring name_;
};

inline
Package::NotFoundPackageException::NotFoundPackageException 
(const Glib::ustring& pkg_name): 
  pkg_name_(pkg_name)
{}

inline const Glib::ustring&
Package::NotFoundPackageException::what () const
{
  return pkg_name_;
}

inline
Package::BadPackageFileException::BadPackageFileException 
(const Glib::ustring& pkg_name):
  pkg_name_ (pkg_name)
{}

inline const Glib::ustring&
Package::BadPackageFileException::what () const
{
  return pkg_name_;
}

inline Package::Package (const std::string& str) throw ():
  num_cards_(0), index_cards_(0), name_(str) {}

inline const Card&
Package::showThisCard () const throw ()
{
  Cards::const_iterator pos = cards.find (index_cards_);
  return pos->second;
}

inline const Glib::ustring& 
Package::name() const throw ()
{
  return name_;
}

inline unsigned int
Package::num_cards () const throw ()
{
  return num_cards_;
}

inline unsigned int
Package::index_cards () const throw ()
{
  return index_cards_;
}
#endif
