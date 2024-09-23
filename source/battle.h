#ifndef BATTLE_H
#define BATTLE_H
#include "player/character.h"
#include <iostream>
using namespace std;

/**
* @brief This is the header file battle.h.This is the interface for the class battle.
* This class takes the player character and an enemy character, then it will run until the player kills the enemy using the attackEnemy(enemy) function of the character class.
*/
class Battle {

public:
    /**\ /@brief This is the constructor for the battle class. It takes a player and generates an enemy.
        * @param chacter is the player's character */
    Battle(Character& player, Character& enemy);
    /**\ /@brief Prints the state of the battle.
    *\return return the resulting string*/
    string toString();
    /**\ /@brief Goes to the next turn of the battle.
    *\return return if the battle is over*/
    bool nextTurn();
    /**\ /@brief Process the player's action*/
    void processAction();
private:
    Character *player; ///< The player character
    Character *enemy; ////< The enemy to fight.
};

#endif //TILE_H
