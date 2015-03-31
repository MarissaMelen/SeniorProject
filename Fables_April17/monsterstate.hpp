#pragma once
#include <vector>
#include "monster.hpp"
#include "status.hpp"

//creatures are monsters with some extra battle data
typedef struct{
  monster basetype;
  char* name = nullptr;
  std::vector<status> effects;
  //while redundant from the monster, these will let the GM replace monsters more easily
  int curhp;
  int curmp;
} monsterstate;
