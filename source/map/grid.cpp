//This is the implementation file: grid.cpp of the class Grid.
//The interface for the class grid is in the header file grid.h.
#include "tile.h"
#include "grid.h"
#include "source/globalFunctions.h"
#include <vector>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
using namespace std;

Grid::Grid(int width, int height, Tile tiles[3072])
{
    if (width > 96)
        width = 96;
    if (height > 32)
        height = 32;
    this->width = width;
    this->height = height;
    this->numTiles = width * height;
    this->upPathOdds = 0;
    this->leftPathOdds = 0;
    this->rightPathOdds = 0;
    this->downPathOdds = 0;
    this->mountains = 0;
    this->water = 0;

    this->numEnemies = 0;
    for (int i = 0; i < 3072; i++)
    {
        this->tiles[i] = tiles[i];
        if(tiles[i].getType() == 'V')
            numEnemies++;
    }
}

Grid Grid::create()
{
    int width;
    int height;
    std::cout << "Please enter the width of the grid (max 96): ";
    std::cin >> width;
    std::cout << "Please enter the height of the grid (max 32): ";
    std::cin >> height;
    std::system("cls");
    Tile tiles[3072];
 
    Grid grid = Grid(width, height, tiles);
    for (int i = 0; i < grid.numTiles; i++)
        grid.tiles[i] = Tile(char(219));
    grid.makePath();

    std::system("cls");
    for (int i = 0; i < grid.numTiles; i++)
        if (grid.tiles[i].getType() != '*')
            grid.tiles[i].setType(' ');
    grid.setTiles();

    grid.getTiles(grid.numTiles-1).setType('X');
    grid.getTiles(0).switchPlayer();
    grid.getTiles(0).setType(' ');
    if (grid.getTiles(0).getIsChest())
        grid.getTiles(0).switchChest();
    else if (grid.getTiles(0).getIsEnemy())
        grid.getTiles(0).switchEnemy();

    std::cout << "Name your grid: ";
    string name;
    std::cin >> name;
    grid.save(name);
    return grid;
}

void Grid::makePath()
{
    int ind = 0;
    int arr[3072];
    arr[0] = -1;
    int *moves = arr;
    char in;
    while (ind != numTiles-1)
    {
        tiles[ind].setType('*');
        std::system("cls");
        std::cout << toString();
        std::cout << "Make the path to the end using WASD keys, use R to undo: ";
        std::cin >> in;

        int prevInd = ind;
        if (in == 'A' || in == 'a')
        {
            ind = moveLeft(ind);
            if (ind != prevInd)
            {
                moves++;
                *moves = 1;
            }
        }
        else if (in == 'D' || in == 'd')
        {
            ind = moveRight(ind);
            if (ind != prevInd)
            {
                moves++;
                *moves = 0;
            }
        }
        else if (in == 'W' || in == 'w')
        {
            ind = moveUp(ind);
            if (ind != prevInd)
            {
                moves++;
                *moves = 3;
            }
        }
        else if (in == 'S' || in == 's')
        {
            ind = moveDown(ind);
            if (ind != prevInd)
            {
                moves++;
                *moves = 2;
            }
        }
        else if (in == 'R' || in == 'r')
        {
            if (*moves != -1)
            {
                tiles[ind].setType(char(219));
                if (*moves == 0)
                    ind = moveLeft(ind);
                if (*moves == 1)
                    ind = moveRight(ind);
                if (*moves == 2)
                    ind = moveUp(ind);
                if (*moves == 3)
                    ind = moveDown(ind);
                moves--;
            }
        }
    }
}

