//this is where the monster will be targeted
//select a weapon and the switch will pick the correct function to use
//most of these functions will be located in the damagemonster.cpp
#include "attackmonster.hpp"
#include "damagemonster.hpp"

double damage_target(weapon weapontype, int roll, int baseDMG, int monsterARM, int monsterDEF, int monsterRES, double elementMOD, int cunningBNS)
{
	double DMGdealt = 0;
	int monsterPWR = monsterDEF + monsterARM;

	//this is for the custom damage function

	switch (weapontype) {
		//each of these will lead to a different weapon attack type
		case sword:
			DMGdealt = swordDMG(baseDMG, roll, monsterPWR, elementMOD);
			break;
		case spear:
			DMGdealt = spearDMG(baseDMG, roll, monsterDEF, monsterPWR, elementMOD);
			break;
		case axe:
			DMGdealt = axeDMG(baseDMG, roll, monsterPWR, elementMOD);
			break;
		case fist:
			DMGdealt = fistDMG(baseDMG, roll, monsterPWR, elementMOD);
			break;
		case bow:
			DMGdealt = bowDMG(baseDMG, roll, monsterPWR, elementMOD);
			break;
		case crossbow:
			DMGdealt = crossbowDMG(baseDMG, roll, monsterDEF, monsterPWR, elementMOD);
			break;
		case firearm:
			DMGdealt = firearmDMG(baseDMG, roll, monsterDEF, elementMOD);
			break;
		case nonmage:
			DMGdealt = nonmageDMG(baseDMG, roll, monsterPWR);
			break;
		case knife:
			//here we need to ask for their cunning bonus, this we will modify inside the function, don't worry
			DMGdealt = knifeDMG(baseDMG, roll, monsterPWR, elementMOD, cunningBNS);
			break;
		case quickcast:
			//quickcast magic, this could also work for normal mage spells, 
			//just keep track of turns yourself
			DMGdealt = quickcastDMG(baseDMG, roll, monsterRES, elementMOD);
			break;
		default:
			return 0;
	}

	if (DMGdealt <= 0) {
		DMGdealt = 0;
	}
	else if (DMGdealt > 0 && DMGdealt < 1) {
		DMGdealt = 1;
	}

	return DMGdealt;
}
