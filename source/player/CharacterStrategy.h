/**
* The classes that implement a concrete strategy should inherit this.
* The playerController class will use this to move and attack
*/
#include "source/npc/npcController.h"
#ifndef CHARACTERSTRATEGY_H
#define CHARACTERSTRATEGY_H

class CharacterStrategy {
public:
	/**
	* Method whose implementation varies depending on the strategy adopted.
	*/
	virtual bool execute(char in, NpcController* npcs, int& playerInd, Grid* grid, Character& character) = 0;
};
#endif // CHARACTERSTRATEGY_H