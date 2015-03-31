#pragma once
#include "element.hpp"
#include "attribute.hpp"
using namespace std;

typedef struct{
  string name;
  int maxhp;
  int maxmp;
  int strength;
  int defense;
  int armor;
  int intelligence;
  int resistance;
  int movement;
  std::pair<element,element> elem;
  attribute attr;
} monster;
  
