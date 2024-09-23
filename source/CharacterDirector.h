#ifndef CHARACTERDIRECTOR_H
#define CHARACTERDIRECTOR_H

#include "player/Customizable/CharacterIO.h"
#include "source/globalFunctions.h"
#include "source/player/CharacterBuilder.h"
#include "source/FighterType.h"
#include "source/player/character.h"
#include "source/player/characterType.h"
#include "source/player/characterObserver.h"

#include<iostream>
#include<string>
#define stringify( name ) #name
#include <typeinfo>
#include <vector>
#include<map>

/**
* @brief
*/
class CharacterDirector {

public:

    /**
    * @brief
    */
    CharacterDirector();

    /**@brief getter */
    Character* getCharacter();

    /**\brief editor menu for characters */
    void characterEditorMenu();


    /**\/@brief Create the character that will be played for this game
    */
    void constructCharacter();


    /**\/@brief Create the character's name that will be played for this game and saved for the file
    */
    string createCharacterName();

    /**\brief Load character from files*/
    Character* loadCharacterFromFile();

    /**@brief choose a brand new character creation*/
    void selectFighterType();
    /**\/@brief Create the character that will be played for this game
    */
    //template<class T>
    void setCharacterBuilder(CharacterBuilder* Builder);

    /**@brief to generate random enemies */
    Character* createEnemy();

    /**@brief So that USer may create their own made enemies */
    Character* customizeEnemy();

private:
    //std::unique_ptr<CharacterBuilder> builder;
    CharacterBuilder* c_builder;
    CharacterIO* generator = new CharacterIO;
};


#endif
