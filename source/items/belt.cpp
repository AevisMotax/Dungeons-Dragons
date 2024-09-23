#include <stdlib.h>
#include "belt.h"
namespace item {
	/**
	 * \brief Belt's default constructor implementation.
	 *
	 * Sets enhanced ability randomly to either Constitution or Strength.
	 */
	Belt::Belt() : Item()
	{
		enhancedAbility = rand() % 2 == 1 ? CharacterStat::Constitution : CharacterStat::Strength;
	}

	Belt::Belt(int mod, CharacterStat stat, string name) : Item(mod, stat, name) {}


	string Belt::toString() {
		return name + " (" + getCharacterStatString(enhancedAbility) + ", " + to_string(modifier) + ")";
	}
}

