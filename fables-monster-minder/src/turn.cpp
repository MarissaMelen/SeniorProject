#include "monsterstate.hpp"
#include <list>

void passturn(std::list<monsterstate>& enemies){
  for(auto& c:enemies){
	for(auto& eff:c.effects){
	  if(eff.type == blight || eff.type == manadrain){
		c.curmp -= eff(c.basetype);
	  }else if(eff.type == curse){
	    int damage = eff(c.basetype);
	    c.curhp -= damage;
	    c.curmp -= damage;
	  }else{
		c.curhp -= eff(c.basetype);
	  }
	}
	c.effects.remove_if([](status s){return s.duration < 0;});
  }
}
