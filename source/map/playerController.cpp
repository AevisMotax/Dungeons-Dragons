//This is the implementation file: playerController.cpp of the class playerController.
//The interface for the class playerController is in the header file playerController.h.
#include "playerController.h"
#include "source/globalFunctions.h"
#include "tile.h"
#include "grid.h"
#include "source/FighterType.h"
#include "source/player/character.h"
#include "source/Npc/NpcController.h"
#include "source/Npc/AttackNpcStrategy.h"
#include "source/player/characterType.h"
#include <source/player/CharacterBuilder.h>
#include "source/CharacterDirector.h"
#include "source/player/humanCharacterStrategy.h"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

//Determine the arrow keys
//#define VK_UP 0x26
//#define VK_DOWN 0x28
//#define VK_RETURN 0x0D


HumanCharacterStrategy strat = HumanCharacterStrategy();
//Initialize the player
PlayerController::PlayerController(Grid& igrid) : grid(igrid)
{
    logger = Logger::getSingleton();
    strategy = &strat;
    playerInd = 0;
}

//Get player's location
int PlayerController::getPlayerInd()
{
    return playerInd;
}

Character* PlayerController::getCharacter()
{
    return character;
}

CharacterDirector PlayerController::getCharacterGenerator() 
{
    return director;
}

////Character* PlayerController::getCharacter()
////{
////    return &builder.getCharacter();
////}



//Just a displaying the character
void PlayerController::displayCharacterSelectionScreen(int selection) 
{
    system("cls"); //erase temp screen
    //Tell user if they want to randomize stats or make them on their own:
    std::cout << "Would you like to load or create an entirely new character? Press Enter on your selected option" << std::endl;
    std::cout << (selection == 0 ? "-Load" : " Load") << std::endl;
    std::cout << (selection == 1 ? "-Create new" : " Create new") << std::endl;
    std::cout << (selection == 2 ? "-Continue" : " Continue") << std::endl;
}


//Allow customization of character
void PlayerController::customizeCharacter() 
{
    //input
    bool cont = true;
    char input;
    int key, choice = 0;

    //DWORD inputTime = GetTickCount(); //Calculate the tick or the ASCII code
    DWORD64 inputTime = 0; //Calculate the tick or the ASCII code

    while (cont) 
    {
        //Display choice
        displayCharacterSelectionScreen(choice);

        // Wait for the release of the ENTER key
        while (GetAsyncKeyState(VK_RETURN) & 0x8000)
            ;

        DWORD64 startTime = GetTickCount64();
        while (true) {
            bool keyPressed = false;
            //Check if a certain amount of time has passed since the last input
            if (startTime - inputTime < 250) {
                startTime = GetTickCount64();
                continue;
            }

            //Check if the user has input a value
            for (key = 0; key < 256; ++key) {
                if (GetAsyncKeyState(key) & 0x8000) { // Check if key is pressed
                    input = char(key); // Store the pressed key
                    inputTime = GetTickCount64(); // Get current time in milliseconds
                    keyPressed = true;
                    break; // Exit the loop once a key is pressed
                }
            }
            if (keyPressed)
                break;
        }

        //// Check for input
        //inputTime = GetTickCount64(); // Reset input time
        //while (GetTickCount64() - inputTime < 250) // Wait for input for 250 milliseconds
        //{
        //    if (GetAsyncKeyState(VK_UP) & 0x8000) { // Arrow up pressed
        //        input = '&';
        //        break;
        //    }
        //    else if (GetAsyncKeyState(VK_DOWN) & 0x8000) { // Arrow down pressed
        //        input = '(';
        //        break;
        //    }
        //    else if (GetAsyncKeyState(VK_RETURN) & 0x8000) { // Enter key pressed
        //        input = '\r';
        //        break;
        //    }
        //}

        //Select the changing output

        //case VK_UP:        //case VK_DOWN
        if (input == '&') {
            if (choice > 0) {
                choice--;
            }
        }
        else if (input == '(') {
            if (choice < 2) {
                choice++;
            }
        }
        //Go with the option we selected        //case VK_RETURN
        else if (input == '\r') {
            if (choice == 0) {
                loadCharacter();
            }
            else if (choice == 1) {
                selectFighterType();
            }
            else if (choice == 2) {
                //Verify if character is still NULL;
                if (character == NULL) {
                    std::cout << "No character was loaded!" << std::endl;
                    clearInputBuffer();
                    _getch();
                }
                else {
                    clearInputBuffer();
                    break;
                }
            }
        }        
    }
}

//Load a made character HOPEFULLY IT WORKS
void PlayerController::loadCharacter() 
{
    character = director.loadCharacterFromFile();
}

//Allow user to select a fighter of their type
void PlayerController::selectFighterType() 
{
    int userInput;

    while (true) {
        system("cls");  // Clear console screen (Windows specific)
        cout << "=== Character Fighting Type ===" << endl;
        cout << "Below are the type of fighter you may wish to be:\nPlease select one of them by pressing the corresponding index "
            "NOTE: ONLY BULLY, NIMBLE, AND TANK WORK AS OF NOW!!!\n" << std::endl;

        //Showcase information of the CHaracters and stuff
        for (int i = static_cast<int>(CharacterType::Bully); i <= static_cast<int>(CharacterType::Tank); i++) {
            CharacterType type = static_cast<CharacterType>(i);
            std::cout << static_cast<int>(type) << ". " << characterTypeInfo[i] << std::endl;
        }

        cin >> userInput;

        // Process user input
        if (userInput == 1) {
            //Create character
            director.setCharacterBuilder(bully);
            director.constructCharacter();
            character = director.getCharacter(); //Adjust character to be it
            return;
            //character.setCharacterClass(CharacterType::Bully);
        }
        else if (userInput == 2) {
            //Create character
            //Create character
            director.setCharacterBuilder(nimble);
            director.constructCharacter();

            character = director.getCharacter();
            return;

            //character.setCharacterClass(CharacterType::Nimble);
        }
        else if (userInput == 3) {
            //Create character
            //Create character
            director.setCharacterBuilder(tank);
            director.constructCharacter();

            character = director.getCharacter();
            return;

            //character.setCharacterClass(CharacterType::Tank);
        }
        else {
            cout << "\nNot valid, try again:";
            clearInputBuffer();
            _getch(); //Pause
        }
    }

    //Delete constructor after implementing it, to save memories
    //--NOTE: ENSURE THAT WE CAN RELOAD IT ONCE WE START A NEW GAME
    delete bully; bully = NULL;
    delete nimble; nimble = NULL;
    delete tank; tank = NULL;
}


//void PlayerController::setCharacterBuilder(CharacterBuilder& builder)
//{
//    this->character = (builder.getCharacter());
//    //this->character = character;
//}


void PlayerController::createEnemies() 
{

}

//Update the player every frame
//int in: user input
bool PlayerController::update(char in, NpcController * npcs)
{
    if (strategy->execute(in, npcs, playerInd, &grid, *character))
    {
        string ind = std::to_string(playerInd) + "";
        logger->log("grid", character->getName() + " has moved to " + ind);
        return true;
    }
    else
        return false;
}