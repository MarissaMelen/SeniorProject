#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "monsterstate.hpp"

struct EncounterData {
	std::unordered_map<std::string, std::vector<monsterstate>> *monsters;
	std::vector<std::string> m_names;	
};

enum difficulty{
  easy,
  normal,
  hard
};

//Function to convert a char to difficulty
difficulty str_to_diff(char str); 

//functions for accessing biomes
/*
void add_biome(std::string location,std::vector<monster> contents);
void remove_biome(std::string location);
std::vector<monster> access_biome(std::string location);
void clear_biomes();
*/

//functions used for generating encounters
//EncounterData makeEncounter(std::unordered_map<std::string, std::vector<monsterstate>> *encounter, std::vector<monster> biome, short total_level, char party_size, difficulty d);
std::vector<monsterstate> makeEncounter(std::vector<monster> candidates, short total_level, char party_size, difficulty d);

