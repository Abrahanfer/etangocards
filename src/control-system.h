//-*-c++-*-
/* control-system.h
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
#ifndef CONTROL_SYSTEM_H_
#define CONTROL_SYSTEM_H_

#include<glibmm.h>
#include<map>
#include<set>

class Package;

class ControlSystem {
public:
  typedef std::map<Glib::ustring, Glib::ustring> RangeCategories;
  typedef std::map<Glib::ustring, unsigned int> Categories;
  typedef std::set<Package *> Packages;
  class RepeatPackageException {
  public:
    explicit RepeatPackageException (const std::string&);
    const std::string& packageName (void) const;
  private:
    std::string packageName_;
  };
  class NoPackagesException {};
  class NoPackageFoundException {
  public:
    explicit NoPackageFoundException (const std::string&);
    const std::string& packageName (void) const;
  private:
    std::string packageName_;
  };
  static void associate (Package*) 
    throw ();
  //static const Packages& associate (void) const;
  //const Package& LoadPackage (const std::string&) const
  //throw (NoPackagesException, NoPackageFoundException);
  static Package* LoadPackage (const std::string&, unsigned int);
  /*    throw (Package::NotFoundPackageException, 
	   Package::BadPackageFileException,
	   RepeatPackageException);*/
  void showPackage (const std::string&);
  void NewPackage (const std::string&);
  static void serializeSystem ();
  static void eliminatePackage (Package*) throw ();
  static void serializeConfigurationFile (void) throw ();
  static const Glib::ustring& range_category (const Glib::ustring&)
    throw ();
  ~ControlSystem (void);
  static std::string path_;
  static RangeCategories range_categories_;
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
#endif
