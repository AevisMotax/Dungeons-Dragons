#pragma once
#include <string>
/**
 * \brief Enum describing the various types of character statistics.
 */
enum class CharacterStat {
    Unknown = -1,
    ArmorClass,
    AttackBonus,
    Charisma,
    Constitution,
    DamageBonus,
    Dexterity,
    Intelligence,
    Strength,
    Wisdom
};

/**
 * \brief Utility function to get a string with the name of a character statistic.
 * 
 * \return Name description of a character statistic.
 */
std::string getCharacterStatString(CharacterStat stat);




