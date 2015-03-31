#pragma once
#include <list>
#include "monster.hpp"
#include "status.hpp"
#include <string>

//a monster and corresponding battle data
class monsterstate{
public:
  monster basetype;
  std::string name;
  std::list<status> effects;
  int curhp;
  int curmp;
  //used for creating a monsterstate WITHOUT am monster. Use readyMonster() for most cases.
  monsterstate();
};

//initialize a monsterstate from a monster
monsterstate readyMonster(monster m);



