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
#include<sstream>
#include<map>
#include<string>
#include<libxml++/libxml++.h>
#include"package.h"
#include"card.h"

Package::Package (const std::string& pathname, bool isXml)
  throw (NotFoundPackageException, BadPackageFileException)
{
  unsigned int n_cards = 0;
  xmlpp::DomParser parser;
  try
    {
      parser.parse_file (pathname);
    }
  catch (xmlpp::internal_error e)
    {
      throw NotFoundPackageException ();
    }
  if (parser)
    {
      const xmlpp::Element* root = 
	parser.get_document ()->get_root_node ();
      name_ = root->get_attribute_value ("name");
      std::string num_cards = 
	root->get_attribute_value ("num_cards");
      std::istringstream iss_num_cards(num_cards);
      iss_num_cards >> num_cards_;
      std::string index_cards = 
	root->get_attribute_value ("index_cards");
      std::istringstream iss_index_cards(index_cards);
      iss_index_cards >> index_cards_;
      xmlpp::Node::NodeList nodelist = root->get_children (); 
      xmlpp::Node::NodeList::const_iterator i;
      for(i = nodelist.begin (); i != nodelist.end (); ++i)
	{
	  xmlpp::Element *node = dynamic_cast<xmlpp::Element*>(*i);
	  if(node)
	    {
	      std::string f(node->get_attribute_value ("front"));
	      std::string b(node->get_attribute_value ("back"));
	      cards.insert(std::make_pair(++n_cards, Card(f, b)));
	    }
	}
      if(n_cards != num_cards_ || 
	 (index_cards_ > num_cards_ || index_cards_ < 1))
	throw BadPackageFileException ();
    }
}

void 
Package::addCard() 
  throw ()
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

void 
Package::showInitCard()
  throw(BadIndexCardsException)
{
  if (index_cards_){
    Cards::iterator pos = cards.find(index_cards_);
    if (pos != cards.end())
      pos->second.show();
    else
      throw BadIndexCardsException();
  }//else
  //addCard();
}

void 
Package::showNextCard()
  throw(EndPackageException)
{
  Cards::iterator pos = cards.find(index_cards_ + 1);
  if (pos != cards.end()){
    index_cards_++;
    pos->second.show();
  }else
    throw EndPackageException();
}


void 
Package::showPrevCard() 
  throw(BeginPackageException)
{
  if(index_cards_ > 1){
    index_cards_--;
    Cards::const_iterator pos = cards.find(index_cards_);
    pos->second.show();
  }else
    throw BeginPackageException();
}

void 
Package::serialization (const std::string& pathname) 
  throw ()
{
  xmlpp::Document document;
  std::ostringstream o1, o2;
  o1 << num_cards_;
  o2 << index_cards_;
  xmlpp::Element* nodeRoot = document.create_root_node ("Package");
  nodeRoot->set_attribute ("name", name_);
  nodeRoot->set_attribute ("num_cards", o1.str ());
  nodeRoot->set_attribute ("index_cards", o2.str ());
  Cards::const_iterator i;
  for (i = cards.begin (); i != cards.end (); ++i)
    {
      xmlpp::Element* nodeChild = nodeRoot->add_child ("Card");
      nodeChild->set_attribute ("front", i->second.front ());
      nodeChild->set_attribute ("back", i->second.back ());
    }
  std::ostringstream o3;
  o3 << pathname << "/" <<name_ << ".xml";

  document.write_to_file_formatted (o3.str ());
}
