#include "play.h"
//This is the driver of the program
//It registers user inputs and updates the map, player and enemies given the inputs.
//It is also responsible for updating the screen every couple of seconds with a redraw of the map or battle.
#include "player/concreteCharacterObserver.h"
#include "player/Character.h"
#include "FighterType.h"
#include "map/gridController.h"
#include "map/GridObserver.h"
#include "map/playerController.h"
#include "map/tile.h"
#include "map/grid.h"
#include "source/CharacterDirector.h"
#include "source/player/Customizable/CharacterIO.h"
#include "source/npc/NpcController.h"
#include "source/npc/NpcStrategy.h"
#include "source/npc/AttackNpcStrategy.h"
#include "source/npc/FriendlyNpcStrategy.h"
#include "source/logger/loggerObserver.h"
#include "dice.h"
#include "itemContainer.h"
#include "battle.h"
#include <iostream>
#include <iomanip>
#include <windows.h>
#include "items/itemIO.h"
#include "npc/defensiveNpcStrategy.h"

using namespace std;

////A function which puts the player in a battle with a randomly generated enemy.
//void Play::battle(Character* character, Character* enemy)
//{
//    system("cls");
//    Battle battle = Battle(*character, *enemy);
//    while (battle.nextTurn())
//    {
//        system("cls");
//    }
//}

//Function that allow the selection of items
void Play::itemSelect(Character* character)
{
    system("cls");
    cout << ItemContainer::toString(*character);
    cout << "Press the number of the piece you want to equip (-1 to cancel): ";

    int num;
    // Input validation
    while (!(cin >> num)) {
        cin.clear();  // Clear the fail state
        cin.ignore(256, '\n');  // Ignore invalid input
        cout << "Invalid input. Please enter a valid number: ";
    }

    if (num >= 0)
    {
        character->equipItem(ItemContainer::getItem(num));
    }
}

NpcController* Play::initializeEnemies(Grid &grid)
{
    CharacterIO charIO;
    int numNpcs = 0;
    AttackNpcStrategy attackStrategy = AttackNpcStrategy(&grid.getTiles(0), grid.getWidth(), grid.getHeight());
    FriendlyNpcStrategy friendlyStrategy = FriendlyNpcStrategy(grid.getWidth(), grid.getHeight(), "");
    DefensiveNpcStrategy defensiveStrategy = DefensiveNpcStrategy(grid.getWidth(), grid.getHeight());

    NpcController* npcs = new NpcController[100];

    //New controllers, though some mainly just to build characters
    PlayerController p1 = PlayerController(grid);

    for (int i = 0; i < 3072; i++)
    {
        if (grid.getTiles(i).getIsEnemy())
        {
            npcs[numNpcs] = NpcController(i, grid, *charIO.loadCharacterFromSavedFiles(grid.getNpc(numNpcs)));
            if (npcs[numNpcs].getCharacter()->getStrategy() == "aggresive")
                npcs[numNpcs].setStrategy(&AttackNpcStrategy::getSingleton());
            else if (npcs[numNpcs].getCharacter()->getStrategy() == "defensive")
                npcs[numNpcs].setStrategy(&DefensiveNpcStrategy::getSingleton());
            else
                npcs[numNpcs].setStrategy(new FriendlyNpcStrategy(npcs[numNpcs].getCharacter()->getStrategy()));
            numNpcs++;
        }
    }
    return npcs;
}

item::Item** Play::initializeChests(Grid & grid)
{
    int numChests = 0;
    item::Item* endItem = new item::Armor();
    item::Item** chests = new item::Item*[100];
    for (int i = 0; i < 100; i++)
        chests[i] = endItem;

    //New controllers, though some mainly just to build characters
    PlayerController p1 = PlayerController(grid);

    for (int i = 0; i < 3072; i++)
    {
        if (grid.getTiles(i).getIsChest())
        {
            item::Item *item = ItemIO::loadItem(grid.getChest(numChests));
            chests[numChests] = item;
            numChests++;
        }
    }
    return chests;
}

