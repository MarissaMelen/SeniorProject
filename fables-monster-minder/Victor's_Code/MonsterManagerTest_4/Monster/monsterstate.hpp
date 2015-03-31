#pragma once
#include <vector>
#include "monster.hpp"
#include "status.hpp"
#include <string>

//creatures are monsters with some extra battle data
typedef struct{
  monster basetype;
  std::string name = nullptr;
  std::vector<status> effects;
  //while redundant from the monster, these will let the GM replace monsters more easily
  int curhp;
  int curmp;
} monsterstate;
