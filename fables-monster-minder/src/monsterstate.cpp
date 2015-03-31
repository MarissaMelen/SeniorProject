#include "monsterstate.hpp"
#include <list>
#include <string.h>

monsterstate::monsterstate(){
  name = "NXMONSTER";
  effects = {};
  curhp = -1;
  curmp = -1;
}

monsterstate readyMonster(monster m){
  std::list<status> empty;
  monsterstate result;
  result.basetype = m;
  result.name = m.default_name;
  result.effects = {};
  result.curhp = m.maxhp;
  result.curmp = m.maxmp;
  return result;
}
