/* card.cpp
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
#include"card.h"

void 
Card::show (void) const
{
  char intro;
  std::cout << "front:\n\t" << front_ << std::endl;
  std::cout << "Press return..." << std::endl;
  do{
    std::cin.get (intro);
  }while (intro != '\n');
  std::cout << "back:\n\t" << back_ << std::endl;
}
