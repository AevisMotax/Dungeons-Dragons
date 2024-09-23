#ifndef CHARACTERTYPE_H
#define CHARACTERTYPE_H

#include<iostream>
#include<vector>

/**
 * @enum CharacterType
 * @brief Enumeration representing different character types.
 */
enum class CharacterType {
    Unknown,
    Bully,
    Nimble,
    Tank,
    Dragon,
    Goblin,
    Hero
};

/** 
* @brief Vector to store additional information corresponding to each CharacterType 
*/
inline std::vector<std::string> characterTypeInfo = {
    "Hero: A heroic character.",
    "Bully: A character with brute strength.",
    "Nimble: A character with high dexterity.",
    "Tank: A character with high constitution.",
    "Dragon: A fearsome dragon enemy.",
    "Goblin: A mischievous goblin enemy."
};


#endif // CHARACTERTYPE_H