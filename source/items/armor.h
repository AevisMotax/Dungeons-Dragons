#pragma once
#include "item.h"
namespace item {

	enum ArmorType {
		Light,
		Medium,
		Heavy
	};


	/**
	 * \brief  Armor class derived from Item.
	 */
	class Armor : public Item
	{
	public:
		/**
		 * \brief Default Armor constructor.
		 */
		Armor();

		/**
		 * \brief Custom Armor constructor.
		 */
		Armor(int mod, CharacterStat stat, string name);
		
		/**
		 * \brief Custom Armor constructor with armorType (light,medium and heavy) included.
		*/
		Armor(int mod, CharacterStat stat, string name, ArmorType type);
		/**
		 * \brief Armor's toString() method.
		 * 
		 * \return Armor description and statistics.
		 */
		string toString() override;

		/** 
		* \brief return armor type so that logs and users can see 
		* \return Amor type
		*/
		string getArmorTypeToString(ArmorType& type);


		/** 
		* \brief get and set armor types
		*/
		void setArmorType(ArmorType type) { armorType = type; };

		ArmorType getArmor() const { return armorType;  };


	private:
		ArmorType armorType; ///<type of armor if it works
	};


	/**
	* \brief overloaded assignment operators of >>
	*/
	istream& operator>>(istream& is, item::ArmorType& armor);
	/**
	* \brief overloaded assignment operators of <<
	*/
	ostream& operator<<(ostream& os, const item::ArmorType& armorTypeToString);
}



