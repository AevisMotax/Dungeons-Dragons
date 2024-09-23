#include "character.h"
#include "source/globalFunctions.h"
#include "characterType.h"
#include "characterObserver.h"
#include "source/dice.h"
#include "source/logger/logger.h"
#include <conio.h>
#include<iostream>
#include <typeinfo>
#include <vector>
#include <cstdlib>
#include <thread>
#include <atomic>
#include <cstdlib>
using std::string;
using std::cout;
using std::cin;
using std::endl;


Character::Character(string name) : Fighter(CharacterType::Hero, 1)
{
    this->name = name;
    this->gender = "M";
  
    //generating main abilities
    this->dexterity = abilityRandomizer();
    this->strength = abilityRandomizer();
    this->constitution = abilityRandomizer();
    this->charisma = abilityRandomizer();
    this->wisdom = abilityRandomizer();
    this->intelligence = abilityRandomizer();
    calculateHitPoints();
    calculateArmor();
    calculateAttackBonus();
    calculateDamageBonus();
}

//CONSTRUCTORS: initialize character for random purposes
Character::Character() : Fighter(CharacterType::Unknown, 1)
{
    this->name = "The Enemy";
    this->gender = "M";
}

//Mainly for Enemies and Stuff
Character::Character(const CharacterType& type, const string& name, int level)
    :name(name), Fighter(type, level)
{
    this->gender = "";

    //generating main abilities
    this->dexterity = abilityRandomizer();
    this->strength = abilityRandomizer();
    this->constitution = abilityRandomizer();
    this->charisma = abilityRandomizer();
    this->wisdom = abilityRandomizer();
    this->intelligence = abilityRandomizer();
    initializeHitPoints();
    calculateArmor();
    calculateAttackBonus();
    calculateDamageBonus();

    //Generate the amount of rounds the enemy can attack
    this->rounds = getAttacksPerRounds();
}

Character::Character(const CharacterType& type, const string& gender, const string& name, int level)
    :gender(gender), name(name), Fighter(type, level)
{
    //generating main abilities
 /*   this->dexterity = abilityRandomizer();
    this->strength = abilityRandomizer();
    this->constitution = abilityRandomizer();
    this->charisma = abilityRandomizer();
    this->wisdom = abilityRandomizer();
    this->intelligence = abilityRandomizer();
    initializeHitPoints();
    calculateArmor();
    calculateAttackBonus();
    calculateDamageBonus();*/

    //if (name == "godman")
    //{
    //    this->hitPoints = 1000;
    //    this->attackBonus = 5;
    //    this->damageBonus = 5;
    //}
}

//Destructor
//Character::~Character() 
//{
//    for (auto& item : equippedItems) {
//        delete item;
//    }
//}

//Accessors and Mutators
 /**
 
    Empty
 
 */


//Godman Mode
void Character::getGodMode()
{
    if (name == "godman")
    {
        this->hitPoints = 1000;
        this->attackBonus = 15;
        this->damageBonus = 15;
    }
}

void Character::attackEnemy(Character& enemy) {
    //repeat the sequence for rounds
    for (int i = 0; i < rounds; i++) {
        // Roll to hit
        int attackRoll = abilityRandomizer();
        int totalAttack = attackRoll + attackBonus;

        //Display messages
        cout << "Round #" << i + 1 << ":" << endl;
        cout << name << " is attacking " << enemy.name << endl;
        // Compare to enemy's Armor
        if (totalAttack >= enemy.armorClass) {
            /*
                Need to update with roll-dices
            */
            int damageRoll = ((rand() % 8) + 1);  // MUST CHANGE THE ROLL DICE-------
            int totalDamage = damageRoll + damageBonus;

            // Apply damage to the enemy
            enemy.takeDamage(totalDamage);
            //Message on screen
            cout << enemy.name + " has been hit for " << totalDamage << " damage!" << endl;
            string dmg = std::to_string(totalDamage) + "";
            Logger::getSingleton()->log("battle", name + " hit " + enemy.name + " for " + dmg + "");

            //Verify if the enemy's hitpoints reached 0, then we just exit
            if (enemy.getHitpoints() == 0) 
            {
                return;
            }
        }
        else {
            //Message on screen
            cout << name << " missed his attack!" << endl;
            Logger::getSingleton()->log("battle", name + " missed his attack");
        }
    }
}

//Generating a random number between 1 and 20 to determine abilities stats
//Simplified d20
int Character::abilityRandomizer() 
{
    return ((rand() % 20) + 1);
}

