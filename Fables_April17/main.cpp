#include <iostream>
#include <string>
#include "weapon.hpp"
#include "element.hpp"
#include "damagemonster.hpp"
#include "attackmonster.hpp"
#include "calcElemDMG.hpp"
#include "calcElement.hpp"

using namespace std;


istream & operator >> (istream &i, weapon &w)
{
    //Read in weapon from command line
    string input;
    i >> input;
    
    //Make input lowercase
    for (int j=0; j<input.size(); j++)
    {
        input[j] = tolower(input[j]);
    }
    
    if (input == "sword")
        w = sword;
    else if (input == "spear")
        w = spear;
    else if (input == "axe")
        w = axe;
    else if (input == "fist")
        w = fist;
    else if (input == "knife")
        w = knife;
    else if (input == "bow")
        w = bow;
    else if (input == "crossbow")
        w = crossbow;
    else if (input == "firearm")
        w = firearm;
    else if (input == "nonmage")
        w = nonmage;
    else if (input == "quickcast")
        w = quickcast;
    else
        w = custom;
    return i;
}


int main()
{
    int roll = 0;
    int baseDMG = 0;
    int monsterARM = 0;
    int monsterDEF = 0;
    int monsterRES = 0;
    double elementMOD = 1;
    double DMGdealt = 0;
    int cunningBNS = 0;
    double defMOD = 1;
    double armMOD = 1;
    double resMOD = 1;
    double dmgMOD = 1;
    element elem1, elem2;
    weapon weapontype;
    weapontype = sword;
    elem1 = none;
    elem2 = none;

    string quit = "no";

    while (quit != "q")
      {
	
	monster mon;
	monsterARM = 10;
	monsterDEF = 15;
	monsterRES = 20;
	elementMOD = 1;
	int monsterPWR = (monsterARM + monsterDEF);
  
	cout << "armor = " << monsterARM << " \ndefense = " << monsterDEF << "\npower = " << monsterPWR << "\nresistance = " << monsterRES << endl;

	cout << "what is your roll? What is your base damage?";
	cin >> roll >> baseDMG;
    
	cout << "What weapon type? ";
	cin >> weapontype;
	cout << "What is cunning bonus? ";
	cin >> cunningBNS;
          
        cout << "what is defMOD, armMOD, resMOD and dmgMOD? ";
	cin >> defMOD >> armMOD >> resMOD >> dmgMOD;
        
	cout << "what are attacking elments? ";
	cin >> elem1 >> elem2;
	
	elementMOD = checkElem(elem1, elem2, mon);

	cout << "elementMOD = " << elementMOD << endl;
	if(elementMOD < 0)
	  {
	    elementMOD = 1;
	  }

	DMGdealt = damage(weapontype, roll, baseDMG, monsterARM, monsterDEF, monsterRES, elementMOD);
	//if the damage that the player would deal is between 0 and 1, they deal 1 damage
	//if it is a different non-integer number then we truncate it
    
	if((0 < DMGdealt)&&(DMGdealt< 1))
	  {
	    DMGdealt = 1;
	  }
	else
	  {
	    DMGdealt = (int)DMGdealt;
	  }
    
	cout << "Damage dealt = " << DMGdealt << endl;
	cout << "\n\n";
      }
    return 0;
}
