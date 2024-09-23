#include "CharacterIO.h"
#include "source/globalFunctions.h"
#include "../characterType.h"
#include "../character.h"
#include "../characterStat.h"
#include "../Fighter.h"
#include "../../Dependency/json.hpp"

#include <fstream>
#include <windows.h>
#include <cstdlib>
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>
#include <conio.h>
#include <chrono>
#include <thread>
#include<stdexcept>
#include<filesystem>
using namespace std;
using json = nlohmann::json; 
//using namespace System::Xml;


//Constructor and Destructor
CharacterIO::CharacterIO() 
{}

CharacterIO::~CharacterIO() 
{}

//CharacterIO::CharacterIO(const std::vector<std::string>& filenames, const std::vector<Character>& allCharacters, const std::vector<Character>& allNPCs, const std::vector<std::string>& fieldsToSkip)
//    : filenames(filenames), allCharacters(allCharacters), allNPCs(allNPCs), fieldsToSkip(fieldsToSkip)
//{
//}

//Loading NPcs
//std::vector<Character> CharacterIO::loadNPCFromSavedFiles() 
//{
//	string directory = "saves/NPCs"; //Directory Path
//
//    
//	//NOTE: MUST ADD EXCEPTION IN CASE IT'S EMPTY
//    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
//        if (entry.is_regular_file()) {
//            filenames.push_back(entry.path().filename().string());
//        }
//    }
//
//
//
//
//}

//Show all path
void CharacterIO::showAllCharacterFiles()
{
    int i = 1;
    string directory = "saves/Characters/"; //Directory Path
    system("cls");

    if (filenames.empty()) //verify if filenames is empty, then we would want to populate it first
    {
        //NOTE: MUST ADD EXCEPTION IN CASE IT'S EMPTY
        for (const auto& entry : std::filesystem::directory_iterator(directory)) {
            if (entry.is_regular_file()) {
                std::string temp = entry.path().filename().string();
                removeExtension(temp, ".json"); //remove json don't want to show that to user
                filenames.push_back(temp);
                //Show Character's file
                std::cout << i << ". " << temp << std::endl;
                i++;
            }
        }
    }
    else //we just show the data
    {
        i = 1;
        for (int j = 0; j < filenames.size(); ++j)
        {
            std::cout << i << ". " << filenames[j] << std::endl;
            i++;
        }
    }
}


//Show which user selects
void CharacterIO::displayCharacterStatsSelection(nlohmann::json& data, int selection)
{
    //Iterate over Character Stat
    // Iterate over each field in the JSON
    for (auto it = data.begin(); it != data.end(); ++it) {
        // Skip specific fields like "hitpoints" or "level"
        std::cout << it.key() << " : " << it.value() << std::endl;
    }
}

Character* CharacterIO::loadCharacterFromSavedFiles(const std::string& name)
{
    //operate on the file
    string fileName = name;
    removeExtension(fileName, ".json");
    std::ifstream readFile("saves/Characters/" + fileName + ".json", std::ifstream::in);

    // Check if the file opened successfully
    if (!readFile.is_open()) {
        readFile.close();
        std::cerr << "Error opening file!" << std::endl;
        return NULL;
    }
    else {
        //load json data
        json load_c;
        readFile >> load_c;

        //Class object
        Character* temporary = new Character;

        //Load all data into it
        temporary->setName(load_c["name"]);
        temporary->setGender(load_c["gender"]);

        //Save character attributes in json format
        //Stats
        temporary->setStrength(load_c["strength"]);
        temporary->setDexterity(load_c["dexterity"]);
        temporary->setConstitution(load_c["constitution"]);
        temporary->setWisdom(load_c["wisdom"]);
        temporary->setCharisma(load_c["charisma"]);
        temporary->setIntelligence(load_c["intelligence"]);

        //Game stuff

        temporary->setHitpoints(load_c["hitpoints"]);
        temporary->setLevel(load_c["level"]);
        temporary->setArmorClass(load_c["armorClass"]);
        temporary->setAttackBonus(load_c["attackBonus"]);
        temporary->setDamageBonus(load_c["damageBonus"]);

        //Whether he is a bully,nimble or Tank
        temporary->setCharacterClass(load_c["characterClass"]);
        //Attacks Per Round
        temporary->setRounds(load_c["rounds"]);
        //experience points
        temporary->setPoints(load_c["exp_Points"]);
        temporary->setStrategy(load_c["strategy"]);

        readFile.close();
        //NOTE: MUST ADD EXCEPTION IN CASE IT'S EMPTY
        return temporary;
    }
}


