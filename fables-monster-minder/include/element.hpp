#pragma once
#include <string>
typedef enum{
  fire,
  ice,
  nature,
  earth,
  wind,
  spark,
  water,
  light,
  dark,
  null,
  noelement,
} element;

element read_element(std::string input);
std::string write_element(element e);
