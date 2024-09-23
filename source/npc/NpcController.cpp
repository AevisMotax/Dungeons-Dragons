#include "NpcController.h"
#include "source/map/grid.h"
#include "source/logger/logger.h"
Grid globalGrid = Grid(1, 1);
//Grid &NpcController::grid = globalGrid;
NpcController::NpcController():grid(&globalGrid)
{
    npcInd = -1;
    logger = Logger::getSingleton();
}

NpcController::NpcController(int ind):grid(&globalGrid)
{
    npcInd = ind;
    logger = Logger::getSingleton();
}

NpcController::NpcController(int ind, Grid &newGrid, Character& enemy):grid(&newGrid)
{
    npcInd = ind;
    character = enemy;
    logger = Logger::getSingleton();
}

void NpcController::setGrid(Grid& newGrid)
{
    *grid = newGrid;
    logger = Logger::getSingleton();
}

void NpcController::nextTurn(Character* player, int playerLocation)
{
	char move = strategy->execute(getCharacter(), npcInd, player, playerLocation);

	update(move);
    string ind = std::to_string(npcInd) + "";
    logger->log("grid", character.getName() + " has moved to " + ind);
}

//Update the player every frame
//int in: user input
bool NpcController::update(char in)
{
    int tempInd = -1;
    //If the user is pressing the left arrow move left
    if (in == '%')
    {
        //Player's new location
        tempInd = grid->moveLeft(getNpcInd());
    }
    //Same as moving left but for moving right
    else if (in == '\'')
    {
        tempInd = grid->moveRight(getNpcInd());
    }
    //Same as moving left but for moving up
    else if (in == '&')
    {
        tempInd = grid->moveUp(getNpcInd());
    }
    //Same as moving left but for moving down
    else if (in == '(')
    {
        tempInd = grid->moveDown(getNpcInd());
    }
    //Check if the user is at the border
    if (tempInd != -1)
    {
        //Get the new tile
        Tile* currentTile = &grid->getTiles(tempInd);
        //Switch the tile to a player tile and check if it is possible
        if (!(currentTile->getIsEnemy()))
        {
            if (currentTile->switchEnemy())
            {
                //Get the old tile and remove the player from that tile
                Tile* previousTile = &grid->getTiles(getNpcInd());
                previousTile->switchEnemy();
                //Update player's location
                setNpcInd(tempInd);
            }
        }
    }
    return true;
}