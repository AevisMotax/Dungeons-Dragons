#ifndef FIGHTER_H
#define FIGHTER_H

#include<iostream>
#include<vector>
#include "characterType.h"

using namespace std;

/**
* @brief enum class for fighter type
*/
enum class FighterType {
	Bully,
	Nimble,
	Tank
};



/**
* @brief base class for Characters
*/
class Fighter
{

public:

	/**
	* @brief Constructor for the Fighter class.
	*
	* @param type The type of the character (e.g., Hero, Dragon, Goblin).
	* @param level The level of the character.
	*/
	Fighter(CharacterType type, int level);

	/**
	* @brief Destructor for the Fighter class.
	*
	* The destructor is virtual to allow proper cleanup in derived classes.
	*/
	virtual ~Fighter() = default;

	/**
	* @brief Display information about the fighter.
	*
	* This function displays information such as character type, level, and attributes.
	*/
	virtual void displayInfo();

	CharacterType getCharacterClass() { return characterClass; } ///<Accessors
	void setCharacterClass(CharacterType recent) { characterClass = recent; } ///<Mutator of characterTyper
	int getLevel() { return level; }
	void setLevel(int more) { level = more; }; ///<Mutator of level

	int getStrength() const { return strength; }
	int getDexterity() const { return dexterity; }
	int getConstitution() const { return constitution; }
	int getWisdom() const { return wisdom; }
	int getCharisma() const { return charisma; }
	int getIntelligence() const { return intelligence; }
	int getRounds() const { return rounds; }
	string getStrategy() const { return strategy; }
	
	void setStrength(int plus) {  strength = plus; }
	void setDexterity(int plus) { dexterity = plus; }
	void setConstitution(int plus) { constitution  = plus; }
	void setWisdom(int plus) { wisdom = plus; }
	void setCharisma(int plus) { charisma = plus; }
	void setIntelligence(int plus) { intelligence = plus; }
	void setRounds(int round) { rounds = round; }
	void setStrategy(string strat) { strategy = strat; }

protected:
	//Attributes
	CharacterType characterClass; ///< indicates the type of fighter
	int level; ///< indicates level of the player
	int strength; ///< indicates its current strength (physical power)
	int dexterity; ///< indicates its current dexterity (stealth, acrobatics, avoiding attacks)
	int constitution;///<indicates its current constitution (health, hardiness and physical endurance)
	int wisdom;///< indicates current wisdom (perceptiveness and intuition)
	int charisma;///< indicates current charisma (ability of persuasion)
	int intelligence; ///< indicates current intelligence (ability to reason)

	int rounds;	///<Attacks Per Round

	string name; ///< name of the fighter
	string gender; ///< gender of the fighter (if any)
	string strategy;
};


#endif

