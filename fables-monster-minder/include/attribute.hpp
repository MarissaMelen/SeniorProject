#pragma once
#include <string>
enum attribute{
  dire,
  were,
  flying,
  swamp,
  rabid,
  undead,
  sand,
  tundra,
  mountain,
  aquatic,
  voidal,
  noattribute,
  specialattribute
};

enum attribute read_attribute(std::string input);
std::string write_attribute(enum attribute e);