void Grid::setTiles()
{
    int ind = 0;
    char in = '+';
    Tile temp;
    temp = Tile(tiles[ind]);
    while (in != 'F' && in != 'f')
    {
        tiles[ind].setType('X');
        std::cout << "Tile: " << ind << ", " << temp.getType() << endl;
        draw();
        std::cout << "Enter command (R, WASD) or F to finish: ";
        std::cin >> in;
        if (in == 'A' || in == 'a')
        {
            tiles[ind] = temp;
            ind = moveLeft(ind);
            temp = Tile(tiles[ind]);
        }
        else if (in == 'D' || in == 'd')
        {
            tiles[ind] = temp;
            ind = moveRight(ind);
            temp = Tile(tiles[ind]);
        }
        else if (in == 'W' || in == 'w')
        {
            tiles[ind] = temp;
            ind = moveUp(ind);
            temp = Tile(tiles[ind]);
        }
        else if (in == 'S' || in == 's')
        {
            tiles[ind] = temp;
            ind = moveDown(ind);
            temp = Tile(tiles[ind]);
        }
        else if (in == 'R' || in == 'r')
        {
            char type = temp.getType();
            if (type != '*')
            {
                if (type == char(219))
                    temp.setType(' ');
                else if (type == 'M')
                    temp.setType('~');
                else if (type == '~')
                    temp.setType(' ');
                else if (type == ' ')
                    temp.setType('M');
            }
        }
        else if (in == 'F' || in == 'f')
        {
            tiles[ind] = temp;
            std::system("cls");
        }
        std::system("cls");
    }

    for (int i = 0; i < numTiles; i++)
        if (tiles[i].getType() == '*')
            tiles[i].setType(' ');
    ind = 0;
    temp = Tile(tiles[ind]);
    in = '+';

    
    string tempNpcs[100];
    string tempChests[100];
    int npcInd = 0;
    int chestInd = 0;
    int locationInd = 0;
    int locations[200];

    for (int i = 0; i < numTiles; i++)
    {
        if (tiles[i].getIsChest())
        {
            tiles[i].switchChest();
        }
        if (tiles[i].getIsEnemy())
        {
            tiles[i].switchEnemy();
        }
    }

    while (in != 'F' && in != 'f')
    {
        tiles[ind].setType('X');
        std::cout << "Add enemies(V) and chests(H) to the map" << endl;
        draw();
        std::cout << "Enter command (V,H,WASD) or F to finish or R to undo last action: ";
        std::cin >> in;
        if (in == 'A' || in == 'a')
        {
            tiles[ind] = temp;
            ind = moveLeft(ind);
            temp = Tile(tiles[ind]);
        }
        else if (in == 'D' || in == 'd')
        {
            tiles[ind] = temp;
            ind = moveRight(ind);
            temp = Tile(tiles[ind]);
        }
        else if (in == 'W' || in == 'w')
        {
            tiles[ind] = temp;
            ind = moveUp(ind);
            temp = Tile(tiles[ind]);
        }
        else if (in == 'S' || in == 's')
        {
            tiles[ind] = temp;
            ind = moveDown(ind);
            temp = Tile(tiles[ind]);
        }
        else if (in == 'V' || in == 'v')
        {
            if (!temp.getIsEnemy())
            {
                system("cls");
                std::string directoryPath = "saves/characters/"; // Replace this with your directory path

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
                std::cout << "Enter the index of the character you want to add: ";
                std::cin >> fileInd;
                if (fileInd < fileNames.size() || fileInd < 0)
                {
                    tempNpcs[npcInd] = fileNames[fileInd];
                    npcInd++;
                    locations[locationInd] = ind;
                    locationInd++;
                    temp.switchEnemy();
                }
                else
                {
                    std::cout << "The index you entered is not valid.";
                }
            }
        }
        else if (in == 'H' || in == 'h')
        {
            if (!temp.getIsChest())
            {
                system("cls");
                std::string directoryPath = "saves/items/"; // Replace this with your directory path

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
                std::cout << "Enter the index of the item you want to add: ";
                std::cin >> fileInd;
                if (fileInd < fileNames.size() || fileInd < 0)
                {
                    tempChests[chestInd] = fileNames[fileInd];
                    chestInd++;
                    locations[locationInd] = ind;
                    locationInd++;
                    temp.switchChest();
                }
                else
                {
                    std::cout << "The index you entered is not valid.";
                }
            }
        }
        else if (in == 'R' || in == 'r')
        {
            if (locationInd > 0)
            {
                if (tiles[locations[locationInd]].getIsEnemy())
                {
                    tiles[locations[locationInd]].switchEnemy();
                    locationInd--;
                    tempNpcs[npcInd] = "";
                    npcInd--;
                }

                if (tiles[locations[locationInd]].getIsChest())
                {
                    tiles[locations[locationInd]].switchChest();
                    locationInd--;
                    tempChests[chestInd] = "";
                    chestInd--;
                }
            }
        }

        else if (in == 'F' || in == 'f')
        {
            tiles[ind] = temp;
        }
        std::system("cls");
    }
    int index = 0;
    while (chestList[index] != "" && index < 100)
    {
        chestList[index] = "";
        index++;
    }
    index = 0;
    while (npcList[index] != "" && index < 100)
    {
        npcList[index] = "";
        index++;
    }

    int chestListInd = 0;
    int npcListInd = 0;
    for (int i = 0; i < numTiles; i++)
    {
        if (tiles[i].getIsChest())
        {
            int place = 0;
            for (int j = 0; j < 200; j++)
            {
                if (locations[j] == i)
                    break;

                if(tiles[locations[j]].getIsChest())
                    place++;
            }
            chestList[chestListInd] = tempChests[place];
            chestListInd++;
        }
        if (tiles[i].getIsEnemy())
        {
            int place = 0;
            for (int j = 0; j < 200; j++)
            {
                if (locations[j] == i)
                    break;

                if (tiles[locations[j]].getIsEnemy())
                    place++;
            }
            npcList[npcListInd] = tempNpcs[place];
            npcListInd++;
        }
    }
}

