#pragma once
#ifndef ITEMCONTAINER_H
#define ITEMCONTAINER_H
#include <source/items/item.h>
#include <source/items/armor.h>
#include <source/items/helmet.h>
#include <source/items/shield.h>
#include <source/items/ring.h>
#include <source/items/boots.h>
#include <source/items/weapon.h>
#include <source/items/belt.h>
#include <source/player/character.h>
/**
 * \brief ItemContainer class contains the character's items, acting as an inventory.
 */
class ItemContainer
{
public:
	/**
	 * \brief Insert a random item into ItemContainer.
	 *
	 * \param item Pointer to Item to be added to ItemContainer.
	 */
	static void insertRandomItem()
	{
		string name = "Rusty ";
		int itemType = rand() % 7;
		item::Item* item = new item::Armor();
		if (itemType == 0){
			name += "Armor";
			item = new item::Armor();
		}else if (itemType == 1){
			name += "Belt";
			item = new item::Belt();
		}else if (itemType == 2){
			name += "Boots";
			item = new item::Boots();
		}else if (itemType == 3){
			name += "Heltmet";
			item = new item::Helmet();
		}else if (itemType == 4){
			name += "Ring";
			item = new item::Ring();
		}else if (itemType == 5){
			name += "Shield";
			item = new item::Shield();
		}else if (itemType == 6){
			name += "Weapon";
			item = new item::Weapon();
		}
		item->setName(name);
		items[index] = item;
		index++;
	}


	/**
	 * \brief Insert an item into ItemContainer.
	 * 
	 * \param item Pointer to Item to be added to ItemContainer.
	 */
	static void insertItem(item::Item* item)
	{
		items[index] = item;
		index++;
	}

	/**
	 * \brief Get item from ItemInventory by index.
	 * 
	 * \param i Item's index in the ItemContainer.
	 * \return  Pointer to Item.
	 */
	static item::Item* getItem(int i)
	{
		return items[i];
	}

	/**
	 * \brief Display list of ItemContainer contents.
	 * 
	 * \return List of ItemContainer contents
	 */
	static string toString(Character player)
	{
		string s = "";
		for (int i = 0; i < index; i++)
		{
			s += "" + std::to_string(i);
			s += ". " + items[i]->toString();
			if (player.getHelmet() == items[i] 
				|| player.getArmor() == items[i]
				|| player.getRing() == items[i]
				|| player.getBelt() == items[i]
				|| player.getBoots() == items[i]
				|| player.getWeapon() == items[i]
				|| player.getShield() == items[i])
				s += "(Equipped)\n";
			else
				s += "(In Bag)\n";
		}
		return s;
	}
private:
	static item::Item* items[200]; ///< Array of items to contain character's items.
	static int index; ///< Next available index in the items array.
};

#endif //ITEMCONTAINER_H

