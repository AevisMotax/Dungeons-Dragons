#include "shield.h"
namespace item {
	/**
	 * \brief Shield's default constructor implementation.
	 *
	 * Sets enhanced ability randomly to ArmorClass.
	 */
	Shield::Shield() :Item()
	{
		enhancedAbility = CharacterStat::ArmorClass;
	}

	Shield::Shield(int mod, CharacterStat stat, string name) : Item(mod, stat, name) {}

	string Shield::toString() {
		return name + " (" + getCharacterStatString(enhancedAbility) + ", " + to_string(modifier) + ")";
	}
}

