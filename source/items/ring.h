#pragma once
#include "item.h"
namespace item {
	/**
	 * \brief  Ring class derived from Item.
	 */
	class Ring : public Item
	{
	public:
		/**
		 * \brief Default Ring constructor.
		 */
		Ring();

		/**
		 * \brief Custom Ring constructor.
		 */
		Ring(int mod, CharacterStat stat, string name);

		/**
		 * \brief Ring's toString() method.
		 *
		 * \return Ring description and statistics.
		 */
		string toString() override;
	};
}