//Checks modifier based on the ability score
int Character::calculateAbilityModifier(int data)
{
    return (data - 10) / 2;
}

//When we initially built a new Character, we wish for them to start somewhere.
void Character::initializeHitPoints() 
{
    //See if it's an enemy, dragon or a hero
    switch (this->characterClass) {
    case CharacterType::Hero:
    case CharacterType::Bully:
    case CharacterType::Nimble:
    case CharacterType::Tank:
        // Roll a d10 and add the constitution modifier
        hitPoints = level *((rand() % 10) + 1 + constitution);
        break;

    case CharacterType::Dragon:
        hitPoints = level + (abilityRandomizer() + calculateAbilityModifier(constitution)) + 10;
        break;

    case CharacterType::Goblin:
        hitPoints = level + (abilityRandomizer() + calculateAbilityModifier(constitution));
        break;
        //If nothing matches
    default:
        hitPoints = 5;
    }
}

// Calculate hit points based on constitution modifier, d20 dice and level
void Character::calculateHitPoints() 
{
    //dice dice; --IMPLEMENT THIS LATER ON 
    
    //See if it's an enemy, dragon or a hero
    switch (this->characterClass) {
        case CharacterType::Hero:
        case CharacterType::Bully:
        case CharacterType::Nimble:
        case CharacterType::Tank:
            // Roll a d10 and add the constitution modifier
            hitPoints += (rand() % 10) + 1 + constitution;
            break;

        case CharacterType::Dragon:
            hitPoints = level + (abilityRandomizer() + calculateAbilityModifier(constitution)) + 10;
            break;

        case CharacterType::Goblin:
            hitPoints = level + (abilityRandomizer() + calculateAbilityModifier(constitution));
            break;
        //If nothing matches
        default:
            hitPoints = 21;
        }
}

// // The number of attacks per round increases by one every five levels
int Character::getAttacksPerRounds() {
    int temp = (int) ((level / 5.001) + 1);
    attackBonus++;

    //return attacks per round
    if (!(this->rounds - temp == 0) && this->rounds != 0) 
    {
        cout << "Sucess! The amount of rounds you can attack per turn has increased!" << endl;
        return temp;
    }

    return temp;
}

// Calculate armor class based on dexterity modifier 
/*
* WILL NEED TO CHANGE WHEN ADDING ARMORS AND STUFF
*/
void Character::calculateArmor()
{
    armorClass =  10 + calculateAbilityModifier(dexterity);
}

//int Character::calculateArmor(int& additional)
//{
//    return 10 + calculateAbilityModifier(dexterity) + additional;
//}


//If player removes his armor and replaces with another one?
//void Character::removeArmor(const Item& item) 
//{
//    armorClass -= item.getModifier();
//}
//
////Equip new armor
//void Character::equipArmor(const Item& item) 
//{
//    armorClass += item.getModifier();
//}


void Character::calculateAttackBonus()
{
    attackBonus = level + calculateAbilityModifier(strength) + calculateAbilityModifier(dexterity);
}

void Character::calculateDamageBonus()
{
    damageBonus = calculateAbilityModifier(strength);
}


// Method to take damage and update hit points
void Character::takeDamage(int& damage)
{
    hitPoints -= damage;
    notify();
    if (hitPoints < 0)
    {
        hitPoints = 0;  // hit points should not go below zero

        cout << name << " has fainted!" << endl;
    }
}


//Create an experience point
void Character::levelingUp(int experience) {
    experience_Points += experience;
    checkLevelUp();
}

//Check threshold to gain a level
void Character::checkLevelUp() {

    //leveling up initial
    int expThreshold = 100 * (level);
        
    while (experience_Points >= expThreshold) {
        ++level;
        experience_Points -= expThreshold;
        cout << name << " leveled up to Level " << level << "!" << endl;

        //Increase hitpoints and attack bonus and rounds per attack
        calculateHitPoints();
        rounds = getAttacksPerRounds();
        
        //Increase threshold as leveling up goes by
        expThreshold = 100 * (level);

        //Pause to admire
        _getch();
    }
}

// Method to handle armor modifiers based on armor type
void Character::applyArmorTypeModifier(item::ArmorType& armorType, int modifier) {

    switch (armorType) {
    case item::ArmorType::Light:
        //minimal impact on dexterity, increase armor class
        armorClass += modifier;
        dexterity += (modifier / 2); // Adjust dexterity slightly
        break;

    case item::ArmorType::Medium:
        //moderate impact on dexterity, increase armor class
        armorClass += 2 + modifier;
        dexterity += (modifier / 4); // Adjust dexterity slightly
        break;

    case item::ArmorType::Heavy:
        //significant impact on dexterity, high increase in armor class
        armorClass += 3 * modifier;
        dexterity -= (modifier / 2); // Decrease dexterity significantly
        break;

    default:
        armorClass += modifier;
        break;

    }
}


