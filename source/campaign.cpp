#define _HAS_STD_BYTE 0
#include "campaign.h"
#include "source/map/grid.h"
#include "globalFunctions.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include <cstdlib>
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>


Campaign::Campaign()
{
	campaignLength = 1;
	activeMap = Grid();
}

Campaign::Campaign(string fileName)
{
    if (fileName == "notSet")
    {
        campaignLength = 0;
        activeMap = Grid();
    }
    else
    {
        campaignLength = 1;
        mapSaves[0] = fileName;
        activeMap = Grid::load(fileName);
    }
}

void Campaign::create()
{
    Campaign campaign = Campaign("notSet");
    string  fout;
    int ind = 0;
    fout = "Press SPACE to confirm your pick and use arrows to switch.\n";
    fout = fout + (ind == 0 ? "-Add Map\n" : " Add Map\n");
    fout = fout + (ind == 1 ? "-Remove Last Map\n" : " Remove Last Map\n");
    fout = fout + (ind == 2 ? "-Edit Campaign\n" : " Edit Campaign\n");
    fout = fout + (ind == 3 ? "-Finish And Save\n" : " Finish And Save\n");


    system("cls");
    cout << fout << endl;
    for (int i = 0; i < campaign.campaignLength; i++)
    {
        cout << campaign.mapSaves[i] << " -> ";
    }

    bool cont = true;
    char in = '+';
    DWORD inputTime = GetTickCount();
    while (cont)
    {
        DWORD startTime = GetTickCount();
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

        if (in == '&')
        {
            if (ind > 0)
                ind--;
        }
        else if (in == '(')
        {
            if (ind < 4)
                ind++;
        }

        string  out;
        out = "Press SPACE to confirm your pick and use arrows to switch.\n";
        out = out + (ind == 0 ? "-Add Map\n" : " Add Map\n");
        out = out + (ind == 1 ? "-Remove Last Map\n" : " Remove Last Map\n");
        out = out + (ind == 2 ? "-Edit Campaign\n" : " Edit Campaign\n");
        out = out + (ind == 3 ? "-Finish And Save\n" : " Finish And Save\n");

        system("cls");
        cout << out << endl;
        for (int i = 0; i < campaign.campaignLength; i++)
        {
            cout << campaign.mapSaves[i] << " -> ";
        }

        if (in == ' ')
        {
            if (ind == 0)
            {
                system("cls");
                std::string directoryPath = "saves/grids/"; // Replace this with your directory path

                std::vector<std::string> fileNames;

                for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
                    if (entry.is_regular_file()) {
                        fileNames.push_back(entry.path().filename().string());
                    }
                }

                int i = 0;
                // Print all file names
                for (const auto& fileName : fileNames) {
                    std::cout << i << "." << fileName << std::endl;
                    i++;
                }

                int fileInd;
                cout << "Enter the index of the save you want to add: ";
                cin >> fileInd;
                if (fileInd < fileNames.size())
                {
                    string file = fileNames[fileInd];
                    campaign.addMap(file);
                }
                else
                {
                    cout << "The index you entered is too large.";
                }
            }
            else if (ind == 1)
            {
                system("cls");

                //Check if campaignLength is empty
                if (campaign.campaignLength != 0)
                {
                    campaign.removeMap();
                    cout << out << endl;
                    for (int i = 0; i < campaign.campaignLength; i++)
                    {
                        cout << campaign.mapSaves[i] << " -> ";
                    }
                }
                else 
                {
                    std::cout << "The editor is empty...." << std::endl;
                }


            }
            else if (ind == 2)
            {
                campaign.editCampaign();
            }
            else
            {
                string name;
                cout << "Enter the name of the campaign: ";
                cin >> name;
                campaign.save(name);
                break;
            }
        }
    }
}


