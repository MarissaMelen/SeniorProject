#pragma once
#include "element.hpp"
#include "attribute.hpp"
#include <string>

class monster{
public:
  std::string default_name;
  double maxhp;
  double maxmp;
  double strength;
  double defense;
  double armor;
  double intelligence;
  double resistance;
  double movement;
  attribute attr;
  std::pair<element,element> elem;
  //needed to prevent a mysterious crash when copying
  monster();
};
  