void Grid::edit() 
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

    string name;
    int fileInd;
    std::cout << "Enter the index of the map you want to edit: ";
    std::cin >> fileInd;
    if (fileInd < fileNames.size() || fileInd < 0)
    {
        name = fileNames[fileInd];
    }
    else
    {
        std::cout << "The index you entered is not valid.";
    }

    Grid::editMap(name);
}


void Grid::editMap(string fname) 
{
    try {
        //trim and modify string fileName
        fname = trim(fname);
        fname = removeExtension(fname, ".txt");

        //Will probably need to add accessors/mutatyors in the future
        Grid grid = Grid::load(fname + ".txt");

        //Verify if it loaded properly
        if (grid.getHeight() <= 0 || grid.getWidth() <= 0)
        {
            std::cerr << "Error: " << fname << " may not exist or has not loaded properly!" << std::endl;
            //return early
            return;
        }

        if (grid.getTiles(0).getIsPlayer())
            grid.getTiles(0).switchPlayer();

        //Build/edit map
        grid.makePath();

        for (int i = 0; i < grid.numTiles; i++)
            if (grid.tiles[i].getType() == char(219))
                grid.tiles[i].setType(' ');

        system("cls");

        grid.setTiles();

        //Set last tile as end route
        grid.getTiles(grid.numTiles - 1).setType('X');


        grid.getTiles(0).switchPlayer();
        grid.getTiles(0).setType(' ');
        if (grid.getTiles(0).getIsChest())
            grid.getTiles(0).switchChest();
        else if (grid.getTiles(0).getIsEnemy())
            grid.getTiles(0).switchEnemy();

        grid.save(fname);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

}

void Grid::save(string name)
{
    // Creation of ofstream class object
    std::ofstream fout;

    // by default ios::out mode, automatically deletes
    // the content of file. To append the content, open in ios:app
    // fout.open("sample.txt", ios::app)
    fout.open("saves/grids/" + name + ".txt");

    // Execute a loop If file successfully opened
    for (int i = 0; i < numTiles; i++)
    {
        if (i % width == 0 && i != 0)
            fout << endl;
        if (tiles[i].getIsChest())
            fout << tiles[i].getType() << "H";
        else if (tiles[i].getIsEnemy())
            fout << tiles[i].getType() << "V";
        else if(tiles[i].getIsPlayer())
            fout << tiles[i].getType() << "O";
        else
            fout << tiles[i].getType() << "N";
    }
    fout << endl << "Npcs:" << endl;
    int ind = 0;
    while (npcList[ind] != "")
    {
        fout << npcList[ind] << endl;
        ind++;
    }
    fout << "Chests:"<<endl;
    ind = 0;
    while (chestList[ind] != "")
    {
        fout << chestList[ind] << endl;
        ind++;
    }

    // Close the File
    fout.close();
}

Grid Grid::load(string name)
{
    std::ifstream file("saves/grids/" + name);

    // Check if the file opened successfully
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
    }
    else
    {
        std::string line;

        int height = 0;
        int width = 0;
        Tile tiles[3072];
        int tileInd = 0;
        // Read the file line by line
        while (std::getline(file, line)) {
            if (line == "Npcs:")
                break;
            if (width == 0)
            {
                width = (int) line.length()/2;
            }
            for (int i = 0; i < line.length(); i++)
            {
                Tile tile;
                if (line[i] == 'M')
                    tile = Tile('M');
                else if (line[i] == '~')
                    tile = Tile('~');
                else if (line[i] == 'X')
                    tile = Tile('X');
                else
                    tile = Tile(' ');

                i++;
                if (line[i] == 'V')
                    tile.switchEnemy();
                else if (line[i] == 'H')
                    tile.switchChest();
                else if (line[i] == 'O')
                    tile.switchPlayer();

                tiles[tileInd] = tile;
                tileInd++;
            }
            height++;
        }
        Grid grid = Grid(width, height, tiles);

        int ind = 0;
        while (std::getline(file, line))
        {
            if (line == "Chests:")
                break;
            grid.setNpc(line, ind);
            ind++;
        }
        ind = 0;
        while (std::getline(file, line))
        {
            grid.setChest(line, ind);
            ind++;
        }
        return grid;
    }

    // Close the file
    file.close();
}

