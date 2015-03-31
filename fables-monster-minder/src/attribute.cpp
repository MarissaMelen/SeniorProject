#include "attribute.hpp"
#include <string>

enum attribute read_attribute(std::string input){
  //Make input lowercase
  for (unsigned int i=0; i<input.size(); ++i)
    {
      input[i] = tolower(input[i]);
    }

  if (input == "dire")
    return dire;
  else if (input == "were")
    return were;
  else if (input == "flying")
    return flying;
  else if (input == "swamp")
    return swamp;
  else if (input == "rabid")
    return rabid;
  else if (input == "undead")
    return undead;
  else if (input == "sand")
    return sand;
  else if (input == "tundra")
    return tundra;
  else if (input == "mountain")
    return mountain;
  else if (input == "aquatic")
    return aquatic;
  else if (input == "void" || input == "voidal")
    return voidal;
  else if (input == "none") 
    return noattribute;
  return specialattribute;
}

std::string write_attribute(enum attribute e){
  if (e == dire){
    return "dire";
  }else if (e == were){
    return "were";
  }else if (e == flying){
    return "flying";
  }else if (e == swamp){
    return "swamp";
  }else if (e == rabid){
    return "rabid";
  }else if (e == undead){
    return "undead";
  }else if (e == sand){
    return "sand";
  }else if (e == tundra){
    return "tundra";
  }else if (e == mountain){
    return "mountain";
  }else if (e == aquatic){
    return "aquatic";
  }else if (e == voidal){
    return "void";
  }else if (e == noattribute){ 
    return "none";
  }
  return "special";

}
