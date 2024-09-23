#define _HAS_STD_BYTE 0
//This is the driver of the program
//It registers user inputs and updates the map, player and enemies given the inputs.
//It is also responsible for updating the screen every couple of seconds with a redraw of the map or battle.
using namespace std;
#include "campaign.h"
#include "play.h"
#include "CharacterDirector.h"
#include <iostream>
#include <filesystem>
#include "items/itemIO.h"

void main()
{
    // Finding a random seed for map generation
    srand(static_cast<unsigned int>(time(nullptr)));
    Campaign campaign = Campaign();

    bool cont = true;
    int ind = 0;
    char in = '+';
    DWORD inputTime = GetTickCount();

    string  out;
    out = "Press SPACE to confirm your pick and use arrows to switch.\n";
    out = out + (ind == 0 ? "-Start Game\n" : " Start Game\n");
    out = out + (ind == 1 ? "-Character Menu Editor\n" : " Character Menu Editor\n");
    out = out + (ind == 2 ? "-Create Map\n" : " Create Map\n");
    out = out + (ind == 3 ? "-Edit Map\n" : " Edit Map\n");
    out = out + (ind == 4 ? "-Create Campaign\n" : " Create Campaign\n");
    out = out + (ind == 5 ? "-Edit Campaign\n" : " Edit Campaign\n");
    out = out + (ind == 6 ? "-Make items\n" : " Make items\n");
    out = out + (ind == 7 ? "-Quit\n" : " Quit\n");

    system("cls");
    cout << out << endl;

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
            if(ind > 0)
                ind--;
        }
        else if (in == '(')
        {
            if(ind < 7)
                ind++;
        }

        out = "Press SPACE to confirm your pick and use arrows to switch.\n";
        out = out + (ind == 0 ? "-Start Game\n" : " Start Game\n");
        out = out + (ind == 1 ? "-Character Menu Editor\n" : " Character Menu Editor\n");
        out = out + (ind == 2 ? "-Create Map\n" : " Create Map\n");
        out = out + (ind == 3 ? "-Edit Map\n" : " Edit Map\n");
        out = out + (ind == 4 ? "-Create Campaign\n" : " Create Campaign\n");
        out = out + (ind == 5 ? "-Edit Campaign\n" : " Edit Campaign\n");
        out = out + (ind == 6 ? "-Make items\n" : " Make items\n");
        out = out + (ind == 7 ? "-Quit\n" : " Quit\n");

        system("cls");
        cout << out << endl;

        if (in == ' ')
        {
            if (ind == 0)
            {
                system("cls");
                std::string directoryPath = "saves/campaigns/"; // Replace this with your directory path

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
                cout << "Enter the index of the campaign you want to play (To exit enter -1): ";
                cin >> fileInd;
                if (fileInd < fileNames.size() && fileInd > -1)
                {
                    campaign = Campaign::load(fileNames[fileInd]);
                    system("cls");
                    Play::play(campaign);
                }
            }
            if (ind == 1) {
                CharacterDirector director;
                director.characterEditorMenu();
            }
            if (ind == 2)
                Grid::create();
            if (ind == 3)
                Grid::edit();
            if (ind == 4)
                Campaign::create();
            if (ind == 5)
                Campaign::editCampaign();
            if (ind == 6)
                ItemIO::createItem();
            if (ind == 7)
                break;
        }
    }
}