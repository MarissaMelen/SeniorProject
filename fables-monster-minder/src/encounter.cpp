#include "encounter.hpp"
#include <random>
#include "monsterstate.hpp"

#define STATS_PER_LEVEL 10
#define STATS_PER_PLAYER 5

difficulty str_to_diff(char str) {
	if (str == 'E') {
		return easy;
	}
	else if (str == 'M') {
		//Medium felt like a better GUI choice than Normal
		return normal;
	}
	else {
		return hard;
	}
}

//quick helper function to get a monsters stat total
float totalstats(monster m){
  return m.maxhp/5+m.maxmp/5+m.strength+m.defense+m.armor+m.intelligence+m.resistance;
}

monster levelMonster(monster m,int level){
  monster newmon = m;
  newmon.maxhp *= level;
  newmon.maxmp *= level;
  newmon.strength *= level;
  newmon.defense *= level;
  newmon.armor *= level;
  newmon.intelligence *= level;
  newmon.resistance *= level;
  return newmon;
}

std::vector<monsterstate> makeEncounter(std::vector<monster> candidates, short total_level, char party_size, difficulty d){
  //for now, let's scale difficulty off the monster's stat total 
  //count hp as 1/5 of an ordinary stat point
  //these numbers will need to adjusted to balance things
  if(party_size < 1){
    return {};
  }
  if(total_level < party_size){
    return {};
  }
  float target_stats = STATS_PER_LEVEL*total_level+STATS_PER_PLAYER*party_size;
  //current stat total
  double current_total = 0;
  double average_level = total_level/party_size;
  //randomness, used to generate random encounters
  std::random_device seed;
  std::mt19937 rng(seed());
  std::uniform_int_distribution<> selection(0,candidates.size()-1);
  std::vector<monsterstate> encounter;
  if(d == easy){
    target_stats *= 0.75;
  }else if(d == hard){
    target_stats *= 1.25;
  }
  while(current_total < target_stats*0.95){
    int choice = selection(rng);
    monster selected = levelMonster(candidates[choice],std::round(average_level));
    if(current_total + totalstats(selected) < target_stats*1.05){
      current_total += totalstats(selected);
      encounter.push_back(readyMonster(selected));
    }else{
      //the randomly chosen monster would overscale the encounter, try another
      int next_attempt = choice;
      while(next_attempt != choice){
	next_attempt--;
	if(next_attempt < 0){
	  next_attempt += candidates.size();
	}
	monster selected = levelMonster(candidates[next_attempt],std::round(average_level));
	if(current_total + totalstats(selected) < target_stats*1.05){
	  current_total += totalstats(selected);
	  encounter.push_back(readyMonster(selected));
	  //just assume we have enough monsters at this point
	  break;
	}
      }
      current_total *= average_level;
      //we either have enough or can't scale properly, just return what we have
      return encounter;
    }
  }
  return encounter;
}
	
