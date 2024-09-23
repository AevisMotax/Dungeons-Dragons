#pragma once
#include "npcStrategy.h"
#include "source/map/Tile.h"
#include<iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <climits>
using namespace std;
/**
* A concrete Strategy that implements a friendly movment for npcs
*/
class DefensiveNpcStrategy : public NpcStrategy {
public:
    DefensiveNpcStrategy(int width, int height);
    DefensiveNpcStrategy();
    static NpcStrategy& getSingleton();

    char execute(Character* npc, int npcLocation, Character* player, int playerLocation);;

private:
    static int width;
    static int height;
};