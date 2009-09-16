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
  /* double old_score = 
    ControlSystem::categories.find (pkg_->category ())->second;
  ControlSystem::categories[pkg_->category ()] 
  = old_score + right_ * (pkg_->score () / pkg_->num_cards ()); */

  ControlSystem::categories["Geography"] = 50;
}
