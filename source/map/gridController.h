#ifndef GRIDCONTROLLER_H
#define GRIDCONTROLLER_H
#include "grid.h"
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

/**
 * @brief Values of this type are gridController,  they update the grid.
 */
class GridController {
public:
    /**\/@brief Update the grid, happens every frame
    *@param the in is the player's input
    *@param the playerInd is the player's current tile*/
    void update(char in, int playerInd, Grid* grid, item::Item** chests);
};

#endif //GRIDCONTROLLER_H