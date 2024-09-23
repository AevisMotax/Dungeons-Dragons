#include "FriendlyNpcStrategy.h"
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

FriendlyNpcStrategy singleton = FriendlyNpcStrategy();
int FriendlyNpcStrategy::width = 0;
int FriendlyNpcStrategy::height = 0;

FriendlyNpcStrategy::FriendlyNpcStrategy() {};

FriendlyNpcStrategy::FriendlyNpcStrategy(int width, int height, string sentence)
{
    this->width = width;
    this->height = height;
    this->sentence = sentence;
}

FriendlyNpcStrategy::FriendlyNpcStrategy(string sentence)
{
    this->sentence = sentence;
}

NpcStrategy& FriendlyNpcStrategy::getSingleton()
{
    return singleton;
}

char FriendlyNpcStrategy::execute(Character* npc, int npcLocation, Character* player, int playerLocation)
{
    if (npcLocation + width == playerLocation)
    {
        cout << sentence << endl;
        cin.get();
    }
    else if (npcLocation - width == playerLocation)
    {
        cout << sentence << endl;
        cin.get();
    }
    else if (npcLocation + 1 == playerLocation && npcLocation % width != width - 1)
    {
        cout << sentence << endl;
        cin.get();
    }
    else if (npcLocation - 1 == playerLocation && npcLocation % width != 0)
    {
        cout << sentence << endl;
        cin.get();
    }
   
    return 'n';
}