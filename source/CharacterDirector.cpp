#include "CharacterDirector.h"
#include "player/Customizable/CharacterIO.h"
#include "source/globalFunctions.h"
#include "source/player/CharacterBuilder.h"
#include "source/FighterType.h"
#include "source/player/character.h"
#include "source/player/characterType.h"
#include "source/player/characterObserver.h"

#include<iostream>
#include<string>
#define stringify( name ) #name
#include <typeinfo>
#include <vector>
#include <cstdlib>
#include <thread>
#include <atomic>
#include <map>
#include <conio.h>


/**
* @brief
*/
CharacterDirector::CharacterDirector() {};

/**@brief getter */
Character* CharacterDirector::getCharacter()
{
    return this->c_builder->getCharacter();
};

//Get menu editor
void CharacterDirector::characterEditorMenu() 
{
    while (true)
    {
        system("cls");
        //Display menu option
        std::cout <<std::setw(15) << "Character Editor Menu" << std::endl;
        std::cout << "1. Create New Character\\NPC" << std::endl;
        std::cout << "2. Edit Existing Character" << std::endl;
        std::cout << "3. Delete Character" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "\nEnter your choice (With an integer): ";

        //User inpout
        int in;

        try {
            //clearInputBuffer(); //Clear what was left before
            std::cin >> in;

            //Checking if it fails
            if (std::cin.fail())
            {
                throw std::invalid_argument("Invalid input! Please retry\n");
            }

            //Create New Character
            if (in == 1)
            {
                this->selectFighterType();
            }
            else if (in == 2)
            {
                generator->showAllCharacterFiles();

                cout << "\nPlease write the character you wish to edit:\n" << endl;
                string temp = "";

                std::cin >> temp;
                generator->editCharacter(temp); //Attempt to edit character
            }
            else if (in == 3)
            {
                generator->showAllCharacterFiles();

                cout << "\nPlease write the character you wish to remove, or else press any key to exit:\n" << endl;
                string temp = "";

                cin >> temp;
                //Attempt to delete character
                generator->deleteCharacterFromFolder(temp);
            }
            else if (in == 4)
            {
                return;
            }
            else
            {
                std::cout << "Not in the choice list! Please retry\n" << std::endl;
                clearInputBuffer(); //Clear what was left before
                std::cin.get();
            }
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            clearInputBuffer(); //Clear what was left before
            std::cin.get();
        }
    }
}

/**@brief choose a brand new character creation*/
//Allow user to select a fighter of their type
void CharacterDirector::selectFighterType()
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
            Bully* bully = new Bully;
            this->setCharacterBuilder(bully);
            this->constructCharacter();
            //character = director.getCharacter(); //Adjust character to be it

            delete bully; bully = NULL;
            return;
            //character.setCharacterClass(CharacterType::Bully);
        }
        else if (userInput == 2) {
            //Create character
            Nimble* nimble = new Nimble;
            this->setCharacterBuilder(nimble);
            this->constructCharacter();

            //character = director.getCharacter();
            delete nimble; nimble = NULL;
            return;

            //character.setCharacterClass(CharacterType::Nimble);
        }
        else if (userInput == 3) {
            //Create character
            Tank* tank = new Tank;
            this->setCharacterBuilder(tank);
            this->constructCharacter();

            //character = director.getCharacter();
            delete tank; tank = NULL;
            return;
            //character.setCharacterClass(CharacterType::Tank);
        }
        else {
            cout << "\nNot valid, try again:";
            clearInputBuffer();
            _getch(); //Pause
        }
    }
}

string CharacterDirector::createCharacterName() 
{
    std::cout << "Please enter the name of the file you wish to save the character in: ";
    string temp;

    cin >> temp;
    return temp;
}

Character* CharacterDirector::loadCharacterFromFile() 
{
    generator->showAllCharacterFiles();

    //show if there any files
    bool temp = generator->isExistFile();
    if (temp) {
        cout << "\nPlease write the character you wish to load:\n" << endl;
        string temp = "";

        // Clear input buffer
        clearInputBuffer();
        // Read input using getline
        //std::getline(std::cin, temp);
        std::cin >> temp;

        Character* character = generator->loadCharacterFromSavedFiles(temp); //Attempt to edit character
        return character;
    }
    else {
        return NULL;
    }
}

/**\/@brief Create the character that will be played for this game
*/
void CharacterDirector::constructCharacter() 
{
    c_builder->createCharacter();
    std::string choice;

    while (true) {
        // Prompt the user to choose between randomizing or manually inputting skills
        std::cout << "Do you want to randomize your skills? (y/n): ";
        std::cin >> choice;
        if (choice == "y" || choice == "Y") {
            // Randomize skills
            c_builder->buildRandomAbilityScores();
            break;
        }
        else if (choice == "n" || choice == "N") {
            // Manually input skills
            c_builder->userSelectsAbilityScores();
            break;
        }
        else
        {
            std::cout << "Please retry" << std::endl;
        }
    }

    //Assign current ability order
    c_builder->assignAbilityOrder();

    //See if it's in god mode or whatever
    c_builder->getCharacter()->getGodMode();

    //get current name of file
    string temp = createCharacterName();

    //Save character as file
    generator->saveCharacter(temp, c_builder->getCharacter());
}

// Method to create an enemy character
Character* CharacterDirector::createEnemy() {
    // Seed the random number generator
    srand(static_cast<unsigned>(time(nullptr)));

    // Generate a random index to select a name from the list
    int index = rand() % ENEMY_NAMES.size();

    //randomly generate enemy names
    string name = ENEMY_NAMES[index];

    //Generate random Type --NOTE: SOME CLASSES HAVE BEEN REMOVED FOR SAFE USAGE
    std::vector<CharacterType> common_enemies = { CharacterType::Bully, CharacterType::Nimble, CharacterType::Tank, /*CharacterType::Dragon, CharacterType::Goblin*/ };

    index = rand() % common_enemies.size();

    CharacterType c = common_enemies[index];

    // Create the enemy character with the specified type and name
    return new Character(c, name, 1);;
}


//Character* CharacterDirector::customizeEnemy() 
//{
//    // Seed the random number generator
//    srand(static_cast<unsigned>(time(nullptr)));
//    string choice;
//    // Prompt the user to choose between randomizing or manually inputting skills
//    std::cout << "Would you like to generate your own enemies or randomize some? (yes/no): ";
//    std::cin >> choice;
//
//    if (choice == "yes") {
//        // Randomize skills
//        c_builder->buildAbilityScoresRandom();
//    }
//    else {
//        // Manually input skills
//        c_builder->buildAbilityScoresManual();
//    }
//
//
//
//
//}

/**\/@brief Create the character that will be played for this game
*/
//template<class T>
void CharacterDirector::setCharacterBuilder(CharacterBuilder* Builder)
{
    //this->builder = std::make_unique(Builder);
    this->c_builder = Builder;
};




