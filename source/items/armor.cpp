#include "armor.h"
#include <iostream>
#include<string>


namespace item {
	/**
	 * \brief Armor's default constructor implementation.
	 * 
	 * Sets enhanced ability to ArmorClass.
	 */
	Armor::Armor() : Item()
	{
		enhancedAbility = CharacterStat::ArmorClass;
	}

	Armor::Armor(int mod, CharacterStat stat, string name) : Item(mod, stat, name) {}


	//Constructor made to characterize light,medium and heavgy armor
	Armor::Armor(int mod, CharacterStat stat, string name, ArmorType type) : Item(mod, stat, name), armorType(type)
	{}

	//return to string
	string Armor::getArmorTypeToString(ArmorType& type) {
		if (type == Light) {
			return "light";
		}
		else if (type == Medium) {
			return "medium";
		}
		else if (type == Heavy) {
			return "heavy";
		}
		else {
			return "normal";
		}

	}


	string Armor::toString() {
		return name + " (" + getArmorTypeToString(armorType) + " " + getCharacterStatString(enhancedAbility) + ", " + to_string(modifier) + ")";
	}

	

	//Overloaded assignment operator
	ostream& operator<<(ostream& os, const item::ArmorType& armorTypeToString) 
	{
		switch (armorTypeToString) {
		case ArmorType::Light:
			os << "Light";
			break;
		case ArmorType::Medium:
			os << "Medium";
			break;
		case ArmorType::Heavy:
			os << "Heavy";
			break;
		default:
			os << "Light";
			break;
		}
		return os;
	
	}

	//Overloaded assignment operator
	istream& operator>>(istream& is, item::ArmorType& armor)
	{
		int input;
		std::cin >> input;

		// Convert the input to ArmorType
		if (input == 1) {
			armor = item::ArmorType::Light;
		}
		else if (input == 2) {
			armor = item::ArmorType::Medium;
		}
		else if (input == 3) {
			armor = item::ArmorType::Heavy;
		}
		else {
			armor = item::ArmorType::Light;
		}
		return is;
	}
}



