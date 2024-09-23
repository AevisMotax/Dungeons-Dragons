#include <stdlib.h>
#include "weapon.h"
namespace item {
	/**
	 * \brief Weapon's default constructor implementation.
	 *
	 * Sets enhanced ability randomly to either AttackBonus or DamageBonus.
	 */
	Weapon::Weapon() : Item()
	{
		enhancedAbility = rand() % 2 == 1 ? CharacterStat::AttackBonus : CharacterStat::DamageBonus;
		this->weaponType = "Sword";
	}

	Weapon::Weapon(int mod, CharacterStat stat, string name, string weaponType) : Item(mod, stat, name) 
	{
		this->weaponType = weaponType;
	}

	string Weapon::toString() {
		return name + " (" + getCharacterStatString(enhancedAbility) + ", " + to_string(modifier) + ", " + weaponType + ")";
	}
}

