#include "monster.hpp"

monster::monster(){
  default_name = "DUMMYMON";
  maxhp = -1;
  maxmp = -1;
  strength = -1;
  defense = -1;
  armor = -1;
  intelligence = -1;
  resistance = -1;
  movement = -1;
  attr = noattribute;
  elem = {noelement,noelement};
}

  