//Character CharacterIO::createNPCs() 
//{}
//
//Character CharacterIO::createMainCharacter()
//{}

//If another character previously existed, it will just overwrite the json file
void CharacterIO::saveCharacter(const std::string& name, Character* fighter)
{
    std::cout << "Saving Character........." << std::endl;
    
    std::ofstream JsonFile("saves/Characters/" + name + ".json" , std::ofstream::out);
    //new JSON class
    json modifyCharacter;

    modifyCharacter["name"] = fighter->getName();
    modifyCharacter["gender"] = fighter->getGender();

    //Save character attributes in json format
    //Stats
    modifyCharacter["strength"] = fighter->getStrength();
    modifyCharacter["dexterity"] = fighter->getDexterity();
    modifyCharacter["constitution"] = fighter->getConstitution();
    modifyCharacter["wisdom"] = fighter->getWisdom();
    modifyCharacter["charisma"] = fighter->getCharisma();
    modifyCharacter["intelligence"] = fighter->getStrength();

    //Game stuff
    modifyCharacter["hitpoints"] = fighter->getHitpoints();
    modifyCharacter["level"] = fighter->getLevel();
    modifyCharacter["armorClass"] = fighter->getArmorClass();
    modifyCharacter["attackBonus"] = fighter->getAttackBonus();
    modifyCharacter["damageBonus"] = fighter->getDamageBonus();

    //Whether he is a bully,nimble or Tank
    modifyCharacter["characterClass"] = fighter->getCharacterClass();
    //Attacks Per Round
    modifyCharacter["rounds"] = fighter->getRounds();
    //experience points
    modifyCharacter["exp_Points"] = fighter->getExp_Points();
    modifyCharacter["strategy"] = fighter->getStrategy();

    //Temporarily pause
    _getch();

    //Transfer data to json file then close it for further purposes
    JsonFile << std::setw(4) <<modifyCharacter << std::endl;
    JsonFile.close();
}


//Edit character
void CharacterIO::editCharacter(const std::string name)
{
    std::ifstream obtainedCharacter("saves/Characters/"+ name + ".json");
    bool continueEditing = true; //Control the loop
    int selection = 1;
    if (!obtainedCharacter.is_open()) {
        std::cerr << "Error: Failed to open JSON file." << std::endl;
        return;
    }

    //load into json
    json data;
    obtainedCharacter >> data;

    //Display available fields
    while (continueEditing)
    {
        system("cls");

        std::cout << "Write stat to modify:\n" << std::endl;

        //Iterate over Character Stat
        //for (int i = static_cast<int>(CharacterStat::ArmorClass); i <= static_cast<int>(CharacterStat::Wisdom); ++i) {
        //    CharacterStat stats = static_cast<CharacterStat>(i);
        //    std::cout << (i == selection ? "-" : " ") << getCharacterStatString(stats) << std::endl;
        //}
        // 
        //Iterate over Character Stat         
        std::cout << name << " File:" << std::endl;
        displayCharacterStatsSelection(data, selection);
        
        // Prompt the user to select a field to modify
        std::string selectedField;
        std::cout << "NOTE: To exit the customization scene, press \"E\"." << std::endl;
        std::cout << "\nEnter the name of the field you want to modify: ";
        clearInputBuffer(); //clear buffer for safe purposes
        std::cin >> selectedField;

        // Check if the input is empty (user pressed Enter)
        if (selectedField == "E" || selectedField == "e") {
            continueEditing = false; // Set the flag to false to exit the loop
            break;
        }

        //remove any nonsense
        selectedField = removeWhitespaces(selectedField); selectedField = trim(selectedField);

        // Check if the selected field should be skipped
        //if (std::find(fieldsToSkip.begin(), fieldsToSkip.end(), selectedField) != fieldsToSkip.end()) {
        //    std::cerr << "Error: Field '" << selectedField << "' cannot be modified." << std::endl;
        //    return;
        //}


        // Check if the selected field exists
        if (data.find(selectedField) != data.end()) 
        {
            // Prompt the user to enter the new value
            changeStat(data, selectedField);
            std::cout << "Value modified successfully." << std::endl;
        }
        else 
        {
            std::cerr << "Error: Field '" << selectedField << "' not found." << std::endl;
        }
    }

    // Close the input file stream
    obtainedCharacter.close();

    // Open the file in write mode
    std::ofstream JsonFile("saves/Characters/" + name + ".json");
    if (!JsonFile.is_open()) {
        std::cerr << "Error: Failed to open JSON file for writing." << std::endl;
        return;
    }

    //Transfer data to json file then close it for further purposes
    JsonFile << std::setw(4) << data << std::endl;
    JsonFile.close();
};

