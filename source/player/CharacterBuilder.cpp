#include "CharacterBuilder.h"
#include "source/globalFunctions.h"
#include "source/FighterType.h"
#include "character.h"
#include "characterType.h"
#include "source/dice.h"
#include "characterObserver.h"
#include<iostream>
#include<string>
#define stringify( name ) #name
#include <typeinfo>
#include <conio.h>
#include <vector>
#include <cstdlib>
#include <thread>
#include <atomic>
#include<map>

using std::cout;
using std::cin;
using std::endl;

//Constructor (SLIGHTLY USELESS)
CharacterBuilder::CharacterBuilder() 
{}


//A function which will initiate your character.
void CharacterBuilder::createCharacter() {

    system("cls");
    cout <<"May I know your name? " << endl;
    string name;
    string gender;
    cin >> name;
    system("cls");

    gender = character->genderSelection();
    system("cls");

    //Build the character model
    character = new Character(CharacterType::Hero, gender, name, 3);
}


//Selection of fighters
//void CharacterBuilder::selectFighterType() {
//    int userInput;
//
//    while (true) {
//        system("cls");  // Clear console screen (Windows specific)
//        cout << "=== Character Fighting Type ===" << endl;
//        cout << "Below are the type of fighter you may wish to be:\nPlease select one of them by pressing the corresponding index "
//            "NOTE: ONLY BULLY, NIMBLE, AND TANK WORK AS OF NOW!!!";
//
//        //Showcase information of the CHaracters and stuff
//        for (int i = static_cast<int>(CharacterType::Bully); i <= static_cast<int>(CharacterType::Tank); i++) {
//            CharacterType type = static_cast<CharacterType>(i);
//            std::cout << static_cast<int>(type) << ". " << stringify(type) << ": " << characterTypeInfo[i] << std::endl;
//        }
//
//        cin >> userInput;
//
//        // Process user input
//        if (userInput == 1) {
//            character->setCharacterClass(CharacterType::Bully);
//        }
//        else if (userInput == 2) {
//            character->setCharacterClass(CharacterType::Nimble);
//        }
//        else if (userInput == 3) {
//            character->setCharacterClass(CharacterType::Tank);
//        }
//        else {
//            cout << "\nNot valid, try again:";
//            _getch(); //Pause
//        }
//    }
//}

//Build randomize ability socres: This is based on 4d6[+0] die kind which is a valuable option
void CharacterBuilder::buildRandomAbilityScores() 
{
    std::vector<int> singleRoll;

    bool temp = DICE.validateDyKind("4d6[+0]"); //validate the thing dice 

    //Hard-coded
    for (int i = 0; i < 6; i++) {
        if (temp) {
            singleRoll = DICE.obtainSingleDieValue(); //acquire randomize dice data

            //sorting it out
            sort(singleRoll.begin(), singleRoll.end(), greater<int>());

            //sort it for the abilities with the 3 highest dice values
            abilityScores.push_back(singleRoll[0] + singleRoll[1] + singleRoll[2]);
        }
        else 
        {
            //Exit the project
            cerr << "An Error occurred. Will Exit" << std::endl;
            exit(1);
        }
    }
    int stratInd = rand() % 3;
    if (stratInd == 0)
        strat = "friendly";
    else if (stratInd == 1)
        strat = "aggresive";
    else if (stratInd == 2)
        strat = "defensive";
}


//If user wishes to choose their own dice
void CharacterBuilder::userSelectsAbilityScores()
{
    std::vector<int> singleRoll;

    string dyKind = DICE.diceExpression();

    bool temp = DICE.validateDyKind(dyKind); //validate the thing dice 

    //Hard-coded
    for (int i = 0; i < 6; i++) {
        if (temp) {
            DICE.rollDie(dyKind);
            //sort it for the abilities with the 3 highest dice values
            abilityScores.push_back(DICE.getTotal());
        }
        else
        {
            //Exit the project
            cerr << "An Error occurred. Will Exit" << std::endl;
            exit(1);
        }
    }
    while (true)
    {
        cout << "Enter your character start (friendly, aggresive or defensive): " << endl;
        cin >> strat;
        string stratType = strat;
        system("cls");
        if (strat == "friendly")
        {
            cout << "What do you want your character to say? " << endl;
            cin >> strat;
            std::cin.ignore(1000, '\n');
            std::cin.clear();
        }
        if (stratType == "friendly" || stratType == "aggresive" || stratType == "defensive")
            break;
        else
            cout << "Invalid input, try again!";
    }
    cout << "Press Enter To Continue.";
    cin.get();
}



//Method assign ability according to stats
void CharacterBuilder::assignAbilityOrder() 
{
    // Check if the abilityScores vector is empty
    if (abilityScores.empty()) {
        std::cerr << "Error: Ability scores vector is empty. Cannot assign abilities." << std::endl;
        return; // Exit the function early
    }

    //generating main abilities
    character->setDexterity(abilityScores[0]);
    character->setStrength(abilityScores[1]);
    character->setConstitution(abilityScores[2]);
    character->setCharisma(abilityScores[3]);
    character->setWisdom(abilityScores[4]);
    character->setIntelligence(abilityScores[5]);
    character->initializeHitPoints();
    character->calculateArmor();
    character->calculateAttackBonus();
    character->calculateDamageBonus();
    character->setStrategy(strat);
}

//Generating levels
void CharacterBuilder::generateLevel() {
    //Ask user which level they want their character to start with (MAX: 5)
    int changeLevel;

    cout << "Please select which level you want to start at (MAX: 5)" << std::endl;
    cin >> changeLevel;

    character->setLevel(changeLevel);
    character->initializeHitPoints(); //Re-initialize the hit points level
}

//Generatw random level for the Enemies when appearing on the map
void CharacterBuilder::generateRandomLevel() {
    //Randomly generate level but based on the user
// Generate a random number within the range of 1-3
    int levelDifference = rand() % 2 + 1;
    // Randomly determine if the enemy's level should be higher or lower than the character's level
    bool increaseLevel = rand() % 2 == 0;

    // Adjust the enemy's level based on the character's level and the randomly generated difference
    int changeLevel = increaseLevel ? character->getLevel() + levelDifference : character->getLevel() - levelDifference;
    character->setLevel(changeLevel);
}

//Return who the character is
Character* CharacterBuilder::getCharacter() {
    return character;
}


//Enemy;s name
//string Character::generateEnemyName() {
//    // Seed the random number generator
//    srand(static_cast<unsigned>(time(nullptr)));
//
//    // Generate a random index to select a name from the list
//    int index = rand() % ENEMY_NAMES.size();
//
//
//
//    // Return the randomly selected name
//    return ENEMY_NAMES[index];
//}


//Getters and setters
int CharacterBuilder::getFighterLevel() 
{
    return character->getLevel();
}

void CharacterBuilder::setFighterLevel(int level) 
{
    character->setLevel(level);
}

////Godman Mode
//void CharacterBuilder::getGodMode()
//{
//    if (this->character->getName() == "godman")
//    {
//        this->character->setHitpoints(1000);
//        this->character->setAttackBonus(5);
//        this->character->setDamageBonus(5);
//    }
//}


//return character's fighter Type
string CharacterBuilder::convertType() {
    return stringify(character->getCharacterClass());
};