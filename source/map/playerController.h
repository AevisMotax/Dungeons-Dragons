#ifndef PLAYER_H
#define PLAYER_H
#define _HAS_STD_BYTE 0
#include "source/globalFunctions.h"
#include "tile.h"
#include "grid.h"
#include "source/player/character.h"
#include "source/FighterType.h"
#include "source/CharacterDirector.h"
#include "source/npc/NpcController.h"
#include "source/player/characterStrategy.h"
#include <iostream>
#include <cstdlib>

using namespace std;

/**
 * @brief This is the header file playerController.h.This is the interface for the class playerController.
 * /
 * Values of this type are players of the map. The user interacts with the world through the playerController. 
 */
class PlayerController {
public:
    /**
    * @brief Intialize and set the controller start location
    */
    PlayerController(Grid& igrid);

    /**\/@brief Return player's location
    * \return The players location number */
    int getPlayerInd();

    /**\/@brief Return the character
    * \return The player's character */
    Character* getCharacter();

    /**\/@brief Return the character
    * \return The player's character */
    CharacterDirector getCharacterGenerator();


    /**\/@brief Set the player's character */
    //void setCharacter(Character character);
    //void setCharacterBuilder(CharacterBuilder& character);

    void resetInd() { playerInd = 0; }

    /**\/@brief Update the player, e.g move the player when the user asks to
    * \return The result of the update */
    bool update(char in, NpcController* npcs);

    /**\brief display menu to indicate current selection */
    void displayCharacterSelectionScreen(int selection);

    /**\/@brief Create the character that will be played for this game
    */
    void customizeCharacter();

    /**@brief load Character */
    void loadCharacter();

    /**@brief choose a brand new character creation*/
    void selectFighterType();

    /**@brief make enemies */
    void createEnemies();

private:
    int playerInd;///<Player's location

    CharacterStrategy* strategy;
    CharacterDirector director; ///<The Director

    Tank* tank = new Tank; ///<creational process of character building and stuff
    Nimble* nimble = new Nimble; ///<creational process of character building and stuff
    Bully* bully = new Bully; ///<creational process of character building and stuff

    //Goblin* goblin = new Goblin; ///<enemies only


    Character* character;///<The character associated with the controller
    std::vector<Character> enemies; ///< the amount of enemies in the game


    Grid& grid;///<Map the player's on
    Logger* logger;
};

#endif //GRID_H

