#include <iostream>
#include "calcElemDMG.hpp"
#include "element.hpp"
#include "calcElement.hpp"
#include "attribute.hpp"
using namespace std;

double checkElem(element atkElem1, element atkElem2, monster &mon)
{
  double totalElemMOD = 1;
  double mod1, mod2;
  mod1 = mod2 = 1;
  element defElem1, defElem2;
  attribute attr;
  defElem1 = mon.elem.first;
  defElem2 = mon.elem.second;
  attr = mon.attr;
  //if the 1st def element is noelement, but the 2nd is not, swap them
  if(defElem1 == noelement && defElem2 != noelement)
    {
      defElem1 = defElem2;
      defElem2 = noelement;
    }

  //if the 1st atk element is noelement, but the 2nd is not, swap them
  if(atkElem1 == noelement && atkElem2 != noelement)
    {
      atkElem1 = atkElem2;
      atkElem2 = noelement;
    }

  //check for void type monsters
  if(attr == voidal)
    {
      elemMod(atkElem1, attr);
    }

  //if the atkElem1 and defElem1 are both "noelement" that means there are no elements involved, return 1
  if(atkElem1 == noelement && defElem1 == noelement)
    {
      totalElemMOD = 1;
    }

  //if atkElem2 and defElem2 are both "noelement", that means that there is nothing in the first slot
  //there is only 1 to 1 elements, calc with 1 to 1
  else if(atkElem2 == noelement && defElem2 == noelement)
    {
      totalElemMOD = elemMod(atkElem1, defElem1);
    }

  //if there is nothing in the second defending slot, there is 2 attacking to 1 defending
  //calculate each attacking element against the defending element
  //then multiply them together for final result
  else if(defElem2 == noelement)
    {
      mod1 = elemMod(atkElem1, defElem1);
      mod2 = elemMod(atkElem2, defElem1);
      totalElemMOD = mod1*mod2;
    }

  //if there is nothing in the second attacking slot, there is 1 attacking to 2 defending
  //calculate same as with 2 attack to 1 defend, but in reverse  
  else if(atkElem2 == noelement)
    {
      mod1 = elemMod(atkElem1, defElem1);
      mod2 = elemMod(atkElem1, defElem2);
      totalElemMOD = mod1*mod2;
    }

  //this is for a two against two calculation
  //check the first attack against the first defense
  //check the second attack against the second defense
  //then multiply results together, so YES, order would matter
  //but that's the point
  else if(atkElem1 != noelement && atkElem2 != noelement && defElem1 != noelement && defElem2 != noelement)
    {
      mod1 = elemMod(atkElem1, defElem1);
      mod2 = elemMod(atkElem2, defElem2);

      totalElemMOD = mod1*mod2;
    }

  return totalElemMOD;
}
