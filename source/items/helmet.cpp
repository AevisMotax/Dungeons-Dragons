#include <array>
#include "helmet.h"
namespace item {
	/**
	 * \brief Helmet's default constructor implementation.
	 *
	 * Sets enhanced ability randomly to either Intelligence, Wisdom, or ArmorClass.
	 */
	Helmet::Helmet() : Item()
	{
		std::array<CharacterStat, 3> possibleEnhancements = {
			CharacterStat::Intelligence,
			CharacterStat::Wisdom,
			CharacterStat::ArmorClass
		};
		enhancedAbility = possibleEnhancements[rand() % possibleEnhancements.size()];
	}

	Helmet::Helmet(int mod, CharacterStat stat, string name) : Item(mod, stat, name) {}

	string Helmet::toString() {
		return name + " (" + getCharacterStatString(enhancedAbility) + ", " + to_string(modifier) + ")";
	}
}

