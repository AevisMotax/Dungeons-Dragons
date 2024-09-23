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
class FriendlyNpcStrategy : public NpcStrategy {
public:
    FriendlyNpcStrategy(int width, int height, string sentence);
    FriendlyNpcStrategy(string sentence);
    FriendlyNpcStrategy();
    static NpcStrategy& getSingleton();

    char execute(Character* npc, int npcLocation, Character* player, int playerLocation);;

private:
    string sentence;
    static int width;
    static int height;
};