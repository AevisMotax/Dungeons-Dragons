#pragma once
#include "gridController.h"
#include "tile.h"
#include <source/items/armor.h>
#include <source/items/helmet.h>
#include <source/items/shield.h>
#include <source/items/ring.h>
#include <source/items/boots.h>
#include <source/items/weapon.h>
#include <source/items/belt.h>
#include <source/itemContainer.h>

void GridController::update(char in, int playerInd, Grid *grid, item::Item** chests) {
    if (grid->getTiles(playerInd).getIsChest())
    {
        grid->getTiles(playerInd).switchChest();
        int ind = 0;
        int chestInd = 0;
        while (ind < playerInd)
        {
            if (grid->getTiles(ind).getIsChest())
                chestInd++;
            ind++;
        }
        ItemContainer::insertItem(chests[chestInd]);

        while (chests[chestInd]->getName() != "nullItem123")
        {
            chests[chestInd] = chests[chestInd + 1];
            chestInd++;
        }
    }
}

