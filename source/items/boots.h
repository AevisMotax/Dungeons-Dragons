#pragma once
#include "item.h"
namespace item {
	/**
	 * \brief  Boots class derived from Item.
	 */
	class Boots :
		public Item
	{
	public:
		/**
		 * \brief Default Boots constructor.
		 */
		Boots();

		/**
		 * \brief Custom Boots constructor.
		 */
		Boots(int mod, CharacterStat stat, string name);

		/**
		 * \brief Boots' toString() method.
		 *
		 * \return Boots description and statistics.
		 */
		string toString() override;
	};
}

