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
#include"control-system.h"
#include"package.h"

using namespace std;

int main() {
  ControlSystem cs;
  bool go = true;
  char option;

  char* name = new char(100);
  if(!name){
    cerr << "ERROR: No memory." << endl;
    exit(1); 
  }
  /* -------------------------------------------
     Test case.
     -------------------------------------------
     ***
     Funcionality: Load of packages in .xml
     Description: Load 3 packages, test1, test2, and test3, 
     with 0, 1, and 3 cards.
     ***
   */
  cs.LoadPackage ("test1");
  cs.LoadPackage ("test2");
  cs.LoadPackage ("test3");
  //---------------------------------------------
  while(go){
    cout << "Choose an option:\n"
	 << "1. New  package.\n"
	 << "2. Load package.\n"
	 << "3. List packages.\n"
	 << "4. Exit.\n"
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
	cout << "Entry packages's name to load:\n$ ";
	cin.getline(name,100);
	cs.showPackage(cs.LoadPackage(name));
	break;
      case '3':
	cs.listPackages();
	break;
      case '4':
	go = false;
	//cout << "Introduce the path of packages be saved:\n$ ";
	//cin.getline (name, 100);
	cs.serializeSystem ("/home/abrahan/.etangocards");
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

}
