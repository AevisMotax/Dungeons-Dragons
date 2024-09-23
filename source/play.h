/**
* @brief Start and manage the game
*/
#ifndef PLAY_H
#define PLAY_H

#include "source/player/CharacterBuilder.h"
#include "source/player/Customizable/CharacterIO.h"
#include "npc/NpcController.h"
#include "battle.h"
#include "campaign.h"
#include <iostream>
#include <iomanip>
#include <iostream>
#include <windows.h>


class Play
{
private:
	/**\/@brief Create the character that will be played for this game
	*/
	static Character createCharacter();

	/**\/@brief Initiate a battle for the player to play in
	*@param The player character in the battle
	*/
	static void battle(Character* character, Character* enemy);

	/**\/@brief Equip the character with an item and view item bag
	*@param The player character to equip the item
	*/
	static void itemSelect(Character* character);

	static NpcController* initializeEnemies(Grid& grid);

	static item::Item** initializeChests(Grid& grid);



public:
	/**\/@brief Start and manage the campaign played
	*@param The campaign that will be played
	*/
	static void play(Campaign campaign);
};
#endif //PLAY_H

