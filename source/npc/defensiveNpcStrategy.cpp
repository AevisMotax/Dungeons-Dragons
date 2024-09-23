#include "DefensiveNpcStrategy.h"
#include "source/player/character.h"
#include "source/map/playerController.h"
#include "source/map/Tile.h"
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <climits>
#include <chrono>
#include <thread>

DefensiveNpcStrategy singleton = DefensiveNpcStrategy();
int DefensiveNpcStrategy::width = 0;
int DefensiveNpcStrategy::height = 0;

DefensiveNpcStrategy::DefensiveNpcStrategy() {}

DefensiveNpcStrategy::DefensiveNpcStrategy(int width, int height)
{
    this->width = width;
    this->height = height;
}

NpcStrategy& DefensiveNpcStrategy::getSingleton()
{
    return singleton;
}

char DefensiveNpcStrategy::execute(Character* npc, int npcLocation, Character* player, int playerLocation)
{
    if (npcLocation + width == playerLocation)
    {
        npc->attackEnemy(*player);
        cin.get();
    }
    else if (npcLocation - width == playerLocation)
    {
        npc->attackEnemy(*player);
        cin.get();
    }
    else if (npcLocation + 1 == playerLocation && npcLocation % width != width -1)
    {
        npc->attackEnemy(*player);
        cin.get();
    }
    else if (npcLocation - 1 == playerLocation && npcLocation % width != 0)
    {
        npc->attackEnemy(*player);
        cin.get();
    }
        
    return 'n';
}