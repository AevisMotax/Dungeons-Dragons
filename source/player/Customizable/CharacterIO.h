#ifndef CHARACTERIO_H
#define CHARACTERIO_H

#define _HAS_STD_BYTE 0
#include "source/globalFunctions.h"
#include "../characterType.h"
#include "../character.h"
#include "../characterStat.h"
#include "../Fighter.h"
#include "source/dice.h"
#include "../../Dependency/json.hpp"

#include <iostream>
#include <fstream>
#include <windows.h>
#include <cstdlib>
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>
#include <conio.h>

/** 
* @file A character generator-- allows people to load character files and much more
* @brief Character Generator class
*
*/
class CharacterIO {

public:
	/// <summary>
	/// Constructors & Destructors
	/// </summary>
	CharacterIO();
	~CharacterIO();
	//CharacterIO(const std::vector<std::string>& filenames, const std::vector<Character>& allCharacters, const std::vector<Character>& allNPCs, const std::vector<std::string>& fieldsToSkip);

	///**\brief editor menu for characters */
	//void editorMenu() const;

	/**\brief show all files fpr CHaracters */
	void showAllCharacterFiles();

	/**\display Character Selection Screen */
	void displayCharacterStatsSelection(nlohmann::json& data, int selection);

	///**\brief ablwe to create new NPCs */
	//Character createNPCs();
	///**\brief ablwe to create new protagonist */
	//Character createMainCharacter();

	/**\brief load the saved file for new characters*/
	Character* loadCharacterFromSavedFiles(const std::string& name);

	/**\brief load the saved file for new NPC*/
	//std::vector<Character> loadNPCFromSavedFiles();

	/**\brief save characters to alrready made file*/
	void saveCharacter(const std::string& name, Character* fighter);

	/**\brief save newly made characters to directories */
	//void saveCreation(std::string name, Fighter* fighter);

	/**\brief add Character */
	//void addCharacter();

	/**\brief edit Character */
	void editCharacter(const std::string name);

	/**\brief change stats */
	//void changeStat(Character* character, CharacterStat s);
	void changeStat(nlohmann::json& data, const std::string& field);

	/**\brief remove a character file */
	void deleteCharacterFromFolder(std::string name);

	///**\brief remove character from the current vector */
	//void removeCharacter();

	/**\brief show if filename is empty, then we automatically musty create a new character */
	bool isExistFile();

private:
	std::vector<std::string> filenames; ///<All FileNames
	std::vector<std::string> attributes; ///<All attributes corresponding to a specific character
	//std::vector<Character> allCharacters; ///<Characters
	//std::vector<Character> allNPCs; ///<NPCS
	//bool isPlayer; ///<Determine if it's for the main player or not
	
	/** @brief List of fields that should not be modified */
	std::vector<std::string> fieldsToSkip = { "hitpoints", "level" };
};


#endif