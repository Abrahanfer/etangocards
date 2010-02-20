//-*-c++-*-
/* control-system.h
 *
 * Copyright (C) by 2009, 2010 Abrahán Fernández Nieto
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
#ifndef CONTROL_SYSTEM_H_
#define CONTROL_SYSTEM_H_

#include<glibmm.h>
#include<map>
#include<set>
#include"package.h"

class Package;

/**
 * <p>This class control the whole system.</p>
 *
 * @author Abrahán Fernández Nieto
 * @version 1.0
 */
class ControlSystem {
public:

  ///This typedef relations Ranges with Categories
  typedef std::map<Glib::ustring, Glib::ustring> RangeCategories;

  ///This typedef realtions Categories with puntuation
  typedef std::map<Glib::ustring, unsigned int> Categories;

  ///This typedef is a set of Package*
  typedef std::set<Package *> Packages;

  /**
   * <p>This exception class is throwed when detect a 
   * repeat package.</p>
   *
   * @author Abrahán Fernández Nieto
   * @version 1.0
   */
  class RepeatPackageException {
  public:

    /**
     * RepeatPackageException constructor.
     *
     * @param str is std::string set with package's name
     */
    explicit RepeatPackageException (const std::string&);

    /**
     * Method for to show the package's name
     *
     * @return the package's name
     */
    const std::string& packageName (void) const;
  private:
    std::string packageName_;
  };

  /**
   * <p>This exception class is throwed when no package 
   * to show.</p>
   *
   * @author Abrahán Fernández Nieto
   * @version 1.0
   */
  class NoPackagesException {};

  /**
   * <p>This exception class is throwed when the package required 
   * it's not fount.</p>
   *
   * @author Abrahán Fernández Nieto
   * @version 1.0
   */
  class NoPackageFoundException {
  public:

    /**
     * NoPackageFoundException constructor.
     *
     * @param str is std::string set with package's name
     */
    explicit NoPackageFoundException (const std::string&);

    /**
     * Method for to show the package's name
     *
     * @return the pacakge's name
     */
    const std::string& packageName (void) const;
  private:
    std::string packageName_;
  };

  /**
   * This method create the stock package.
   *
   * @param pkg is Package*
   */
  static void associate (Package*) 
    throw ();
  //static const Packages& associate (void) const;
  //const Package& LoadPackage (const std::string&) const
  //throw (NoPackagesException, NoPackageFoundException);

  /**
   * This method load a package.
   *
   * @param str is a path of package
   * @param index_cards is a index for package
   */
  static Package* LoadPackage (const std::string&, unsigned int)
    throw (Package::BadPackageFileException);
  /*    throw (Package::NotFoundPackageException, 
	   Package::BadPackageFileException,
	   RepeatPackageException);*/

  /**
   * This method show the package by cout
   *
   * @param str is the package's name 
   */
  //void showPackage (const std::string&);

  /**
   * This method create a new package.
   *
   * @param str is a package's name
   */
  void NewPackage (const std::string&);

  /**
   * This method serialize whole system. 
   */
  static void serializeSystem ();

  /**
   * This method erase a package of system.
   *
   * @param pkg is pointer to package
   */
  static void eliminatePackage (Package*) throw ();

  /**
   * This method save the configuration of whole system.
   *
   */
  static void serializeConfigurationFile (void) throw ();

  /**
   * This method return the range in a determinate category.
   *
   * @param name_category is a category's name
   * @return the range
   */
  static const Glib::ustring& range_category (const Glib::ustring&)
    throw ();

  /**
   * This observer method return de path of configuration
   * file be saved.
   *
   * @return The path of configuration file be saved
   */

  static const std::string& path (void) throw (); 
  /**
   * Destructor
   */
  ~ControlSystem (void);

  ///Path when save the configuration
  static std::string path_;

  ///attribute for relations between ranges and categories
  static RangeCategories range_categories_;

  ///attribute for relations between categories and puntuation
  static Categories categories;
private:
  static Packages packages;
};

/*inline const ControlSystem::Packages& 
ControlSystem::associate (void) const
{
  return packages;
  }*/

inline 
ControlSystem::RepeatPackageException::RepeatPackageException(
					   const std::string& str):
  packageName_(str) {}

inline const std::string& 
ControlSystem::RepeatPackageException::packageName() const
{
  return packageName_;
}

inline 
ControlSystem::NoPackageFoundException::NoPackageFoundException(
					   const std::string& str):
  packageName_(str) {}

inline const std::string& 
ControlSystem::NoPackageFoundException::packageName() const
{
  return packageName_;
}

inline const Glib::ustring&
ControlSystem::range_category (const Glib::ustring& name_category)
  throw ()
{
  return range_categories_[name_category];
}

inline const std::string&
ControlSystem::path (void) throw ()
{
  return path_;
}
#endif //CONTROL_SYSTEM_H_