void Character::applyItemModifier(CharacterStat stat, int modifier)
{
    if (stat == CharacterStat::ArmorClass)
        armorClass += modifier;
    else if (stat == CharacterStat::AttackBonus)
        attackBonus += modifier;
    else if (stat == CharacterStat::Charisma)
        charisma += modifier;
    else if (stat == CharacterStat::Constitution)
        constitution += modifier;
    else if (stat == CharacterStat::DamageBonus)
        damageBonus += modifier;
    else if (stat == CharacterStat::Dexterity)
        dexterity += modifier;
    else if (stat == CharacterStat::Intelligence)
        intelligence += modifier;
    else if (stat == CharacterStat::Strength)
        strength += modifier;
    else if (stat == CharacterStat::Wisdom)
        wisdom += modifier;
}

void Character::equipItem(item::Item* item)
{
    // Check if the item is nullptr
    if (item == nullptr) 
    {
        // Optionally, you can throw an exception or print an error message
        std::cerr << "Error: Attempting to equip a null item." << std::endl;
        //Pause
        _getch();
        // Or throw an exception
        // throw std::invalid_argument("Attempting to equip a null item.");
        return; // Return early since there's nothing to equip
    }


    bool unequiping = false;
    if (getHelmet() == item) {
        helmet = nullptr;
        unequiping = true;
    }
    else if (getArmor() == item) {
        armor = nullptr;
        unequiping = true;
    }
    else if (getRing() == item) {
        ring = nullptr;
        unequiping = true;
    }
    else if (getBelt() == item) {
        belt = nullptr;
        unequiping = true;
    }
    else if (getBoots() == item) {
        boots = nullptr;
        unequiping = true;
    }
    else if (getWeapon() == item) {
        weapon = nullptr;
        unequiping = true;
    }
    else if (getShield() == item) {
        shield = nullptr;
        unequiping = true;
    }
    if (unequiping)
    {
        applyItemModifier(item->getEnhancedAbility(), -1 * item->getModifier());
        return;
    }

    unequipItem(item);

    if (item::Armor* armorPtr = dynamic_cast<item::Armor*>(item)) {
        // Determine the armor type and apply appropriate modifiers
        item::ArmorType armorType = armorPtr->getArmor(); // Assuming Armor has a method getArmorType()
        applyArmorTypeModifier(armorType, armorPtr->getModifier());
        armor = armorPtr;
        return;
    }
    else {
        if (item::Ring* ringPtr = dynamic_cast<item::Ring*>(item))
            ring = ringPtr;
        //else if (item::Armor* armorPtr = dynamic_cast<item::Armor*>(item))
        //    armor = armorPtr;
        else if (item::Boots* bootsPtr = dynamic_cast<item::Boots*>(item))
            boots = bootsPtr;
        else if (item::Helmet* helmetPtr = dynamic_cast<item::Helmet*>(item))
            helmet = helmetPtr;
        else if (item::Belt* beltPtr = dynamic_cast<item::Belt*>(item))
            belt = beltPtr;
        else if (item::Weapon* weaponPtr = dynamic_cast<item::Weapon*>(item))
            weapon = weaponPtr;
        else if (item::Shield* shieldPtr = dynamic_cast<item::Shield*>(item))
            shield = shieldPtr;
        else
            return;

        applyItemModifier(item->getEnhancedAbility(), item->getModifier());
    }
}

void Character::unequipItem(item::Item* item)
{
    const std::type_info& type = typeid(*item);

    if (type == typeid(item::Ring) && ring != nullptr)
    {
        applyItemModifier(ring->getEnhancedAbility(), -1 * ring->getModifier());
        ring = nullptr;
    }
    else if (type == typeid(item::Armor) && armor != nullptr)
    {
        applyItemModifier(armor->getEnhancedAbility(), -1 * armor->getModifier());
        armor = nullptr;
    }
    else if (type == typeid(item::Boots) && boots != nullptr)
    {
        applyItemModifier(boots->getEnhancedAbility(), -1 * boots->getModifier());
        boots = nullptr;
    }
    else if (type == typeid(item::Helmet) && helmet != nullptr)
    {
        applyItemModifier(helmet->getEnhancedAbility(), -1 * helmet->getModifier());
        helmet = nullptr;
    }
    else if (type == typeid(item::Belt) && belt != nullptr)
    {
        applyItemModifier(belt->getEnhancedAbility(), -1 * belt->getModifier());
        belt = nullptr;
    }
    else if (type == typeid(item::Weapon) && weapon != nullptr)
    {
        applyItemModifier(weapon->getEnhancedAbility(), -1 * weapon->getModifier());
        weapon = nullptr;
    }
    else if (type == typeid(item::Shield) && shield != nullptr)
    {
        applyItemModifier(shield->getEnhancedAbility(), -1 * shield->getModifier());
        shield = nullptr;
    }
}


