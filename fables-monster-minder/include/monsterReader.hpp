#pragma once
#include <fstream>
#include <string>
#include "monsterstate.hpp"
#include "element.hpp"
#include "attribute.hpp"
#include "monster.hpp"
#include <stdlib.h>
#include <string.h>
#include <vector>
using namespace std;

istream & operator >> (istream &i, element &e);

istream & operator >> (istream &i, attribute &a);

bool monsterReader(string filename, vector<monster> &monsterbiome);
