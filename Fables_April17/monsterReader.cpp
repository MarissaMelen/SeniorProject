#include <fstream>
#include <string>
#include "monsterstate.hpp"
#include "element.hpp"
#include "attribute.hpp"
#include "monster.hpp"
using namespace std;

istream & operator >> (istream &i, element &e)
{
  //Read in element from file
  string input;
  i >> input;

  //Make input lowercase
  for (int i=0; i<input.size(); ++i)
    {
      input[i] = tolower(input[i]);
    }

  if (input == "fire")
    e = fire;
  else if (input == "ice")
    e = ice;
  else if (input == "nature")
    e = nature;
  else if (input == "earth")
    e = earth;
  else if (input == "wind")
    e = wind;
  else if (input == "spark")
    e = spark;
  else if (input == "water")
    e = water;
  else if (input == "light")
    e = light;
  else if (input == "dark")
    e = dark;
  else if (input == "null")
    e = null;
  else if (input == "none") 
    e = noelement;
  else
    e = specialelement;
  return i;
}

istream & operator >> (istream &i, attribute &a)
{
  string input;
  i >> input;
  return i;
}

bool monsterReader(string filename, vector<monster> &monsterbiome)
{
  ifstream infile;
  infile.open(filename);
  //check to see if file is open
  if(!infile.is_open())
    {
      //if file is not open, return false and send error message
      return false;
    }
  while(!infile.eof())
    {
      //"v_name" is the monster name
      string v_name;
      element v_elem1, v_elem2;
      attribute v_attr;
      int v_move;
      //I called the inputs "v_NAME" as a shortened form of "Value_NAME"
      float v_hp, v_mp, v_str, v_def, v_arm, v_dex, v_ref, v_int, v_res;
      //ignore any lines starting with #
      infile >> v_name;
      while(v_name[0] == '#')
	{
	  getline(infile, v_name);
	  infile >> v_name;
	}
      //read in the values
      infile >> v_move >> v_hp >> v_mp >> v_str >> v_def >> v_arm >> v_int >> v_res;
      infile >> v_elem1 >> v_elem2 >> v_attr;
      
      //make a temporary monster
      monster temp;
      temp.name = v_name;
      temp.movement = v_move;
      temp.maxhp = v_hp;
      temp.maxmp = v_mp;
      temp.strength = v_str;
      temp.defense = v_def;
      temp.armor = v_arm;
      temp.intelligence = v_int;
      temp.resistance = v_res;
      temp.elem.first = v_elem1;
      temp.elem.second = v_elem2;
      temp.attr = v_attr;
      //add temp to the vector
      monsterbiome.push_back(temp);
    }

  infile.close();
  return true;
}
