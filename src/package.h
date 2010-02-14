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
//#include"control-system.h"
#include"card.h"

/**
 * This class hold the information of a package.
 *
 * @author Abrahán Fernández Nieto
 * @version 1.0
 */
class Package {
public:
  /// Typedef which represent relations between ranges 
  /// and puntuations.
  typedef std::map<Glib::ustring, unsigned int> Ranges;

  /**
   * Class exception throwed when a error in package's 
   * index is detected.
   *
   * @author Abrahán Fernández Nieto
   * @version 1.0
   */
  class BadIndexCardsException {};

  /**
   * Class exception throwed when the package's begin is detected.
   *
   * @author Abrahán Fernández Nieto
   * @version 1.0
   */
  class BeginPackageException {};

  /**
   * Class exception throwed when the package's end is detected.
   *
   * @author Abrahán Fernández Nieto
   * @version 1.0
   */
  class EndPackageException {};

  /**
   * Class exception throwed when the package is not found.
   *
   * @author Abrahán Fernández Nieto
   * @version 1.0
   */
  class NotFoundPackageException {
  public:

    /**
     * Constructor
     *
     * @param pkg_name package's name
     */
    NotFoundPackageException (const Glib::ustring&);

    /**
     * Method which return package's name
     *
     * @return package's name
     */
    const Glib::ustring& what (void) const;
  private:
    Glib::ustring pkg_name_;
  };

  /**
   * Class exception throwed when the package is corrupted.
   *
   * @author Abrahán Fernández Nieto
   * @version 1.0
   */
  class BadPackageFileException {
  public:

    /**
     * Constructor
     *
     * @param pkg_name package's name
     */
    BadPackageFileException (const Glib::ustring&);

    /**
     * Method which return package's name
     *
     * @return package's name
     */
    const Glib::ustring& what (void) const;
  private:
    Glib::ustring pkg_name_;
  };

  /**
   * Typedef for cards stocks in package.
   */
  typedef std::map<unsigned int, Card> Cards;

  /**
   * Constructor which receive one parameters
   *
   * @param name is package name
   */
  Package (const Glib::ustring&)
    throw ();

  /**
   * Constructor which receive five parameters.
   *
   * @param name package name
   * @param path path where be saved
   * @param category category which belong
   * @param score punctuation this package
   * @param range range which belong 
   */
  Package (const Glib::ustring&, const Glib::ustring&, const Glib::ustring&,
	   const Glib::ustring&, int)
    throw ();

  /**
   * Constructor which receive three parameters.
   *
   * @param pathname path where be the package
   * @param index_cards index for view
   * @param isXml boolean always true
   */
  Package (const std::string&, unsigned int, bool) 
    throw (NotFoundPackageException, BadPackageFileException);

  /**
   * Method for add card to package.
   *
   * @param front is card's front
   * @param back is card's back
   */
  void addCard (const Glib::ustring&, const Glib::ustring&) 
    throw ();

  /**
   * Method which show de init card
   *
   * @return the init card
   */
  const Card& showInitCard ()
    throw (BadIndexCardsException);

  /**
   * Method which show de next card
   *
   * @return the next card
   */
  const Card& showNextCard () 
    throw (EndPackageException);

  /**
   * Method which show de preview card
   *
   * @return the preview card
   */
  const Card& showPrevCard ()
    throw (BeginPackageException);

  /**
   * Method which show de actual card
   *
   * @return the actual card
   */
  const Card& showThisCard () const throw ();

  /**
   * Method which return the package's name.
   *
   * @return pacakge's name
   */
  const Glib::ustring& name () const throw ();

  /**
   * Method which return the package's number of cards.
   *
   * @return nunmbers of cards
   */
  unsigned int num_cards () const throw ();

  /**
   * Method which return the package's index.
   *
   * @return package's index
   */
  unsigned int index_cards () const throw ();

  /**
   * Method which return the package's path.
   *
   * @return pacakge's path
   */
  const Glib::ustring& path () const throw ();

  /**
   * Method which serialize the pacakge.
   */
  void serialization () throw ();

  /**
   * Operator overload which return the card in the 
   * position refered.
   *
   * @param i card's position in the package
   * @return card in that position 
   */
  const Card& operator[] (unsigned int) throw ();

  /**
   * Method which return the package's category.
   *
   * @return pacakge's category
   */
  const Glib::ustring& category (void) const throw ();

  /**
   * Method which return the package's score.
   *
   * @return pacakge's score
   */
  unsigned int score (void) const throw ();

  /**
   * Construstor of ranges.
   */
  static void create_ranges (void) throw ();

  /**
   * Method which return all ranges.
   *
   * @return all ranges
   */
  static const Ranges& ranges (void) throw ();

  /**
   * Method which return the package's range.
   *
   * @return pacakge's range
   */
  const Glib::ustring& range (void) const throw ();
private:
  static Ranges ranges_;
  Glib::ustring range_;
  Glib::ustring path_;
  Glib::ustring name_;
  Glib::ustring category_;
  unsigned int score_;
  unsigned int num_cards_;
  unsigned int index_cards_;
  Cards cards;
};

inline
Package::NotFoundPackageException::NotFoundPackageException 
(const Glib::ustring& pkg_name):
  pkg_name_ (pkg_name)
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

inline
Package::Package (const Glib::ustring& name)
  throw ():
  name_ (name)
{}

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

inline const Glib::ustring&
Package::path () const throw ()
{
  return path_;
}

inline const Glib::ustring&
Package::category (void) const throw ()
{
  return category_;
}

inline unsigned int
Package::score (void) const throw ()
{
  return score_;
}

inline const Package::Ranges&
Package::ranges (void) throw ()
{
  return ranges_;
}

inline const Glib::ustring&
Package::range (void) const throw ()
{
  return range_;
}
#endif //PACKAGE_H_
