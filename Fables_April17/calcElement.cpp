//Calaculating damage modulators for elements
//Listed elements are as follows:
//Terrestrial: Fire, Ice, Nature, Earth, Wind, Spark, Water
//Dual: Light, Dark
//Pure: Null
//Other: None

//Notes on element weakness/resistance
//For terrestrial, they will do double damage to one on right (fire x2 to ice) (water loops to front)
// takes 1/2 damage from one on right (ice x0.5 to fire), again fire loops back to water
// takes 1/4 damage from self (fire x0.25 to fire)
//deals/takes x1 to dual, deals/takes  x1.25 to pure

//For dual elements: Each deal x2 damage to the other, takes x0.25 from self
// deals/takes x1 from terrestrial, deals/takes x1.25 from pure

//For pure element: Takes/deals x2 damage to self, takes/deals x1.25 to all others

//None is always a x1 modifier as it is a placeholder
#include "element.hpp"
#include <iostream>
#include "attribute.hpp"
using namespace std;


double elemMod(element elemATK, attribute attr)
{
  double elementMOD = 1;
  if (elemATK != none)
    {
      elementMOD = 2;
    }
  return elementMOD;
}


double elemMod(element elemATK, element elemDEF)
{
  double elementMOD = 1;

  //if the attacking is none, mod is 1
  if(elemATK == none)
    {
      elementMOD = 1;
    }
  //if the elements are the same, the modifier should be x0.25
  //unless null, which I will check for
  else if(elemATK == elemDEF)
    {
      //if ATK is null (DEF will be null too), MOD is 2
      if(elemATK == null)
	{
	  elementMOD = 2;
	}
      //if they are not null, then it is 0.25
      else
	{
	  elementMOD = 0.25;
	}
    }
  //normal null interaction
  else if((elemATK == null) && ((elemDEF != null)&&(elemDEF != none)))
    {
      elementMOD = 1.25;
    }
  //dual elements, strong and weak are the same
  else if( ((elemATK == light)&&(elemDEF == dark)) || ((elemATK == dark)&&(elemDEF == light)) )
    {
      elementMOD = 2;
    }
  //terrestrial elements and what they are strong against (x2)
  else if( ((elemATK == fire)&&(elemDEF == ice)) || ((elemATK == ice)&&(elemDEF == nature)) || ((elemATK == nature)&&(elemDEF == earth)) || ((elemATK == earth)&&(elemDEF == wind)) || ((elemATK == wind)&&(elemDEF == spark)) || ((elemATK == spark)&&(elemDEF == water)) || ((elemATK == water)&&(elemDEF == fire)) )
    {
      elementMOD = 2;
    }
  //terrestrial elements and what they are weak against (x0.5)
  else if( ((elemATK == ice)&&(elemDEF == fire)) || ((elemATK == nature)&&(elemDEF == ice)) || ((elemATK == earth)&&(elemDEF == nature)) || ((elemATK == wind)&&(elemDEF == earth)) || ((elemATK == spark)&&(elemDEF == wind)) || ((elemATK == water)&&(elemDEF == spark)) || ((elemATK == fire)&&(elemDEF == water)) )
    {
      elementMOD = 0.5;
    }
    
  return elementMOD;
}
