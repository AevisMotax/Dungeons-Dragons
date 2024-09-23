#pragma once
#include "source/player/characterStat.h"
using namespace std;
namespace item {
	/**
	 * \brief  Item is a simple abstract class providing the common interface for other item derived classes..
	 */
	class Item
	{
	public:
		/**
		 * \brief Default constructor for Item.
		 */
		Item();

		/**
		 * \brief custom constructor for Item.
		 */
		Item(int mod, CharacterStat stat, string name);

		/**
		 * Basic Item destructor.
		 */
		virtual ~Item() {};

		/**
		 * \brief Get the character ability this item enhances.
		 * 
		 * \return Character ability this item enhances.
		 */
		CharacterStat getEnhancedAbility() const;

		/**
		 * \brief Get modifier value of the enhanced character ability.
		 * 
		 * \return Modifier value of the enhanced character ability.
		 */
		int getModifier() const;

		void setName(string name);

		/**
		 * \brief Get name value of the item.
		 *
		 * \return name of the item.
		 */
		string getName() { return name; }

		/**
		 * \brief Base virtual toString() method that derived classes override with their specific implementation.
		 * 
		 * \return String representation of the Item object.
		 */
		virtual string toString() = 0;

	protected:
		CharacterStat enhancedAbility; ///< Stores the type of the enhanced character ability.
		int modifier; ///< Stores the modifier value of the enhanced character ability.
		string name; ///< The name of the item
	};
}
