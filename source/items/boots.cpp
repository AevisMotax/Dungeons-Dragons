#include <stdlib.h>
#include "boots.h"
namespace item {
	/**
	 * \brief Belt's default constructor implementation.
	 *
	 * Sets enhanced ability randomly to either ArmorClass or Dexterity.
	 */
	Boots::Boots() : Item()
	{
		enhancedAbility = rand() % 2 == 1 ? CharacterStat::ArmorClass : CharacterStat::Dexterity;
	}

	Boots::Boots(int mod, CharacterStat stat, string name) : Item(mod, stat, name) {}

	string Boots::toString() {
		return name + " (" + getCharacterStatString(enhancedAbility) + ", " + to_string(modifier) + ")";
	}
}

