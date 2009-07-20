/* package.cpp
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
#include<map>
#include<string>
#include"package.h"
#include"card.h"

void Package::AddCard()
{
  char *front, *back;
  front = new char(100);
  back = new char(100);

  std::cout << "Introduce the card's front:\n"
	    << "$ ";
  std::cin.getline(front,100);

  std::cout << "Introduce the card's back:\n"
	    << "$ ";
  std::cin.getline(back,100);
  std::string f(front), b(back);
  cards.insert(std::make_pair(++num_cards_, Card(f, b)));
  std::cout << "Showing new card:" << std::endl; 
  index_cards_ = num_cards_; 
  Cards::const_iterator pos = cards.find(num_cards_);
  if(pos != cards.end())
    (pos->second).show();
  delete front;
  delete back;
}

void Package::ShowInitCard()
  throw(BadIndexCardsException)
{
  if (index_cards_){
    Cards::iterator pos = cards.find(index_cards_);
    if (pos != cards.end())
      pos->second.show();
    else
      throw BadIndexCardsException();
  }else
    AddCard();
}

void Package::ShowNextCard()
  throw(EndPackageException)
{
  Cards::iterator pos = cards.find(index_cards_ + 1);
  if (pos != cards.end()){
    index_cards_++;
    pos->second.show();
  }else
    throw EndPackageException();
}


void Package::ShowPrevCard() 
  throw(BeginPackageException)
{
  if(index_cards_ > 0){
    index_cards_--;
    Cards::const_iterator pos = cards.find(index_cards_);
    pos->second.show();
  }else
    throw BeginPackageException();
}
