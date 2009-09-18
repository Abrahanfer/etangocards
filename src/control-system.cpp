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
#include<libxml++/libxml++.h>
#include<glibmm/main.h>
#include"dialog-package.h"
#include"control-system.h"
#include"package.h"
#include"etangocards-applet.h"

std::string ControlSystem::path_(Glib::get_home_dir () + "/.etangocards");

ControlSystem::Categories ControlSystem::categories;

ControlSystem::RangeCategories ControlSystem::range_categories_;

ControlSystem::Packages ControlSystem::packages;

void
ControlSystem::associate (Package* pkg)
  throw ()
{
    packages.insert (pkg);
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
ControlSystem::LoadPackage (const std::string& str, unsigned int index_cards)
/*throw (Package::NotFoundPackageException, Package::BadPackageFileException,
  RepeatPackageException)*/
{
  Package *pkg = new Package(str, index_cards, true);
  associate (pkg);
  DialogPackage *pdpkg = new DialogPackage (pkg);
  DialogPackage::insertDialogPackage (pdpkg);

  return pkg;
}

/*void
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
  try
    {
      pkg->showInitCard ();
      while (go)
	{
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
    }
catch (Package::BadIndexCardsException e){
  std::cout << "This package is corrupted, "
	    << "please load other package." << std::endl;
 }
 }*/

void
ControlSystem::NewPackage (const std::string& str)
{
  Package *pkg = new Package (str);

  associate (pkg);
}

void
ControlSystem::serializeSystem (void)
{
  Packages::const_iterator i;

  for (i = packages.begin (); i != packages.end (); ++i)
    {
      (*i)->serialization ();
    }

  serializeConfigurationFile ();
}

void
ControlSystem::eliminatePackage (Package* pkg) throw ()
{
  Packages::iterator pos = packages.find (pkg);
  packages.erase (pos);
}

void
ControlSystem::serializeConfigurationFile (void) throw ()
{
  xmlpp::Document configurationFile;
  std::stringstream oss;
  oss << ETangoCardsApplet::get_timeout ();

  xmlpp::Element* nodeRoot = 
    configurationFile.create_root_node ("Packages");
  nodeRoot->set_attribute ("timeout",oss.str ());
  Packages::const_iterator i;
  for (i = packages.begin (); i != packages.end (); ++i)
    {
      xmlpp::Element* nodeChild = nodeRoot->add_child ("Package");
      std::ostringstream oss;
      oss << (*i)->index_cards ();
      nodeChild->set_attribute ("index_cards", oss.str ());
      nodeChild->set_attribute ("path", (*i)->path ());
    }
  Categories::const_iterator j;
  xmlpp::Element* nodeCategories = nodeRoot->add_child ("Categories");
  for (j = categories.begin (); j != categories.end (); ++j)
    {
      xmlpp::Element* nodeCategory = nodeCategories->add_child ("Category");
      nodeCategory->set_attribute ("category", j->first);
      std::ostringstream oss;
      oss << j->second;
      nodeCategory->set_attribute ("score", oss.str ());
      nodeCategory->set_attribute ("range", ControlSystem::range_category 
				   (j->first));
    }

  configurationFile.write_to_file_formatted (path_);
}

ControlSystem::~ControlSystem (void)
{
  Packages::iterator pos;

  for (pos = packages.begin (); pos != packages.end (); 
       ++pos)
    delete *pos;
}
