#include <source/npc/npcController.h>
#include "source/player/humanCharacterStrategy.h"
#include "source/npc/attackNpcStrategy.h"
#include <source/itemContainer.h>
/**
* The classes that implement a HumanCharacterStrategy should inherit this.
* The playerController class will use this to move and attack
*/

/**
* Method whose implementation varies depending on the strategy adopted.
*/
bool HumanCharacterStrategy::execute(char in, NpcController* npcs, int& playerInd, Grid* grid, Character& character)
{
    int lastInd;
    int tempInd = -1;
    string type = "";
    if (character.getWeapon() != nullptr)
    {
        type = character.getWeapon()->getWeaponType();
    }
    //if using gappling hook weapon
    if (type == "GrapplingHook")
    {
        if (in == 'a' || in == 'A')
        {
            //Player's new location
            tempInd = grid->moveLeft(playerInd);
            lastInd = -1;
            while (lastInd != tempInd && grid->getTiles(tempInd).getType() != 'M' && !grid->getTiles(tempInd).getIsEnemy())
            {
                lastInd = tempInd;
                tempInd = grid->moveLeft(tempInd);
                char tempType = grid->getTiles(tempInd).getType();
                grid->getTiles(tempInd).setType('-');
                system("cls");
                grid->draw();
                grid->getTiles(tempInd).setType(tempType);
            }
            tempInd = grid->moveRight(tempInd);
        }
        //Same as moving left but for moving right
        else if (in == 'd' || in == 'D')
        {
            tempInd = grid->moveRight(playerInd);
            lastInd = -1;
            while (lastInd != tempInd && grid->getTiles(tempInd).getType() != 'M' && !grid->getTiles(tempInd).getIsEnemy())
            {
                lastInd = tempInd;
                tempInd = grid->moveRight(tempInd);
                char tempType = grid->getTiles(tempInd).getType();
                grid->getTiles(tempInd).setType('-');
                system("cls");
                grid->draw();
                grid->getTiles(tempInd).setType(tempType);
            }
            tempInd = grid->moveLeft(tempInd);
        }
        //Same as moving left but for moving up
        else if (in == 'w' || in == 'W')
        {
            tempInd = grid->moveUp(playerInd);
            lastInd = -1;
            while (lastInd != tempInd && grid->getTiles(tempInd).getType() != 'M' && !grid->getTiles(tempInd).getIsEnemy())
            {
                lastInd = tempInd;
                tempInd = grid->moveUp(tempInd);
                char tempType = grid->getTiles(tempInd).getType();
                grid->getTiles(tempInd).setType('-');
                system("cls");
                grid->draw();
                grid->getTiles(tempInd).setType(tempType);
            }
            tempInd = grid->moveDown(tempInd);
        }
        //Same as moving left but for moving down
        else if (in == 's' || in == 'S')
        {
            tempInd = grid->moveDown(playerInd);
            lastInd = -1;
            while (lastInd != tempInd && grid->getTiles(tempInd).getType() != 'M' && !grid->getTiles(tempInd).getIsEnemy())
            {
                lastInd = tempInd;
                tempInd = grid->moveDown(tempInd);
                char tempType = grid->getTiles(tempInd).getType();
                grid->getTiles(tempInd).setType('-');
                system("cls");
                grid->draw();
                grid->getTiles(tempInd).setType(tempType);
            }
            tempInd = grid->moveUp(tempInd);
        }

        if (tempInd != -1)
        {
            Tile* currentTile = &(grid->getTiles(tempInd));
            if (currentTile->getIsEnemy())
            {
                int currentNpc = 0;
                NpcController* enemy = new NpcController();
                while (npcs[currentNpc].getNpcInd() != -1)
                {
                    if (npcs[currentNpc].getNpcInd() == tempInd) {
                        enemy = &npcs[currentNpc];
                        enemy->setStrategy(&AttackNpcStrategy::getSingleton());
                        break;
                    }
                    currentNpc++;
                }

                character.attackEnemy(*enemy->getCharacter());
                cin.get();
                if (enemy->getCharacter()->getHitpoints() < 1)
                {
                    character.levelingUp(188); //leveling up
                    enemy->setNpcInd(-2);
                    currentTile->switchEnemy();
                }
            }
            else if (tempInd != playerInd)
            {
                if (grid->getTiles(tempInd).getType() == '~')
                {
                    int dmg = 1;
                    character.takeDamage(dmg);
                    cout << "Don't go in the water!";
                    cin.get();
                }
                //Switch the tile to a player tile and check if it is possible
                else if (currentTile->switchPlayer())
                {
                    //Get the old tile and remove the player from that tile
                    Tile* previousTile = &(grid->getTiles(playerInd));
                    previousTile->switchPlayer();
                    //Update player's location
                    playerInd = tempInd;
                }
            }
            return true;
        }
    }
    else if (type == "Bow")
    {
        if (in == 'a' || in == 'A')
        {
            //Player's new location
            tempInd = grid->moveLeft(playerInd);
            lastInd = -1;
            while (lastInd != tempInd && grid->getTiles(tempInd).getType() != 'M' && !grid->getTiles(tempInd).getIsEnemy())
            {
                lastInd = tempInd;
                tempInd = grid->moveLeft(tempInd);
                char tempType = grid->getTiles(tempInd).getType();
                grid->getTiles(tempInd).setType('-');
                system("cls");
                grid->draw();
                grid->getTiles(tempInd).setType(tempType);
            }
        }
        //Same as moving left but for moving right
        else if (in == 'd' || in == 'D')
        {
            tempInd = grid->moveRight(playerInd);
            lastInd = -1;
            while (lastInd != tempInd && grid->getTiles(tempInd).getType() != 'M' && !grid->getTiles(tempInd).getIsEnemy())
            {
                lastInd = tempInd;
                tempInd = grid->moveRight(tempInd);
                char tempType = grid->getTiles(tempInd).getType();
                grid->getTiles(tempInd).setType('-');
                system("cls");
                grid->draw();
                grid->getTiles(tempInd).setType(tempType);
            }
        }
        //Same as moving left but for moving up
        else if (in == 'w' || in == 'W')
        {
            tempInd = grid->moveUp(playerInd);
            lastInd = -1;
            while (lastInd != tempInd && grid->getTiles(tempInd).getType() != 'M' && !grid->getTiles(tempInd).getIsEnemy())
            {
                lastInd = tempInd;
                tempInd = grid->moveUp(tempInd);
                char tempType = grid->getTiles(tempInd).getType();
                grid->getTiles(tempInd).setType('-');
                system("cls");
                grid->draw();
                grid->getTiles(tempInd).setType(tempType);
            }
        }
        //Same as moving left but for moving down
        else if (in == 's' || in == 'S')
        {
            tempInd = grid->moveDown(playerInd);
            lastInd = -1;
            while (lastInd != tempInd && grid->getTiles(tempInd).getType() != 'M' && !grid->getTiles(tempInd).getIsEnemy())
            {
                lastInd = tempInd;
                tempInd = grid->moveDown(tempInd);
                char tempType = grid->getTiles(tempInd).getType();
                grid->getTiles(tempInd).setType('-');
                system("cls");
                grid->draw();
                grid->getTiles(tempInd).setType(tempType);
            }
        }

        if (tempInd != -1)
        {
            Tile* currentTile = &(grid->getTiles(tempInd));
            if (currentTile->getIsEnemy())
            {
                int currentNpc = 0;
                NpcController* enemy = new NpcController();
                while (npcs[currentNpc].getNpcInd() != -1)
                {
                    if (npcs[currentNpc].getNpcInd() == tempInd) {
                        enemy = &npcs[currentNpc];
                        enemy->setStrategy(&AttackNpcStrategy::getSingleton());
                        break;
                    }
                    currentNpc++;
                }

                character.attackEnemy(*enemy->getCharacter());
                cin.get();
                if (enemy->getCharacter()->getHitpoints() < 1)
                {
                    character.levelingUp(188); //leveling up
                    enemy->setNpcInd(-2);
                    currentTile->switchEnemy();
                }
            }
            return true;
        }
    }

    //If the user is pressing the left arrow move left
    if (in == '%')
    {
        //Player's new location
        tempInd = grid->moveLeft(playerInd);
    }
    //Same as moving left but for moving right
    else if (in == '\'')
    {
        tempInd = grid->moveRight(playerInd);
    }
    //Same as moving left but for moving up
    else if (in == '&')
    {
        tempInd = grid->moveUp(playerInd);
    }
    //Same as moving left but for moving down
    else if (in == '(')
    {
        tempInd = grid->moveDown(playerInd);
    }
    //Check if the user is at the border
    if (tempInd != -1)
    {
        Tile* currentTile = &(grid->getTiles(tempInd));
        if (currentTile->getIsEnemy())
        {
            int currentNpc = 0;
            NpcController* enemy = new NpcController();
            while (npcs[currentNpc].getNpcInd() != -1)
            {
                if (npcs[currentNpc].getNpcInd() == tempInd) {
                    enemy = &npcs[currentNpc];
                    enemy->setStrategy(&AttackNpcStrategy::getSingleton());
                    break;
                }
                currentNpc++;
            }

            character.attackEnemy(*enemy->getCharacter());
            cin.get();
            if (enemy->getCharacter()->getHitpoints() < 1)
            {
                character.levelingUp(188); //leveling up
                enemy->setNpcInd(-2);
                currentTile->switchEnemy();
                ItemContainer::insertRandomItem();
            }
        }
        else if (tempInd != playerInd)
        {
            if (grid->getTiles(tempInd).getType() == '~')
            {
                int dmg = 1;
                character.takeDamage(dmg);
                cout << "Don't go in the water!";
                cin.get();
            }
            //Switch the tile to a player tile and check if it is possible
            else if (currentTile->switchPlayer())
            {
                //Get the old tile and remove the player from that tile
                Tile* previousTile = &(grid->getTiles(playerInd));
                previousTile->switchPlayer();
                //Update player's location
                playerInd = tempInd;
            }
        }
        return true;
    }
    else
        return false;
}
