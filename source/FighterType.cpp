#include "FighterType.h"
#include "source/player/CharacterBuilder.h"
#include "player/characterStat.h"
#include "source/player/character.h"
#include "source/player/characterType.h"
#include "source/player/characterObserver.h"
#include<iostream>
#include <typeinfo>
#include <vector>
#include <conio.h>


//COnstructors
Bully::Bully() 
{}

//destructor
Bully::~Bully() 
{}

Character* Bully::getCharacter() 
{
    return character;
}

//A function which will initiate your character.
void Bully::createCharacter() {

    cout << "Hello, Welcome to the Mountain Exploration Game!"
        "Before beginning, may I know your name?" << endl;
    string name;
    string gender;
    cin >> name;
    system("cls");

    gender = character->genderSelection();
    system("cls");

    //Build the character model
    character = new Character(CharacterType::Bully, gender, name, 1);
}

void Bully::assignAbilityOrder() 
{
    // Check if the abilityScores vector is empty
    if (abilityScores.empty()) {
        std::cerr << "Error: Ability scores vector is empty. Cannot assign abilities." << std::endl;
        return; // Exit the function early
    }

    //generating main abilities
    character->setDexterity(abilityScores[2]);
    character->setStrength(abilityScores[0]);
    character->setConstitution(abilityScores[1]);
    character->setCharisma(abilityScores[4]);
    character->setWisdom(abilityScores[5]);
    character->setIntelligence(abilityScores[3]);

    //Generate other stats
    character->initializeHitPoints();
    character->calculateArmor();
    character->calculateAttackBonus();
    character->calculateDamageBonus();
    character->setStrategy(strat);

    //WILL NEED TO CHANGE THIS TO ENSURE NOTHING BREAKS AFTERWARDS
    character->setRounds(character->getAttacksPerRounds());
}

//constructor
Nimble::Nimble() 
{}

//destructor
Nimble::~Nimble() 
{}


Character* Nimble::getCharacter()
{
    return character;
}

//A function which will initiate your character.
void Nimble::createCharacter() {

    cout << "Hello, Welcome to the Mountain Exploration Game!"
        "Before beginning, may I know your name?" << endl;
    string name;
    string gender;
    cin >> name;
    system("cls");

    gender = character->genderSelection();
    system("cls");

    //Build the character model
    character = new Character(CharacterType::Nimble, gender, name, 1);
}

void Nimble::assignAbilityOrder()
{
    // Check if the abilityScores vector is empty
    if (abilityScores.empty()) {
        std::cerr << "Error: Ability scores vector is empty. Cannot assign abilities." << std::endl;
        return; // Exit the function early
    }

    //generating main abilities
    character->setDexterity(abilityScores[0]);
    character->setStrength(abilityScores[2]);
    character->setConstitution(abilityScores[1]);
    character->setCharisma(abilityScores[4]);
    character->setWisdom(abilityScores[5]);
    character->setIntelligence(abilityScores[3]);

    //Generate other stats
    character->initializeHitPoints();
    character->calculateArmor();
    character->calculateAttackBonus();
    character->calculateDamageBonus();
    character->setStrategy(strat);

    //WILL NEED TO CHANGE THIS TO ENSURE NOTHING BREAKS AFTERWARDS
    character->setRounds(character->getAttacksPerRounds());
}

//constructor
Tank::Tank() 
{}

//destructor
Tank::~Tank() 
{}


Character* Tank::getCharacter()
{
    return character;
}

//A function which will initiate your character.
void Tank::createCharacter() {

    cout << "Hello, Welcome to the Mountain Exploration Game!"
        "Before beginning, may I know your name?" << endl;
    string name;
    string gender;
    cin >> name;
    system("cls");

    gender = character->genderSelection();
    system("cls");

    //Build the character model
    character = new Character(CharacterType::Tank, gender, name, 1);
}

void Tank::assignAbilityOrder()
{
    // Check if the abilityScores vector is empty
    if (abilityScores.empty()) {
        std::cerr << "Error: Ability scores vector is empty. Cannot assign abilities." << std::endl;
        return; // Exit the function early
    }

    //generating main abilities
    character->setDexterity(abilityScores[1]);
    character->setStrength(abilityScores[2]);
    character->setConstitution(abilityScores[0]);
    character->setCharisma(abilityScores[4]);
    character->setWisdom(abilityScores[5]);
    character->setIntelligence(abilityScores[3]);

    //Generate other stats
    character->initializeHitPoints();
    character->calculateArmor();
    character->calculateAttackBonus();
    character->calculateDamageBonus();
    character->setStrategy(strat);

    //WILL NEED TO CHANGE THIS TO ENSURE NOTHING BREAKS AFTERWARDS
    character->setRounds(character->getAttacksPerRounds());
}