#include "item.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

namespace item {
    /**
     * \brief Implementation of the default Item constructor.
     * 
     * This constructor sets the default values of the Item attributes.
     * It sets the enhanced ability to Unknown and 
     * assigns a random integer between 1 and 5 inclusively as the modifier value.
     */
    Item::Item()
    {
        name = "nullItem123";
        modifier = rand() % 3 + 1;
        enhancedAbility = CharacterStat::Unknown;
    }

    Item::Item(int mod, CharacterStat stat, string name)
    {
        modifier = mod;
        enhancedAbility = stat;
        this->name = name;
    }

    CharacterStat Item::getEnhancedAbility() const
    {
        return enhancedAbility;
    }

    int Item::getModifier() const
    {
        return modifier;
    }

    void Item::setName(string name)
    {
        this->name = name;
    }
}