//Edit campiagn whenever the user wants
void Campaign::editCampaign() 
{
    system("cls");
    std::string campaignsPath = "saves/campaigns/"; // Replace this with your directory path

    std::vector<std::string> campaignFileNames;

    for (const auto& entry : std::filesystem::directory_iterator(campaignsPath)) {
        if (entry.is_regular_file()) {
            campaignFileNames.push_back(entry.path().filename().string());
        }
    }

    int i = 0;
    // Print all file names
    for (const auto& fileName : campaignFileNames) {
        std::cout << i << "." << fileName << std::endl;
        i++;
    }

    string name;
    std::cout << "Enter the name of the campaign: \n";
    std::cin >> name;

    //trim and modify string fileName
    name = trim(name);
    name = removeExtension(name, ".txt");

    if (!filesystem::exists("saves/campaigns/" + name + ".txt")) {
        std::cout << "File does not exists (Enter to continue): " << name << std::endl;
        std::cin.get();
        return;
    }

    //Load campaign
    Campaign campaign = Campaign::load(name+ ".txt");


    // Display the current maps in the campaign
    cout << "Current maps in the campaign:" << endl;
    for (int i = 0; i < campaign.campaignLength; i++) {
        std::cout << i << ". " << campaign.mapSaves[i] << std::endl;
    }

    // Choose the map to edit or modify
    std::cout << "Enter the index of the map to edit or -2 to add a map or -1 to finish: ";
    int editIndex;
    std::cin >> editIndex;

    // Validate input
    if (editIndex < -2 || editIndex >= campaign.campaignLength) {
        std::cout << "Invalid index. Aborting edit." << std::endl;
        return;
    }

    if (editIndex == -1) {
        // Save the modified campaign
        campaign.save(name);
        return;
    }
    if (editIndex == -2)
    {
        system("cls");
        std::string directoryPath = "saves/grids/"; // Replace this with your directory path

        std::vector<std::string> fileNames;

        for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
            if (entry.is_regular_file()) {
                fileNames.push_back(entry.path().filename().string());
            }
        }

        int i = 0;
        // Print all file names
        for (const auto& fileName : fileNames) {
            std::cout << i << "." << fileName << std::endl;
            i++;
        }

        int fileInd;
        cout << "Enter the index of the save you want to add: ";
        cin >> fileInd;
        if (fileInd < fileNames.size())
        {
            string file = fileNames[fileInd];
            campaign.addMap(file);
        }
        else
        {
            cout << "The index you entered is too large.";
        }
        campaign.save(name);
        return;
    }
    //Add lines 
    std::cout << "\n\nFor reference, Here are all current map files available:" << std::endl;

    //SHowcase all maps available
    std::string directoryPath = "saves/grids/"; // Replace this with your directory path

    std::vector<std::string> fileNames;

    for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
        if (entry.is_regular_file()) {
            fileNames.push_back(entry.path().filename().string());
        }
    }

    //reset to 0 for future usage
    i = 0;
    // Print all file names
    for (const auto& fileName : fileNames) {
        std::cout << i << "." << fileName << std::endl;
        i++;
    }

    // Choose the action to perform
    std::cout << "\n\n\nSelect what to do with this map file by pressing a number:" << std::endl;
    std::cout << "1. Change Map File" << std::endl;
    std::cout << "2. Delete current Map" << std::endl;

    int action;
    std::cin >> action;

    if (action == 1) {
        //Change map file
        int fileInd;
        std::cout << "\n\nEnter the index of the new map file: ";
        std::cin >> fileInd;
        if (fileInd < fileNames.size())
        {
            string file = fileNames[fileInd];
            // Update the map file
            campaign.mapSaves[editIndex] = file;
        }
        else
        {
           std::cout << "The index you entered is too large.";
        }

        //Small message
        std::cout << "Map file changed successfully." << std::endl;
    }
    else if (action == 2) {
        // Delete Map
        // Move maps after editIndex one position left to overwrite the deleted map
        for (int i = editIndex; i < campaign.campaignLength - 1; i++) {
            campaign.mapSaves[i] = campaign.mapSaves[i + 1];
        }
        campaign.mapSaves[campaign.campaignLength -1] = "";
        campaign.campaignLength--;
        std::cout << "Map deleted successfully." << std::endl;
    }
    else {
        std::cout << "Invalid action. Aborting edit." << std::endl;
        return;
    }


    // Save the modified campaign
    campaign.save(name);
}


//Save campaign in directories
void Campaign::save(string name)
{
    // Creation of ofstream class object
    std::ofstream fout;

    // by default ios::out mode, automatically deletes
    // the content of file. To append the content, open in ios:app
    // fout.open("sample.txt", ios::app)
    fout.open("saves/campaigns/" + name + ".txt");

    // Execute a loop If file successfully opened
    for (int i = 0; i < campaignLength; i++)
    {
        fout << mapSaves[i] << endl;
    }

    // Close the File
    fout.close();
}

void Campaign::showAllFiles() 
{
    /* Empty for now, but eesentially a method to show all map files or campaigns in the upcoming future*/
}

Campaign Campaign::load(string name)
{
    std::ifstream file("saves/campaigns/" + name);
    Campaign campaign = Campaign("notSet");
    // Check if the file opened successfully
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
    }
    else
    {
        std::string line;
        // Read the file line by line
        while (std::getline(file, line)) {
            campaign.addMap(line);
        }
    }

    //Close file
    file.close();

    //return newly made campaign
    return campaign;
}

void Campaign::addMap(string mapFile)
{
    if (campaignLength == 0)
    {
        mapSaves[campaignLength] = mapFile;
        activeMap = Grid::load(mapFile);
        campaignLength++;
    }
    else
    {
        mapSaves[campaignLength] = mapFile;
        campaignLength++;
    }
}

//Remove the last map at the end
void Campaign::removeMap()
{
	mapSaves[campaignLength-1] = "";
	campaignLength--;
}

void Campaign::setActiveMap(int ind)
{
	activeMap = Grid::load(mapSaves[ind]);
}

Grid Campaign::getActiveMap()
{
	return activeMap;
}

string Campaign::getMapFile(int ind)
{
	return mapSaves[ind];
}

int Campaign::getLength()
{
	return campaignLength;
}