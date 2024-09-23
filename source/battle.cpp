//This is the implementation file: battle.cpp of the class battle.
//The interface for the class battle is in the header file battle.h.
#include "battle.h"
#include "player/character.h"
#include <iostream>
Battle::Battle(Character& player, Character& enemy)
{
	this->player = &player;
	this->enemy = &enemy;
}
string Battle::toString()
{
	return "Press Enter to attack";
}
bool Battle::nextTurn()
{
	player->attackEnemy(*enemy);
	enemy->attackEnemy(*player);
	cout << "Press Enter To Continue.";
	cin.get();

	if (enemy->getHitpoints() <= 0)
		player->levelingUp(188);
		return false;
	if (player->getHitpoints() <= 0)
		return false;
	return true;
}
void Battle::processAction()
{

}