//Edit his stats
void CharacterIO::changeStat(nlohmann::json& data, const std::string& field)
{
    dice dice; //generate new dice

    std::cout << "Enter an appropriate integer value or Press \"R\" to randomize data" << std::endl;

    //User input
    string temp;
    clearInputBuffer(); //clear input beforehand
    std::getline(std::cin, temp);

    if (temp == "R" || temp == "r") 
    {
        dice.selectDiceToUse();

        data[field] = dice.getTotal();
        clearInputBuffer();
    }
    else 
    {
        try {
            //Automatically cancels if value is negative
            if (std::stoi(temp) <= 0) 
            {
                throw std::out_of_range("Value must be positive");
            }
            //Convert string to integer
            data[field] = std::stoi(temp);
        }
        catch (const std::invalid_argument& e) {
            // if the string does not represent a valid integer
            std::cerr << "Error: Invalid argument - " << e.what() << std::endl;

            clearInputBuffer();
            std::cin.get();
        }
        catch (const std::out_of_range& e) {
            // if value is out of the range of the target integer type
            std::cerr << "Error: Out of range - " << e.what() << std::endl;

            clearInputBuffer();
            std::cin.get();
        }      
    }      
}


//delete character from the save files
void CharacterIO::deleteCharacterFromFolder(std::string name)
{
    std::string directory = "saves/Characters/";
    removeExtension(name, ".json");

    try {
        std::filesystem::path filepath = directory + name + ".json";

        // Check if the file exists
        if (std::filesystem::exists(filepath)) {
            // Delete the file
            std::filesystem::remove(filepath);
            std::cout << "File '" << name << "' deleted successfully.\n";

            //Remove it from the vector with all filenames LOL
            filenames.erase(std::remove(filenames.begin(), filenames.end(), name));
        }
        else {
            std::cout << "File '" << name << "' does not exist.\n";
        }
    }
    catch (const std::filesystem::filesystem_error & e) {
        std::cerr << "Error deleting file: " << e.what() << std::endl;
    }
}

//Show if directory is empty... or else we just exity
bool CharacterIO::isExistFile()
{
    if (filenames.empty()) {
        std::cout << "Nothing exist! Can not proceed...Must create a new character.." << std::endl;

        // Pause for 2 seconds
        std::this_thread::sleep_for(std::chrono::seconds(2));

        return false;
    }
    //Assume it's true
    return true;
}

//void CharacterIO::saveCreation(std::string name, Fighter* fighter)
//{
//    std::ofstream fout;
//
//    // by default ios::out mode, automatically deletes
//    // the content of file. To append the content, open in ios:app
//    // fout.open("sample.txt", ios::app)
//    fout.open("saves/Characters" + name + ".json");
//
//
//
//    //Close file
//    fout.close();
//}