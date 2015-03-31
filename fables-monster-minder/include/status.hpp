#pragma once
#include <math.h>
#include <string>
#include "monster.hpp"

typedef enum{
  damage,
  healing,
  manadrain,
  manaregen,
  burn,
  freeze,
  poison,
  petrify,
  headwind,
  paralyze,
  silence,
  blind,
  confuse,
  infatuate,
  bind,
  bleed,
  blight,
  asleep,
  taunt,
  curse,
  statdown,
  statup,
  specialstatus
} statustype;

typedef struct{
  statustype type = specialstatus;
  //8 bit integer
  char level = 0;
  char duration = -1;
  std::string name;
  bool fresh = true;
  int orig_max_hp = 0;
  int orig_max_mp = 0;
  int operator ()(monster& m){
	//initial application
	if(fresh){
	  if(type == burn || type == curse){
	    orig_max_hp = m.maxhp;
	    m.maxhp -= m.maxhp*fmin(0.25,(0.05+0.05*level));
		m.strength -= floor(1.2*level);
		m.defense -= floor(1.2*level);
	  }if(type == blight || type == curse){
	    orig_max_mp = m.maxmp;
	    m.maxmp -= m.maxmp*fmin(0.25,(0.05+0.05*level));
		m.intelligence -= floor(1.2*level);
		m.resistance -= floor(1.2*level);
	  }else if(type == statdown){
		m.strength -= m.strength*0.01*level;
		m.defense -= m.defense*0.01*level;
		m.intelligence -= m.intelligence*0.01*level;
		m.resistance -= m.resistance*0.01*level;
	  }else if(type == statup){
		m.strength += m.strength*0.01*level;
		m.defense += m.defense*0.01*level;
		m.intelligence += m.intelligence*0.01*level;
		m.resistance += m.resistance*0.01*level;
	  }
	  fresh = false;
	  return 0;
	}else if(duration == 0){
	  if(type == burn || type == curse){
	    m.maxhp = orig_max_hp;
		m.strength += floor(1.2*level);
		m.defense += floor(1.2*level);
	  }if(type == blight || type == curse){
	    m.maxmp = orig_max_mp;
		m.intelligence += floor(1.2*level);
		m.resistance += floor(1.2*level);
	  }else if(type == statdown){
		m.strength += m.strength*0.01*level;
		m.defense += m.defense*0.01*level;
		m.intelligence += m.intelligence*0.01*level;
		m.resistance += m.resistance*0.01*level;
	  }else if(type == statup){
		m.strength -= m.strength*0.01*level;
		m.defense -= m.defense*0.01*level;
		m.intelligence -= m.intelligence*0.01*level;
		m.resistance -= m.resistance*0.01*level;
	  }
	  duration-=1;
	  return 0;
	}else{
	  duration-=1;
	  if(type == curse || type==poison || type == blight){
		//note: damage to mp if blighted
		return m.maxhp*fmin(0.25,(0.05+0.05*level));
	  }else if(type == bleed){
		//bleed is completely discontinuous and random.
		//we will need to interface with physical dice
		//to determine what to do here.
		//
		return 0;
	  }else if(type == damage || type == manadrain){
		return level;
	  }else if(type == healing || type == manaregen){
		//to allow for simple subtraction of the output
		return -1*level;
	  }
	}
	return 0;
  }
} status;

statustype read_statustype(std::string input);
std::string write_statustype(statustype s);
