#include <array>
#include "ring.h"
namespace item {
	/**
	 * \brief Ring's default constructor implementation.
	 *
	 * Sets enhanced ability randomly to either ArmorClass, Strength, Constitution, Wisdom, or Charisma.
	 */
	Ring::Ring() : Item()
	{
		std::array<CharacterStat, 5> possibleEnhancements = {
			CharacterStat::ArmorClass,
			CharacterStat::Strength,
			CharacterStat::Constitution,
			CharacterStat::Wisdom,
			CharacterStat::Charisma
		};
		enhancedAbility = possibleEnhancements[rand() % possibleEnhancements.size()];
	}

	Ring::Ring(int mod, CharacterStat stat, string name) : Item(mod, stat, name) {}

	string Ring::toString() {
		return name + " (" + getCharacterStatString(enhancedAbility) + ", " + to_string(modifier) + ")";
	}
}