Grid::Grid(int width, int height)
{
    //Set the width and height with a max of 100 and 50 respectively.
    
    this->width = width;
    this->height = height;

    //Set the numOfTiles
    numTiles = width * height;

    //Set the odds that mountain and water tiles will spawn
    mountains = ((rand() % 30) + 20) / 100.0;
    water = ((rand() % 30) + 20) / 100.0;

    //Generate the path, this ensures the user can get to the end
    generatePath();

    //Fill the rest of the map
    fillMap();

    //Spawn the player at the top left
    tiles[0].switchPlayer();
    //Make the bottom right tile the ending tile
    tiles[numTiles - 1] = Tile('X');
}

Grid::Grid()
{
    //Set the width and height randomly
    this->width = (rand() % 48)+48;
    this->height = (rand() % 16) + 16;
    //Set the number of tiles
    numTiles = width * height;

    //Set the odds that mountain and water tiles will spawn
    mountains = ((rand() % 30) + 5) / 100.0;
    water = ((rand() % 30) + 5) / 100.0;

    //Uncomment to debug map
    //for (int i = 0; i < 3072; i++)
    //{
    //    tiles[i] = Tile('*');
    //}

    //Generate the path, this ensures the user can get to the end
    generatePath();

    //Fill the rest of the map
    fillMap();

    //Spawn the player at the top left
    tiles[0].switchPlayer();

    //Make the bottom right tile the ending tile
    tiles[numTiles - 1] = Tile('X');
}

void Grid::generatePath()
{
    //Set the odds that the path moves a certain direction every move
    setPathOdds();

    //Setting up the checks to set the direction of the path
    int ind = 0;
    double right = rightPathOdds;
    double down = right + downPathOdds;
    double up = down + upPathOdds;

    //Make the start tile empty
    tiles[ind] = Tile(char(' '));

    while (ind != numTiles - 1)
    {
        //Randomly choose a direction then set that tile to empty
        double nextMove = (rand() % 100) / 100.0;
        if (nextMove < right)
            ind = moveRight(ind);
        else if (nextMove < down)
            ind = moveDown(ind);
        else if (nextMove < up)
            ind = moveUp(ind);
        else
            ind = moveLeft(ind);
        tiles[ind] = Tile(char(' '));

        double addExtension = (rand() % 1000) / 1000.0;
        if (addExtension < 0.05)
            outPath(ind);

        double isEnemy = (rand() % 1000) / 1000.0;
        if (isEnemy < 0.15 && ind != 0)
        {
            tiles[ind].switchEnemy();
            numEnemies++;
        }

        //Uncomment to debug map and view map generation
        //cout << toString();
        //cin.get();
    }
}

void Grid::outPath(int index)
{
    //Setting up the direction odds to make a new random path, and setting the length of the path
    int length = rand() % (numTiles / 50) + 10;
    int ind = index;

    double heightPath = ((rand() % 70) + 15) / 100.0;
    double widthPath = 1 - heightPath;;
    double rightOdds = widthPath * (((rand() % 50) + 25)/100.0);
    double upOdds = heightPath * (((rand() % 50) + 25)/100.0);
    double leftOdds = heightPath - rightOdds;
    double downOdds = widthPath - upOdds;

    double right = rightOdds;
    double down = right + downOdds;
    double up = down + upOdds;
    int i = 0;

    tiles[ind] = Tile(char(' '));

    while (i < length)
    {
        //Randomly choose a direction then set that tile to empty
        double nextMove = (rand() % 100) / 100.0;
        if (nextMove < right)
            ind = moveRight(ind);
        else if (nextMove < down)
            ind = moveDown(ind);
        else if (nextMove < up)
            ind = moveUp(ind);
        else
            ind = moveLeft(ind);

        tiles[ind] = Tile(char(' '));

        double isEnemy = (rand() % 1000) / 1000.0;
        if (isEnemy < 0.1 && ind != 0)
        {
            tiles[ind].switchEnemy();
            numEnemies++;
        }

        double addExtension = (rand() % 1000) / 1000.0;
        if (addExtension < 0.015)
            outPath(ind);
        i++;
    }
    tiles[ind].switchChest();
}


void Grid::fillMap()
{
    //Setting the odds that the tile will be empty
    double plains = 1 - (water + mountains);

    for (int i = 1; i < numTiles; i++)
    {
        //Checking if the path is on this tile
        if (tiles[i].getType() == char(0))
        {
            //Setting the type of the tile randomly
            double tileType = (rand() % 100) / 100.0;
            if (tileType < plains)
                tiles[i] = Tile(char(' '));
            else if (tileType < plains + mountains)
                tiles[i] = Tile('M');
            else
                tiles[i] = Tile('~');
        }
    }
}


