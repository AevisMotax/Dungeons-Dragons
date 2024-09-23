/**
* The classes that implement a HumanCharacterStrategy should inherit this.
* The playerController class will use this to move and attack
*/
#include "source/npc/npcController.h"
#include "source/player/characterStrategy.h"
#ifndef HUMANCHARACTERSTRATEGY_H
#define HUMANCHARACTERSTRATEGY_H

class HumanCharacterStrategy:public CharacterStrategy {
public:
	/**
	* Method whose implementation varies depending on the strategy adopted.
	*/
	bool execute(char in, NpcController* npcs, int& playerInd, Grid* grid, Character& character);
};
#endif // HUMANCHARACTERSTRATEGY_H