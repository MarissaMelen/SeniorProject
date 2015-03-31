#pragma once
#include "element.hpp"
//#include "attribute.hpp"
#include <string>
using namespace std;

typedef struct{
	std::string name;
	int maxhp;
	int maxmp;
	int strength;
	int defense;
	int armor;
	int intelligence;
	int resistance;
	int movement;
	std::pair<element,element> elem;
//	attribute attr;
} monster;
  
