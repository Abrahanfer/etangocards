/* quiz.cpp
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
#include<glibmm/ustring.h>
#include<map>
#include<set>
#include<cstdlib>
#include<ctime>
#include"quiz.h"
#include"package.h"
#include"card.h"
#include"dialog-quiz-front.h"
#include"control-system.h"

Quiz::Quiz (const Glib::ustring& filename) throw ()
{
  unsigned int i, rand_num;
  pkg_ = new Package (filename, 1, true);

  std::map<unsigned int, bool> map_bool;

  for (i = 1;i < pkg_->num_cards () + 1; ++i)
    map_bool[i] = false;

  total_ = pkg_->num_cards () * 0.8;

  srand (time (0));
  i = 0;
  while (i < total_)
    {
      rand_num = (rand () % pkg_->num_cards ()) + 1;
      if (!map_bool[rand_num])
	{
	  quiz_cards.insert (std::make_pair
			     (i, pkg_->operator[](rand_num)));
	  ++i;
	  map_bool[rand_num] = true;
	}
    }
  old_score_ = ControlSystem::categories.find (pkg_->category ())->second;
  index = quiz_cards.begin ();
  end = quiz_cards.end ();
  index_row_number_ = 1;
  next_card ();
}

void
Quiz::next_card (void) const throw ()
{
  new DialogQuizFront (this);
}

void

Quiz::update_result (void) const throw ()
{
  ControlSystem::categories[pkg_->category ()]
    = old_score () + quiz_score (); 

  Package::Ranges ranges_ = Package::ranges ();

  if (ranges_[ControlSystem::range_categories_[pkg_->category ()]] < 
      ControlSystem::categories[pkg_->category ()])
    {
      unsigned int score = ControlSystem::categories[pkg_->category ()];
      bool stop = false;
      Package::Ranges::const_iterator i = ranges_.find 
	(ControlSystem::range_categories_[pkg_->category ()]);
      while (!stop && i != ranges_.end ())
	{
	  if (i->second < score)
	    i++;
	  else
	    {
	      ControlSystem::range_categories_[pkg_->category ()] = 
		i->first;
	      stop = true;
	    }
	    
	}
    }
}