string Grid::toString()
{
    //Printing the map
    string out;

    //Going through each row
    for (int i = 0; i < height; i++)
    {
        //Going through each column on the current row
        for (int t = 0; t < width; t++)
        {
            //Adding the tile to the out string
            out = out + tiles[t + i*width].toString();
        }
        //Printing instructions for the user
        if (i < 7)
        {
            if (i == 0)
                out = out + "     Legend:             Intructions:";
            else if (i == 1)
                out = out + "     M: Mountains        Use Arrows to move";
            else if (i == 2)
                out = out + "     V: Enemy            Press D to roll dice";
            else if (i == 3)
                out = out + "     ~: Water            Press I to equip items";
            else if (i == 4)
                out = out + "     O: Player           Press P to view stats";
            else if (i == 5)
                out = out + "     H: Chest";
            else if (i == 6)
                out = out + "     X: Winning Tile";
        }
        //Skipping to next row
        out = out + "\n";
    }
    return out;
}

void Grid::draw()
{
    //Going through each row
    for (int i = 0; i < height; i++)
    {
        //Going through each column on the current row
        for (int t = 0; t < width; t++)
        {
            //Adding the tile to the out string
            ColoredText text = tiles[t + i * width].draw();
            std::cout << text.bgColor << text.color << text.text << RESET;
        }
        //Printing instructions for the user
        if (i < 7)
        {
            if (i == 0)
                std::cout << "     " << "Legend:             Intructions:";
            else if (i == 1)
                std::cout << "     " << WHITE             << "M" << RESET << ": Mountains        Use Arrows to move";
            else if (i == 2)
                std::cout << "     " << RED               << "V" << RESET << ": NPC              Use WASD to use equipped weapon";
            else if (i == 3)
                std::cout << "     " << CYAN              << "~" << RESET << ": Water            Press R to roll dice";
            else if (i == 4)
                std::cout << "     " << BRIGHT_YELLOW     << "O" << RESET << ": Player           Press I to equip items";
            else if (i == 5)
                std::cout << "     " << YELLOW            << "H" << RESET << ": Chest            Press P to view stats";
            else if (i == 6)
                std::cout << "     " << BLACK << BG_GREEN << "X" << RESET << ": Winning Tile     Press L to view logs";
        }
        std::cout << endl;
    }
}

int Grid::getHeight()
{
    return height;
}

int Grid::getWidth()
{
    return width;
}

Tile& Grid::getTiles(int ind)
{
    return tiles[ind];
}

void Grid::setPathOdds()
{
    //Setting the path odds randomly, the odds always prefer moving right or down.
    //This is because over time moving right or down more often guarantees we make it to the end
    double leftRightOdds = ((double)width) / (width+height);
    double upDownOdds = 1 - leftRightOdds;
    leftPathOdds = leftRightOdds * ((rand() % 35) + 10) / 100.0;
    upPathOdds = upDownOdds * ((rand() % 35) + 10) / 100.0;
    rightPathOdds = leftRightOdds - leftPathOdds;
    downPathOdds = upDownOdds - upPathOdds;
}

int Grid::moveUp(int index)
{
    //Check if the index is at the top
    if (index < width)
        return index;
    return index - width;
}
int Grid::moveDown(int index)
{
    //Check if the index is at the bottom
    if (index >= (numTiles-width))
        return index;
    return index + width;
}
int Grid::moveLeft(int index)
{
    //Check if the index is at the left side
    if (0 == index % width)
        return index;
    return index - 1;
}
int Grid::moveRight(int index)
{
    //Check if the index is at the right side
    if (width-1 == index % width)
        return index;
    return index + 1;
}

int Grid::checkBattle(int playerInd)
{
    if (tiles[moveUp(playerInd)].getIsEnemy())
    {
        tiles[moveUp(playerInd)].switchEnemy();
        return 1;
    }
    else if (tiles[moveDown(playerInd)].getIsEnemy())
    {
        tiles[moveDown(playerInd)].switchEnemy();
        return 2;
    }
    else if (tiles[moveLeft(playerInd)].getIsEnemy())
    {
        tiles[moveLeft(playerInd)].switchEnemy();
        return 3;
    }
    else if (tiles[moveRight(playerInd)].getIsEnemy())
    {
        tiles[moveRight(playerInd)].switchEnemy();
        return 4;
    }
    else 
        return 0;
}