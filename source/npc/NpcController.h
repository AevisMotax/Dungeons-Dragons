#ifndef NPC_H
#define NPC_H
#include "npcStrategy.h"
#include "source/logger/logger.h"
#include "source/map/grid.h"

class NpcController {
public:
	NpcController();
	NpcController(int ind);
	NpcController(int ind, Grid& newGrid, Character& enemy);
	void nextTurn(Character* player, int playerLocation);
	bool update(char in);
	int getNpcInd() { return npcInd; }
	Character* getCharacter() { return &character; }
	void setGrid(Grid& newGrid);
	void setNpcInd(int ind) { npcInd = ind; }
	void setStrategy(NpcStrategy* strat) { strategy = strat; }

	NpcController& operator=(const NpcController& other) {
		if (this != &other) {
			// Copy the character
			character = other.character;

			// Copy npcInd
			npcInd = other.npcInd;

			// Update the grid reference
			grid = other.grid;

			// Ensure both objects share the same NpcStrategy
			strategy = other.strategy;
		}
		return *this;
	}

private:
	Character character;
	NpcStrategy* strategy;
	int npcInd;
	Grid* grid;
	Logger* logger;
};

#endif //NPC_H