#ifndef CHARACTER_H
#define CHARACTER_H

#include "characterObserver.h"
#include "fighter.h"
#include "source/globalFunctions.h"
#include "characterType.h"
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
/**
 * @brief The main player and enemies character class.
 */
class Character : public Fighter
{

public:
    /**
     * @brief Default constructor for Character class.
     */
    Character(string name);
    Character();

    /**
     * @brief Constructor for Character class with specified type, name, and level.
     * 
     * @param type The type of the character.
     * @param name The name of the character.
     * @param level The level of the character.
     */
    Character(const CharacterType& type, const string& name, int level);

    /**
     * @brief Constructor for Character class with specified type, gender, name, and level.
     * 
     * @param type The type of the character.
     * @param gender The gender of the character.
     * @param name The name of the character.
     * @param level The level of the character.
     */
    Character(const CharacterType& type, const std::string& gender, const std::string& name, int level);

    void attach(CharacterObserver* observer);
    void detach(CharacterObserver* observer);
    void notify();


    /**
    *@method Easter Egg mode
    */
    void getGodMode();
    /**
     * @brief Dealing damages to the enemy.
     * 
     * @param enemy The enemy character to attack.
     */
    void attackEnemy(Character& enemy);

    /**
     * @brief Optional gender selection for the character.
     * 
     * @return The selected gender.
     */
    string genderSelection();

    /**
     * @brief Display information about the character.
     */
    void displayInfo() override;

    /**
     * @brief Randomizes ability scores for the character.
     * 
     * @return The randomized ability score.
     */
    int abilityRandomizer();

    /**
     * @brief modifies a player's ability given score
     * 
     * @return The modified stat
     */
    int calculateAbilityModifier(int data);


    /**
    * @brief Calculates the initial hit points for the character.
    */
    void initializeHitPoints();


    /**
     * @brief Calculates the hit points for the character.
     */
    void calculateHitPoints();

    /**
     * @brief Calculates the armor class for the character.
     * 
     * Note: This function may need modification when adding different armor types.
     */
    void calculateArmor(); /* WILL NEED TO CHANGE WHEN ADDING ARMORS AND STUFF*/
    //int calculateArmor(int& additional);

    /**
    * @brief handle armor modifiers
    *
    */
    void applyArmorTypeModifier(item::ArmorType& type, int modifier);
    //If player removes his armor and replaces with another one?
    //void removeArmor(const Item& oldArmor);

     /**
     * @brief Equips a new item to the character.
     * 
     * @param item The item to be equipped.
     */
    void equipItem(item::Item* item);

    /**
     * @brief Unequips an item from the character.
     * 
     * @param item The item to be unequipped.
     */
    void unequipItem(item::Item* item);

    /**
     * @brief Adding attack bonus for the character when attacking an enemy.
     */
    void calculateAttackBonus();

    /**
     * @brief Adding damage bonus for the character when hitting an enemy.
     */
    void calculateDamageBonus();

    /**
     * @brief Inflicts damage on the character.
     * 
     * @param damage The amount of damage to be inflicted.
     */
    void takeDamage(int& damage);

    /**
     * @brief If the character acquired enough experience points to level up.
     */
    void checkLevelUp();

    /**
     * @brief Levels up the character and stats based on experience points.
     * 
     * @param experience The experience points earned.
     */
    void levelingUp(int experience);
    void increaseStats();

    /**
     * @brief Gets the current hitpoints of the character.
     * 
     * @return The current hitpoints.
     */
    int getHitpoints();

    /**
    * @brief Sets the current hitpoints of the character.
    *
    * @return The current hitpoints.
    */
    void setHitpoints(int points);


    /**
     * @brief Gets the current name of the character.
     *
     * @return The current name.
     */
    string getName() { return name; }
    string getGender() const { return gender; }

    /**
    * @brief Sets the current name of the character.
    *
    */
    void setName(std::string lname) { name = lname; }
    void setGender(std::string lgender) { gender = lgender; }

    /**
     * @brief Calculates increase in attacks per rounds as leveling up.
     *
     * @return The current name.
     */
    int getAttacksPerRounds();

    // Get functions for Attributes calculated according to the character's main attributes
    int getArmorClass() const { return armorClass; }
    int getAttackBonus() const { return attackBonus; }
    int getDamageBonus() const { return damageBonus; }
    int getExp_Points() const { return experience_Points;  }

    // Get functions for Attributes calculated according to the character's main attributes
    void setArmorClass(int armor) { armorClass = armor; }
    void setAttackBonus(int bonus) {  attackBonus = bonus; }
    void setDamageBonus(int damage) {  damageBonus = damage; }
    void setPoints(int points) { experience_Points = points; }

    // Get functions for equipped items
    item::Helmet* getHelmet() const { return helmet; }
    item::Armor* getArmor() const { return armor; }
    item::Shield* getShield() const { return shield; }
    item::Ring* getRing() const { return ring; }
    item::Boots* getBoots() const { return boots; }
    item::Belt* getBelt() const { return belt; }
    item::Weapon* getWeapon() const { return weapon; }

private:
    //Character's details
	std::string name; ///< name of character
	std::string gender; ///< gender of character


    ///<Experience Points and stuff
    int experience_Points; 

    ///<Points earned throughout the game?
    int total_Points;

    //Attributes calculated according to the character's main attributes

    ///< the amount of health the character has left
    int hitPoints; 
    ///< Armor decides how much attack is required to hit an enemy
    int armorClass;
    ///< Attack is used to pierce an enemies' armor
    int attackBonus;

    ///< Damage is the amiunt of hitpoints taken form an enemy
    int damageBonus;

    item::Helmet* helmet = nullptr; ///< Pointer to the equipped helmet.
    item::Armor* armor = nullptr;   ///< Pointer to the equipped armor.
    item::Shield* shield = nullptr; ///< Pointer to the equipped shield.
    item::Ring* ring = nullptr;     ///< Pointer to the equipped ring.
    item::Boots* boots = nullptr;   ///< Pointer to the equipped boots.
    item::Belt* belt = nullptr;     ///< Pointer to the equipped belt.
    item::Weapon* weapon = nullptr; ///< Pointer to the equipped weapon.

    std::vector<CharacterObserver*> observers_; ///< Observers of the character

    /**
     * @brief When wearing an Item, applies a modifier to a specific character stat.
     * 
     * @param stat The character stat to be modified.
     * @param modifier The modifier to be applied.
     */
    void applyItemModifier(CharacterStat stat, int modifier);
};



#endif // !PART1_H
