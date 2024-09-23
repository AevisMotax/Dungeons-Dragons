#ifndef GRID_H
#define GRID_H

#include "tile.h"
#include "source/player/character.h"
#include "../subject.h"
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

/**
* @brief Values of this type are grids, these grid make the map on which deffines the user's view and world.
*/
class Grid : public Subject {
public:
    /**\/@brief Initialize a grid with a specific height, width and set of tiles
    * @param the array of tiles that makes the grid
    */
    Grid(int width, int height, Tile tile[3072]);

    /**\/@brief Build your custom grid
    */
    static Grid create();
    /**\/@brief Set your own custom path
    */
    void makePath();
    /**\/@brief Set each tile of your grid
    */
    void setTiles();
    /**\/@brief Set a chest in your grid
    */
    void setChest(string chest, int ind) { chestList[ind] = chest; }
    /**\/@brief Set an npc in your grid
    */
    /**\/@brief Set an npc in your grid
    */
    void setNpc(string npc, int ind) { npcList[ind] = npc; }
    /**\/@brief Save your grid
    * @param the name of the grid
    */
    string getChest(int ind) { return chestList[ind]; }
    /**\/@brief Set an npc in your grid
    */
    string getNpc(int ind) { return npcList[ind]; }
    /**\/@brief Set an npc in your grid
    */
    void save(string name);
    /**\/@brief Load a previously saved grid
    * @param the name of the grid
    */

    static void edit();

    /** 
        \brief gives the ability to edit a previously done map
        @param the name of the file
    */
    static void editMap(string fname);

    /** \brief load the grid into the screen 
        @param the name of the grid*/
    static Grid load(string name);

    /**\/@brief Initialize the grid with a custom size
    * @param the width of the grid
    * @param the height of the grid
    */
    Grid(int width, int height);

    /**\/@brief Initialize the grid with a random size*/
    Grid();

    /**\/@brief Make a path from start to end.This ensures that there is a path for the user
      *  
    */
    void generatePath();

    /**\/@brief This will add outcrops to the map in the shape of an r
        *@param ind is the starting tile of the path*/
    void outPath(int ind);

    /**\/@brief Fill everything other than the path.*/
    void fillMap();

    /**\/@brief Return the height of the grid*/
    int getHeight();

    /**\/@brief Return the width of the grid*/
    int getWidth();

    /**\/@brief Get a specific tile, they are order left to right and up to down
    *e.g
    *| 1 | 2 | 3 |
    *| 4 | 5 | 6 |
    *| 7 | 8 | 9 |
    *@param the ind is the index of the tile in the array.*/
    Tile& getTiles(int ind);

    /**\/@brief Move an index one row up the grid
    *@param the index is the number of the tile to be moved*/
    int moveUp(int index);

    /**\/@brief Move an index one row down the grid
    *@param the index is the number of the tile to be moved*/
    int moveDown(int index);

    /**\/@brief Move an index one column to the left on the grid
    *@param the index is the number of the tile to be moved*/
    int moveLeft(int index);

    /**\/@brief Move an index one column to the right on the grid
    *@param the index is the number of the tile to be moved*/
    int moveRight(int index);

    /**\/@brief Check if a battle is being initiated
    *@param the playerInd is the player's current tile*/
    int checkBattle(int playerInd);

    /**\/@brief Make a string representing the grid.*/
    string toString();

    /**\/@brief Print the grid. This prints the map which the user interacts with*/
    void draw();

private:
    /**\/@brief Set the odds of the direction the path will take, for intance how often will the path move right*/
    void setPathOdds();

    int width;///<Width of grid
    int height;///<Height of grid
    int numTiles;///<Number of tiles in the grid
    int numEnemies;///<Number of enemies
    Character npcs[50];///<Npc characters
    int npcLocations[50];

    double leftPathOdds;///<Odds that the path moves Left
    double rightPathOdds;///<Odds that the path moves Right
    double upPathOdds;///<Odds that the path moves Up
    double downPathOdds;///<Odds that the path moves down

    Tile tiles[3072];///<Array of tiles
    double mountains;///<Quantity of mountains
    double water;///<Quantity of water

    string npcList[100];
    string chestList[100];
};

#endif //GRID_H