//When the main character levels up!
//DEPRECATED AS PER PART OF THE PROJECT
void Character::increaseStats() {
    // Adjust stats based on the current level 
    this->hitPoints += level * 10;
    this->strength += level * 2;
    this->dexterity += level;
    this->constitution += level;   
}

int Character::getHitpoints()
{
    return hitPoints;
}

void Character::setHitpoints(int points) 
{
    this->hitPoints = points;
}

//Gender Selection OPTIONAL
  string Character::genderSelection() {
    char userInput;

    while (true) {
        system("cls");  // Clear console screen (Windows specific)
        cout << "=== Gender Selection ===" << endl;
        cout << "Are you a Male (M) or a Female (F)? Please enter it by pressing M or F: ";
        cin >> userInput; 

        // Process user input
        if (toupper(userInput) == 'M' ) {
             return "Male";
        }
        else if (toupper(userInput) == 'F' ) {
            return "Female";
        }
        else {
            cout << "\nNot valid, try again:";
            _getch(); //Pause
        }
    }
}


//Pause menu to see the details of the user
void Character::displayInfo() {
    //Create a table to check Character's Info
    cout << std::left << setw(20)  << std::setw(15) << name << "  Gender: " << gender << endl;
    cout << std::left << setw(20) << "Character Class:" << std::setw(15) << characterTypeToString(characterClass) << endl;
    cout << std::setw(20) << "Level:" << std::setw(15) << level << endl;
    cout << std::setw(20) << "Strength:" << std::setw(15) << strength << " (Modifier: " << calculateAbilityModifier(strength) << ")" << endl;
    cout << std::setw(20) << "Dexterity:" << std::setw(15) << dexterity << " (Modifier: " << calculateAbilityModifier(dexterity) << ")" << endl;
    cout << std::setw(20) << "Constitution:" << std::setw(15) << constitution << " (Modifier: " << calculateAbilityModifier(constitution) << ")" << endl;
    cout << std::setw(20) << "Wisdom:" << std::setw(15) << wisdom << endl;
    cout << std::setw(20) << "Charisma:" << std::setw(15) << charisma << endl;
    cout << std::setw(20) << "Intelligence:" << std::setw(15) << intelligence << endl;
    cout << std::setw(20) << "Hit Points:" << std::setw(15) << hitPoints << endl;
    cout << std::setw(20) << "Armor Class:" << std::setw(15) << armorClass << endl;
    cout << std::setw(20) << "Attack Bonus:" << std::setw(15) << attackBonus << endl;
    cout << std::setw(20) << "Damage Bonus:" << std::setw(15) << damageBonus << endl;

    if (helmet != nullptr)
        cout << std::setw(20) << "Helmet:" << std::setw(15) << helmet->toString() << endl;
    if (armor != nullptr)
        cout << std::setw(20) << "Armor:" << std::setw(15) << armor->toString() << endl;
    if (shield != nullptr)
        cout << std::setw(20) << "Shield:" << std::setw(15) << shield->toString() << endl;
    if (ring != nullptr)
        cout << std::setw(20) << "Ring:" << std::setw(15) << ring->toString() << endl;
    if (belt != nullptr)
        cout << std::setw(20) << "Belt:" << std::setw(15) << belt->toString() << endl;
    if (boots != nullptr)
        cout << std::setw(20) << "Boots:" << std::setw(15) << boots->toString() << endl;
    if (weapon != nullptr)
        cout << std::setw(20) << "Weapon:" << std::setw(15) << weapon->toString() << endl;

    //Pause
    _getch();
}


void Character::attach(CharacterObserver* observer) {
    observers_.push_back(observer);
}

void Character::detach(CharacterObserver* observer) {
    observers_.erase(std::remove(observers_.begin(), observers_.end(), observer), observers_.end());
}

void Character::notify() {
    for (CharacterObserver* observer : observers_) {
        observer->notify(this);
    }
}


