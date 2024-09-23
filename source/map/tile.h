
#ifndef TILE_H
#define TILE_H

#include <iostream>
#include "source/globalFunctions.h"
using namespace std;

/**.
* @brief Values of this type are tiles of the map grid. The deffined during the map generator process
*/
class Tile {
    public:
        /**\/@brief Intializes a tile by deciding it's type 
        *@param The type is the type of the tile like M for mountain*/
        Tile(char type);
        /**\/@brief Intialize the tile by setting it's type to empty */
        Tile();

        Tile(const Tile &tile);

        /**\/@brief Get the type of the tile 
        * \return The type e.g M for mountain*/
        char getType();
        /**\/@brief See if the player is on the tile 
        * \return Whether or not the player is on the tile*/
        bool getIsPlayer();
        /**\/@brief See if an enemy is on the tile 
        * \return Whether or not an enemy is on the tile*/
        bool getIsEnemy();
        /**\/@brief See if a tile contains a chest
        * \return Whether or not a chest is on the tile*/
        bool getIsChest();
        /**\/@brief Set the tile to a player tile
        * \return If tile has been switched*/
        bool switchPlayer();
        /**\/@brief Set the tile to an enemy tile
        * \return If tile has been switched*/
        bool switchEnemy();
        /**\/@brief Set the tile to a chest tile
        * \return If tile has been switched*/
        bool switchChest();
        /**\/@brief See if the tile kills the player or lets him win
        * \return If the player was killed*/
        bool isEnding();
        
        void setType(char type);

        /**\/@brief Return the tiles output.
        * \return The type e.g M for mountain*/
        string toString();

        /**\/@brief Output the tile*/
        ColoredText draw();

    private:
       
        char type;///< The type of the tile
        bool isPlayer; ///<  Is the player on the tile
        bool isEnemy;///<  Is an enemy on the tile
        bool isChest;///<  Is a chest on the tile
};

#endif // TILE_H
