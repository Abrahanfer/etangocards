/* main.cpp
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
#include<cstdlib>
#include<gtkmm/main.h>
#include<pthread.h>
#include<libpanelappletmm.h>
#include<libbonobo.h>
#include"control-system.h"
#include"package.h"
#include"dialog-package.h"
#include"dialog-new.h"
#include"etangocards-applet.h"

using namespace std;

/*void*
execute_in_background (void* p_null)
{
  Gtk::Main::run ();

  return 0;
}*/

int
main (int argc, char* argv[]) 
{
  /*Package* pkg_test2;
  ControlSystem cs;
  bool go = true;
  char option;

  char* name = new char(100);
  if(!name){
    cerr << "ERROR: No memory." << endl;
    exit(1); 
  }

  Gtk::Main kit (argc, argv);

   -------------------------------------------
     Test case 1 & 2
     -------------------------------------------
     ***
     Funcionality 1: Load of packages in .xml.
     Description 1: Load 3 packages, test1, test2, and test3.
     ***
     Funcionality 2: Show packages in windows.
     Description 2: Show 3 packages in their respest windows.
  */
  /* try
    {
      
      cs.LoadPackage ("test1");
      
    }
  catch (Package::NotFoundPackageException nfpe)
    {
      cerr << "Some packages do not exist."
	   << endl;
    }
  catch (Package::BadPackageFileException bpfe)
    {
      cerr << "Some file are corrupted."
	   << endl;
    }
  try
    {
      pkg_test2 = cs.LoadPackage ("test2");
      
    }
  catch (Package::NotFoundPackageException nfpe)
    {
      cerr << "Some packages do not exist."
	   << endl;
    }
  catch (Package::BadPackageFileException bpfe)
    {
      cerr << "Some file are corrupted."
	   << endl;
    }
  try 
    {
      cs.LoadPackage ("test3");
    }
  catch (Package::NotFoundPackageException nfpe)
    {
      cerr << "Some packages do not exist."
	   << endl;
    }
  catch (Package::BadPackageFileException bpfe)
    {
      cerr << "Some file are corrupted."
	   << endl;
    }
 
  //Gtk::Main::run ();
  //---------------------------------------------
  ---------------------------------------------
    Test case 3
    ---------------------------------------------
    ***
    Funcionality 3: Create new cards in a window.
    Description 3: Add 2 cards to package "test2".
    ***
    */
  //DialogNew dn1 (pkg_test2); 
  //DialogNew dn2 (pkg_test2);
  //---------------------------------------------

  /*while(go){
    cout << "Choose an option:\n"
	 << "1. New  package.\n"
	 << "2. Show package.\n"
	 << "3. Load package.\n"
	 << "4. List packages.\n"
	 << "5. Exit.\n"
	 << "$ ";

    cin.get(option);
    cin.getline(name,100);
    try{
      switch(option){
      case '1':
	cout << "Entry new packages's name:\n$ ";
	cin.getline(name,100);
	cs.NewPackage(name);
	break;
      case '2':
	cout << "Entry packages's name to show:\n$ ";
	cin.getline(name,100);
	cs.showPackage(name);
	break;
      case '3':
	cout << "Entry packages's name to load:\n$ ";
	cin.getline(name,100);
	cs.LoadPackage(name);
      case '4':
	cs.listPackages();
	break;
      case '5':
	go = false;
	//cout << "Introduce the path of packages will be saved:\n$ ";
	//cin.getline (name, 100);
	cs.serializeSystem (ControlSystem::path);
	cout << "System serialiced.\n"
	     << "See you the next time...;-)" << endl;
	break;
      default:
	cout << "Option incorrect" << endl;
      }
    }catch(ControlSystem::RepeatPackageException e){
      cout << "ERROR: The package " << e.packageName() 
	   << " already exist." << endl;
    }catch(ControlSystem::NoPackagesException e){
      cout << "ERROR: No packages in the system." << endl;
    }catch(ControlSystem::NoPackageFoundException e){
      cout << "ERROR: The package " << e.packageName()
	   << " not exist." << endl;
    }
  }
  //delete name;
  */
  Gnome::Panel::init("EtangoCards", "0.0.1", argc, argv);
  
  try
    {
      int returncode = Gnome::Panel::factory_main<ETangoCardsApplet>("OAFIID:ETangoCardsApplet_Factory");
      return returncode;
    }
  catch(const Glib::Error& ex)
    {
      std::cout << ex.what() << std::endl;
      return 0;
    }

}
