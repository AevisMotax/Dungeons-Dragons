#pragma once
#include "item.h"
namespace item {
	/**
	 * \brief  Belt class derived from Item.
	 */
	class Belt : public Item
	{
	public:
		/**
		 * \brief Default Belt constructor.
		 */
		Belt();

		/**
		 * \brief Custom Belt constructor.
		 */
		Belt(int mod, CharacterStat stat, string name);

		/**
		 * \brief Belt's toString() method.
		 *
		 * \return Belt description and statistics.
		 */
		string toString() override;
	};
}

