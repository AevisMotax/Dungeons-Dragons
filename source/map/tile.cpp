//This is the implementation file: tile.cpp of the class Tile.
//The interface for the class Tile is in the header file tile.h.
#include <iostream>
#include <cctype>
#include <cstdlib>
using namespace std;
#include "Tile.h"
#include "source/globalFunctions.h"

Tile::Tile(char type)
{
    this->type = type;
    isPlayer = false;
    isEnemy = false;
    isChest = false;
}

Tile::Tile()
{
    this->type = char(0);
    isPlayer = false;
    isEnemy = false;
    isChest = false;
}

Tile::Tile(const Tile &tile)
{
    this->type = tile.type;
    isPlayer = tile.isPlayer;
    isEnemy = tile.isEnemy;
    isChest = tile.isChest;
}

char Tile::getType()
{
    return type;
}

bool Tile::getIsPlayer()
{
    return isPlayer;
}

bool Tile::switchPlayer()
{
    //Check if the player can move on the tile and return true
    if (!isPlayer && type != 'M' && type != '~')
    {
        //Debug: cout << "switching tile to true" << endl;
        isPlayer = true;
        return true;
    }
    //The player can't move on the tile so return false
    else
    {
        //Debug: cout << "switching tile to false" << endl;
        isPlayer = false;
        return false;
    }
}

bool Tile::getIsEnemy()
{
    return isEnemy;
}

bool Tile::switchEnemy()
{
    //Check if an enemy can be on the tile
    if (!isPlayer && !isEnemy && type != 'M' && type != '~')
    {
        isEnemy = true;
        return true;
    }
    //The enemy can't be there so return false
    else
    {
        isEnemy = false;
        return false;
    }
}

bool Tile::getIsChest()
{
    return isChest;
}

bool Tile::switchChest()
{
    isChest = !isChest;
    return true;
}

bool Tile::isEnding()
{
    if(type == 'X')
    {
        cout << "You've made it!";
        return true;
    }
    return false;
}

void Tile::setType(char type)
{
    this->type = type;
}

string Tile::toString()
{
    //Output the type of this tile
    if (isPlayer)
    {
        return "O";
    }

    if (isEnemy)
    {
        return "V";
    }

    if (isChest)
    {
        return "H";
    }

    std::string out = "";
    out += type;
    return out;
}

ColoredText Tile::draw()
{
    ColoredText text;
    if (getType() == ' ') {
        text.bgColor = BG_GREEN;
        text.text = " ";
    }
    else if (getType() == 'M') {
        text.bgColor = BG_BRIGHT_BLACK;
        text.color = WHITE;
        text.text = "M";
    }
    else if (getType() == '~') {
        text.bgColor = BG_BLUE;
        text.color = CYAN;
        text.text = "~";
    }
    else if (type == 'X')
    {
        text.bgColor = BG_GREEN;
        text.color = BLACK;
        text.text = "X";
    }

    //Output the type of this tile
    if (isPlayer)
    {
        text.color = BRIGHT_YELLOW;
        text.text = "O";
    }

    else if (isEnemy)
    {
        text.color = RED;
        text.text = "V";
    }

    else if (isChest)
    {
        text.color = YELLOW;
        text.text = "H";
    }
    else if (getType() == '-') {
        text.color = YELLOW;
        text.text = "-";
    }
    else if (getType() == '*') {
        text.bgColor = RED;
        text.color = BLACK;
        text.text = "*";
    }

    return text;
}