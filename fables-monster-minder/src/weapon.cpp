#include "weapon.hpp"

weapon str_to_weap(const std::string &weap) {
	if (weap == "Sword") {
		return sword;	
	}
	else if (weap == "Spear") {
		return spear;	
	}
	else if (weap == "Axe") {
		return axe;	
	}
	else if (weap == "Fist") {
		return fist;
	}
	else if (weap == "Bow") {
		return bow;	
	}
	else if (weap == "Crossbow") {
		return crossbow;
	}
	else if (weap == "Firearm") {
		return firearm;	
	}
	else if (weap == "Non-mage Tome") {
		return nonmage;
	}
	else if (weap == "Non-mage Staff") {
		return nonmage;	
	}
	else if (weap == "Knife") {
		return knife;	
	}
	else if (weap == "Mage Tome") {
		return quickcast;	
	}
	else if (weap == "Mage Staff") {
		return quickcast;	
	}
	else {
		return custom;	
	}
}