//The draw function and user input register.
void Play::play(Campaign campaign)
{
    Logger *logger = Logger::getSingleton();
    LoggerObserver logObs = LoggerObserver(logger);
    int mapInd = 0;
    logger->log("game", "initializing game");

    //Generate a map
    Grid map = campaign.getActiveMap();
    GridController gridController = GridController();
    GridObserver gridObserver = GridObserver(&map);

    //Initialize the player
    PlayerController player = PlayerController(map); //generate player
    player.customizeCharacter(); //select fighter they wish to be

    //Remove any nonsense that might affect some stuff
    clearInputBuffer();

    //player.setCharacter(createCharacter());
    //DIsplay Information for the first time
    player.getCharacter()->displayInfo();

    ConcreteCharacterObserver characterObserver;
    player.getCharacter()->attach(&characterObserver);

    int numNpcs = 0;
    NpcController* npcs = initializeEnemies(map);

    int numChests = 0;
    item::Item** chests = initializeChests(map);

    //Set intial input to '+'
    char in = '+';

    //Menu screen
    cout << "Welcome to the mountain explorer game: Press Enter to Start" << endl << endl;
    //Wait for input to start
    std::cin.get();

    logger->log("game", "starting game");
    DWORD inputTime = GetTickCount(); // Get current time in milliseconds
    //Run until the user wins or the user presses 'Q'
    while (in != 'q' && in != 'Q')
    {
        //Set input to '+' which does nothing
        in = '+';

        //Clear the screen
        system("cls"); // Clear screen on Windows

        //Print the map
        map.draw();
        cout << RESET << "Hitpoints: " << player.getCharacter()->getHitpoints() << endl;

        //Register the time
        DWORD startTime = GetTickCount(); // Get current time in milliseconds

        //Wait for user input or move to next frame
        while (true) {
            bool keyPressed = false;
            //Check if a certain amount of time has passed since the last input
            if (startTime - inputTime < 250) {
                startTime = GetTickCount();
                continue;
            }

            //Check if the user has input a value
            for (int key = 0; key < 256; ++key) {
                if (GetAsyncKeyState(key) & 0x8000) { // Check if key is pressed
                    in = char(key); // Store the pressed key
                    inputTime = GetTickCount(); // Get current time in milliseconds
                    keyPressed = true;
                    break; // Exit the loop once a key is pressed
                }
            }
            if (keyPressed)
                break;
        }

        //Debuging Data:
        //cout << in << endl;
        //cout << player.getPlayerInd() << "," << map.getTiles(player.getPlayerInd()).getIsPlayer() << endl;
        //cout << 0 << "," << map.getTiles(0).getIsPlayer() << endl;

        //Update the player,map and enemies based on the input
        if (player.update(in, npcs))
        {
            if(map.getTiles(player.getPlayerInd()).getType() == 'X')
            {
                mapInd++;
                if (campaign.getLength() > mapInd)
                {
                    campaign.setActiveMap(mapInd);
                    map = campaign.getActiveMap();
                    int npcsInd = 0;
                    while (npcsInd < 100)
                    {
                        npcs->setNpcInd(-2);
                        npcsInd++;
                    }
                    int chestInd = 0;
                   
                    npcs = initializeEnemies(map);
                    chests = initializeChests(map);

                    player.resetInd();
                }
                else
                    break;
            }
            int currentNpc = 0;
            NpcController* enemy = new NpcController();
            while (npcs[currentNpc].getNpcInd() != -1)
            {
                if (npcs[currentNpc].getNpcInd() != -2) {
                    npcs[currentNpc].nextTurn(player.getCharacter(),player.getPlayerInd());
                }
                currentNpc++;
            }

            gridController.update(in, player.getPlayerInd(), &map, chests);

            if (player.getCharacter()->getHitpoints() <= 0)
            {
                cout << "You've been killed!!!" << endl;
                break;
            }
        }
        else if (in == 'r' || in == 'R') {
            dice dice;

            dice.selectDiceToUse();
        }
          
        else if (in == 'i' || in == 'I')
        {
            itemSelect(player.getCharacter());
        }

        else if (in == 'p' || in == 'P')
        {
            system("cls");
            player.getCharacter()->displayInfo();
            cout << endl << "Press enter to exit.";
            std::cin.get();
        }
        else if (in == 'l' || in == 'L')
        {
            system("cls");
            logger->printLogs();
        }
        logger->log("game", "next turn");
    }
    logger->log("game", "ending game");
    //Input to close the game
    cout << "Press enter to quit.";
    std::cin.get();
}
