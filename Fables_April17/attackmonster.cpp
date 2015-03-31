//this is where the monster will be targeted
//select a weapon and the switch will pick the correct function to use
//most of these functions will be located in the damagemonster.cpp
#include "weapon.hpp"
#include "damagemonster.hpp"
#include <iostream>
using namespace std;


double damage(weapon weapontype, int roll, int baseDMG, int monsterARM, int monsterDEF, int monsterRES, double elementMOD, int cunningBNS)
{
    double DMGdealt = 0;
    int monsterPWR = monsterDEF + monsterARM;
    
    //this is for the custom damage function

    switch (weapontype) {
            //each of these will lead to a different weapon attack type
//sword
        case sword:
            DMGdealt = swordDMG(baseDMG, roll, monsterPWR, elementMOD);
            break;
//spear
        case spear:
            DMGdealt = spearDMG(baseDMG, roll, monsterDEF, monsterPWR, elementMOD);
            break;
//axe
        case axe:
            DMGdealt = axeDMG(baseDMG, roll, monsterPWR, elementMOD);
            break;
//fist
        case fist:
            DMGdealt = fistDMG(baseDMG, roll, monsterPWR, elementMOD);
            break;
//bow
        case bow:
            DMGdealt = bowDMG(baseDMG, roll, monsterPWR, elementMOD);
            break;
//crossbow
        case crossbow:
            DMGdealt = crossbowDMG(baseDMG, roll, monsterDEF, monsterPWR, elementMOD);
            break;
//firearm
        case firearm:
            DMGdealt = firearmDMG(baseDMG, roll, monsterDEF, elementMOD);
            break;
//nonmage
        case nonmage:
            DMGdealt = nonmageDMG(baseDMG, roll, monsterPWR);
            break;
//knife
        case knife:
   //here we need to ask for their cunning bonus, this we will modify inside the function, don't worry
            DMGdealt = knifeDMG(baseDMG, roll, monsterPWR, elementMOD, cunningBNS);
            break;
//quickcast magic, this could also work for normal mage spells, 
//just keep track of turns yourself
        case quickcast:
            DMGdealt = quickcastDMG(baseDMG, roll, monsterRES, elementMOD);
            break;
        default:
            return 0;
    }
    return DMGdealt;
}
