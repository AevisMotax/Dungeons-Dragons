/**
* The classes that implement a concrete strategy should inherit this.
* The Npc class will use this to move
*/
#ifndef NPCSTRATEGY_H
#define NPCSTRATEGY_H
#define _HAS_STD_BYTE 0
#include "source/player/character.h"

class NpcStrategy {
public:
	/**
	* Method whose implementation varies depending on the strategy adopted.
	*/
	virtual char execute(Character* npc, int npcLocation, Character* player, int playerLocation) = 0;
};
#endif // NPCSTRATEGY_H