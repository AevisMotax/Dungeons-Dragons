#include <map>
#include "characterStat.h"

std::map<CharacterStat, std::string> characterStatToString = {
    { CharacterStat::Unknown, "unknown" },
    { CharacterStat::ArmorClass, "armor class" },
    { CharacterStat::AttackBonus, "attack bonus" },
    { CharacterStat::Charisma, "charisma" },
    { CharacterStat::Constitution, "constitution" },
    { CharacterStat::DamageBonus, "damage bonus" },
    { CharacterStat::Dexterity, "dexterity" },
    { CharacterStat::Intelligence, "intelligence" },
    { CharacterStat::Strength, "strength" },
    { CharacterStat::Wisdom, "wisdom" }
};

std::string getCharacterStatString(CharacterStat stat)
{
    return characterStatToString[stat];
}
