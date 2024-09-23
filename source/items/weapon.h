#pragma once
#include "item.h"
namespace item {
	/**
	 * \brief  Weapon class derived from Item.
	 */
	class Weapon : public Item
	{
	public:
		/**
		 * \brief Default Weapon constructor.
		 */
		Weapon();

		/**
		 * \brief Custom Weapon constructor.
		 */
		Weapon(int mod, CharacterStat stat, string name, string weaponType);
		
		string getWeaponType() const { return weaponType; }

		/**
		 * \brief Weapon's toString() method.
		 *
		 * \return Weapon description and statistics.
		 */
		string toString() override;

		private:
			string weaponType;
	};
}

