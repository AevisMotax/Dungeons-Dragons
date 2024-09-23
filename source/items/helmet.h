#pragma once
#include "item.h"
namespace item {
	/**
	 * \brief  Helmet class derived from Item.
	 */
	class Helmet : public Item
	{
	public:
		/**
		 * \brief Default Helmet constructor.
		 */
		Helmet();

		/**
		 * \brief Custom Helmet constructor.
		 */
		Helmet(int mod, CharacterStat stat, string name);

		/**
		 * \brief Helmet's toString() method.
		 *
		 * \return Helmet description and statistics.
		 */
		string toString() override;
	};
}

