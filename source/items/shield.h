#pragma once
#include "item.h"
namespace item {
	/**
	 * \brief  Shield class derived from Item.
	 */
	class Shield : public Item
	{
	public:
		/**
		 * \brief Default Shield constructor.
		 */
		Shield();

		/**
		 * \brief Custom Shield constructor.
		 */
		Shield(int mod, CharacterStat stat, string name);

		/**
		 * \brief Shield's toString() method.
		 *
		 * \return Shield description and statistics.
		 */
		string toString() override;
	};
}

