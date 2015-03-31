#include "element.hpp"
#include <string>

element read_element(std::string input){
  //Make input lowercase
  for (unsigned int i=0; i<input.size(); ++i)
    {
      input[i] = tolower(input[i]);
    }

  if (input == "fire")
    return fire;
  else if (input == "ice")
    return ice;
  else if (input == "nature")
    return nature;
  else if (input == "earth")
    return earth;
  else if (input == "wind")
    return wind;
  else if (input == "spark")
    return spark;
  else if (input == "water")
    return water;
  else if (input == "light")
    return light;
  else if (input == "dark")
    return dark;
  else if (input == "null")
    return null;
  else
    return noelement;
}

std::string write_element(element e){
  if (e == fire){
    return "fire";
  }else if (e == ice){
    return "ice";
  }else if (e == nature){
    return "nature";
  }else if (e == earth){
    return "earth";
  }else if (e == wind){
    return "wind";
  }else if (e == spark){
    return "spark";
  }else if (e == water){
    return "water";
  }else if (e == light){
    return "light";
  }else if (e == dark){
    return "dark";
  }else if (e == null){
    return "null";
  }else{ 
    return "none";
  }
}
