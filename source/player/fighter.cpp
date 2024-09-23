#include "fighter.h"
#include <iostream>
#include <iomanip>

/**
* @brief Constructor of the Fighter class 
* 
* @param type The type of the character (e.g., Hero, Dragon, Goblin).
* @param level The level of the character.
*/  
Fighter::Fighter(CharacterType type, int level):characterClass(type), level(level) {
    this->strength = 0;
    this->constitution = 0;
    this->intelligence = 0;
    this->dexterity = 0;
    this->charisma = 0;
    this->wisdom = 0;
}

/**
 * @brief Display information about the fighter.
 *
 * Pause menu to see the details of the user
 */
void Fighter::displayInfo() {
    //Create a table to check Character's Info
    cout << std::left << setw(20) << std::setw(15) << name << "  Gender: " << gender << endl;
    cout << std::setw(20) << "Level:" << std::setw(15) << level << endl;
    cout << std::setw(20) << "Strength:" << std::setw(15) << strength  << endl;
    cout << std::setw(20) << "Dexterity:" << std::setw(15) << dexterity <<  endl;
    cout << std::setw(20) << "Constitution:" << std::setw(15) << constitution << endl;
    cout << std::setw(20) << "Intelligence:" << std::setw(15) << intelligence << endl;
    cout << std::setw(20) << "Wisdom:" << std::setw(15) << wisdom << endl;
    cout << std::setw(20) << "Charisma:" << std::setw(15) << charisma << endl;
}