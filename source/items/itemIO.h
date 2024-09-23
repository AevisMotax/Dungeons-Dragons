#define _HAS_STD_BYTE 0
#ifndef ITEM_H
#define ITEM_H
#include <source/items/armor.h>
#include <source/items/helmet.h>
#include <source/items/shield.h>
#include <source/items/ring.h>
#include <source/items/boots.h>
#include <source/items/weapon.h>
#include <source/items/belt.h>
#include <source/items/item.h>

class ItemIO {
	public:
		static void createItem();
		static item::Item* loadItem(string name);
	private:
		static void makeItem(string &name, int &mod);
		static void makeArmor();
		static void makeBelt();
		static void makeBoots();
		static void makeHelmet();
		static void makeRing();
		static void makeShield();
		static void makeWeapon();
};
#endif //ITEM_H
