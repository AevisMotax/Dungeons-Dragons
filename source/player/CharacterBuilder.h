#ifndef CHARACTERBUILDER_H
#define CHARACTERBUILDER_H

#include "characterObserver.h"
#include "fighter.h"
#include "characterType.h"
#include "source/dice.h"
#include <source/items/armor.h>
#include <source/items/helmet.h>
#include <source/items/shield.h>
#include <source/items/ring.h>
#include <source/items/boots.h>
#include <source/items/weapon.h>
#include <source/items/belt.h>
#include <string>
#include <iomanip>
#include<ctime>
#include <typeinfo>
#include <conio.h>
#include <vector>
#include <cstdlib>
#include <thread>
#include <atomic>
#include<map>


/**
* @brief Abstract Class implementation for the creation of more creativbe characters
*/
class CharacterBuilder
{
public:
    //Constructors and Destructors
    CharacterBuilder();
    virtual ~CharacterBuilder() {}

    //Functions

    /** @brief get character*/
    virtual  Character* getCharacter();

    /** @brief set CHaracter */



    /** @brief generation of levels*/
    virtual void generateLevel();
   
    virtual void generateRandomLevel();

    /** @brief Allows user to generate abilities based on 4d6[+0]*/
    void buildRandomAbilityScores();

    /**@brief Allows user to choose their dice and roll it */
    void userSelectsAbilityScores();

    /** @brief */
    virtual void assignAbilityOrder() = 0;

    /**@brief */
    virtual void createCharacter();

    ///**\brief create enemy  */
    //virtual void createNPCs();

    ///**@brief */
    //void selectFighterType();


    //virtual Character* createEnemy(CharacterType& type );

    /** @brief convert character typ into printable format*/
    string convertType();

    /**@brief get fighter's level */
    int getFighterLevel();
    /**@brief change fighter's level */
    void setFighterLevel(int level);

    /**@method Easter Eggs */
    //void getGodMode();


protected:
    std::vector<int> abilityScores; ///< Ability scores in decreasing order of importance
    string strat;
    dice DICE; ///<Dice to use for the user
    Character* character; ///< Products build by Character Builder
};



#endif // !CHARACTERBUILDER_H

