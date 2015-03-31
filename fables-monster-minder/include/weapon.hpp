#pragma once
#include <string>

typedef enum{
  sword,
  spear,
  axe,
  fist,
  bow,
  crossbow,
  firearm,
  nonmage,
  knife,
  quickcast,
  custom 
} weapon;

weapon str_to_weap(const std::string &weap);
