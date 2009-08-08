/* control-system.cpp
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
#include<iostream>
#include<string>
#include<map>
#include<set>
#include"dialog-package.h"
#include"control-system.h"
#include"package.h"

std::string ControlSystem::path("/home/abrahan/.etangocards/");

void
ControlSystem::associate (const std::string& str, Package* pkg)
  throw (RepeatPackageException)
{
  if (packages.find (str) == packages.end ())
    packages.insert (std::make_pair (str, pkg));
  else
    throw RepeatPackageException (str);
}

/*const Package& 
ControlSystem::LoadPackage (const std::string& str) const
  throw (NoPackagesException, NoPackageFoundException)
{
  if (packages.empty ())
    throw NoPackagesException ();
  else{
    Packages::const_iterator pos;
    if ((pos = packages.find (str)) 
	== packages.end ())
      throw NoPackageFoundException (str);
    else
      return *(pos->second);
  }
  }*/

Package*
ControlSystem::LoadPackage (const std::string& str)
/*throw (Package::NotFoundPackageException, Package::BadPackageFileException,
  RepeatPackageException)*/
{
  Package *pkg = new Package(path + str + ".xml", true);
  associate (str, pkg);
  new DialogPackage (pkg);

  return pkg;
}

void
ControlSystem::showPackage (const std::string& str)
{
  Package *pkg;

  if (packages.empty ())
    throw NoPackagesException ();
  else{
    Packages::iterator pos;
    if ((pos = packages.find (str)) 
	== packages.end ())
      throw NoPackageFoundException (str);
    else
      pkg = pos->second;
  }
  bool go = true;
  char *option = new char (100);
  try{
    pkg->showInitCard ();
    while (go){
      std::cout << "Choose an option:\n" 
		<< "(a)add card, (n)next card, (p)previous card, "
		<< "(e)exit" << std::endl
		<< "$ ";
      std::cin.getline (option, 100);
      try{
	switch (option[0]){
	case 'a':
	  pkg->addCard ("", "");
	  break;
	case 'n':
	  pkg->showNextCard ();
	  break;
	case 'p':
	  pkg->showPrevCard ();
	  break;
	case 'e':
	  std::cout << "Exiting..." << std::endl;
	  go = false;
	  break;
	default:
	  std::cout << "Bad option." << std::endl;
	}
      }catch (Package::EndPackageException e){
	std::cout << "In the finish of package." << std::endl; 
      }catch (Package::BeginPackageException e){
	std::cout << "In the begin of package." << std::endl;
      }
    }
  }catch (Package::BadIndexCardsException e){
    std::cout << "This package is corrupted, "
	      << "please load other package." << std::endl;
  }
}

void
ControlSystem::listPackages () const
{
  Packages::const_iterator i;
  for (i = packages.begin (); i != packages.end (); ++i)
    std::cout << i->first  << std::endl;
}

void
ControlSystem::NewPackage (const std::string& str)
{
  Package *pkg = new Package (str);

  associate (str,pkg);
}

void
ControlSystem::serializeSystem (const std::string& pathname)
{
  Packages::const_iterator i;

  for (i = packages.begin (); i != packages.end (); ++i)
    {
      i->second->serialization (pathname);
    }
}

ControlSystem::~ControlSystem ()
{
  Packages::iterator pos;

  for (pos = packages.begin (); pos != packages.end (); ++pos)
    delete pos->second;
}
