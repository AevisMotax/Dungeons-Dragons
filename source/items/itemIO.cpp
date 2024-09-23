#define _HAS_STD_BYTE 0
#include "itemIO.h"
#include "item.h"
#include "armor.h"
#include <source/items/armor.h>
#include <source/items/helmet.h>
#include <source/items/shield.h>
#include <source/items/ring.h>
#include <source/items/boots.h>
#include <source/items/weapon.h>
#include <source/items/belt.h>
#include <source/items/item.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <string>
#include <windows.h>
using namespace item;
using namespace std;

void ItemIO::createItem() {
    bool cont = true;
    int ind = 0;
    char in = '+';

    string  out;
    out = "Choose the type of item you want to create (Press space to confirm)\n";
    out = out + (ind == 0 ? "-Armor\n" : " Armor\n");
    out = out + (ind == 1 ? "-Belt\n" : " Belt\n");
    out = out + (ind == 2 ? "-Boots\n" : " Boots\n");
    out = out + (ind == 3 ? "-Helmet\n" : " Helmet\n");
    out = out + (ind == 4 ? "-Ring\n" : " Ring\n");
    out = out + (ind == 5 ? "-Shield\n" : " Shield\n");
    out = out + (ind == 6 ? "-Weapon\n" : " Weapon\n");
    out = out + (ind == 7 ? "-Exit\n" : " Exit\n");

    system("cls");
    cout << out << endl;

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
            if (ind < 7)
                ind++;
        }

        out = "Choose the type of item you want to create\n";
        out = out + (ind == 0 ? "-Armor\n" : " Armor\n");
        out = out + (ind == 1 ? "-Belt\n" : " Belt\n");
        out = out + (ind == 2 ? "-Boots\n" : " Boots\n");
        out = out + (ind == 3 ? "-Helmet\n" : " Helmet\n");
        out = out + (ind == 4 ? "-Ring\n" : " Ring\n");
        out = out + (ind == 5 ? "-Shield\n" : " Shield\n");
        out = out + (ind == 6 ? "-Weapon\n" : " Weapon\n");
        out = out + (ind == 7 ? "-Exit\n" : " Exit\n");

        system("cls");
        cout << out << endl;

        if (in == ' ')
        {
            if (ind == 0)
                makeArmor();
            if (ind == 1)
                makeBelt();
            if (ind == 2)
                makeBoots();
            if (ind == 3)
                makeHelmet();
            if (ind == 4)
                makeRing();
            if (ind == 5)
                makeShield();
            if (ind == 6)
                makeWeapon();
            if (ind == 7)
                cont = false;
        }
    }
    cout << "Press enter to continue.";
    cin.get();
}

item::Item* ItemIO::loadItem(string name) {
    std::ifstream file("saves/items/" + name);
    string itemName;
    string type;
    string weaponType;
    CharacterStat stat;
    string armorToString; //string to acquire the type of armor
    item::ArmorType armorType; //string for armor type

    int mod;
    // Check if the file opened successfully
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
    }
    else
    {
        std::string line;
        std::getline(file, line); 
        itemName = line;

        std::getline(file, line);
        type = line;
        if (type == "Weapon")
        {
            std::getline(file, line);
            weaponType = line;
        }

        if (type == "Armor") {
            std::getline(file, line);
            armorToString = line;
        }

        std::getline(file, line);
        if (line == "ArmorClass")
            stat = CharacterStat::ArmorClass;
        else if (line == "AttackBonus")
            stat = CharacterStat::AttackBonus;
        else if (line == "DamageBonus")
            stat = CharacterStat::DamageBonus;
        else if (line == "Strength")
            stat = CharacterStat::Strength;
        else if (line == "Charisma")
            stat = CharacterStat::Charisma;
        else if (line == "Constitution")
            stat = CharacterStat::Constitution;
        else if (line == "Wisdom")
            stat = CharacterStat::Wisdom;
        else if (line == "Dexterity")
            stat = CharacterStat::Dexterity;
        else if (line == "Intelligence")
            stat = CharacterStat::Intelligence;
        std::getline(file, line);
        mod = stoi(line);
    }
    // Close the file
    file.close();

    if (type == "Armor") {
        if (armorToString == "Light") {
            armorType = item::ArmorType::Light;
        }
        else if (armorToString == "Medium") {
            armorType = item::ArmorType::Medium;
        }
        else if (armorToString == "Heavy") {
            armorType = item::ArmorType::Heavy;
        }
        return new item::Armor(mod, stat, itemName, armorType);
    }
    else if (type == "Helmet")
        return new item::Helmet(mod, stat, itemName);
    else if (type == "Boots")
        return new item::Boots(mod, stat, itemName);
    else if (type == "Helmet")
        return new item::Helmet(mod, stat, itemName);
    else if (type == "Ring")
        return new item::Ring(mod, stat, itemName);
    else if (type == "Shield")
        return new item::Shield(mod, stat, itemName);
    else if (type == "Weapon")
        return new item::Weapon(mod, stat, itemName, weaponType);
}

void ItemIO::makeItem(string &name, int &mod) {
    cout << "Enter the name of your item: ";
    cin >> name;

    cout << endl << "Enter the modifier of your item (Enter an integer): ";
    cin >> mod;
}
void ItemIO::makeArmor() {
    string name;
    int mod;
    item::ArmorType armorType;

    cout << "Please provide which type of armor you would prefer? Enter with ther corresponding integer:" << endl
         <<"1. light" << endl 
         <<"2. medium"<< endl
         <<"3. heavy" << endl;


    cin >> armorType; //using overloaded >> operator in armor.cpp

    makeItem(name, mod);

    ofstream fout;
    fout.open("saves/items/" + name + ".txt");
    fout << name << endl;
    fout << "Armor" << endl;
    fout << armorType << endl; //using overload operator << in armor.cpp
    fout << "ArmorClass" << endl;
    fout << mod << endl;
    fout.close();
    cout << "Press enter to continue.";
    cin.get();
}
void ItemIO::makeBelt() {
    string name;
    int mod;
    makeItem(name, mod);

    string type;
    bool cont = true;
    int ind = 0;
    char in = '+';

    string  out;
    out = "Choose the stat the item impacts (Enter space to confirm): \n";
    out = out + (ind == 0 ? "-Strength\n" : " Strength\n");
    out = out + (ind == 1 ? "-Constitution\n" : " Constitution\n");

    system("cls");
    cout << out << endl;

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
            if (ind < 1)
                ind++;
        }

        out = "Choose the stat the item impacts (Enter space to confirm): \n";
        out = out + (ind == 0 ? "-Strength\n" : " Strength\n");
        out = out + (ind == 1 ? "-Constitution\n" : " Constitution\n");

        system("cls");
        cout << out << endl;

        if (in == ' ')
        {
            if (ind == 0)
                type = "Strength";
            if (ind == 1)
                type = "Constitution";
            break;
        }
    }

    ofstream fout;
    fout.open("saves/items/" + name + ".txt");
    fout << name << endl;
    fout << "Belt" << endl;
    fout << type << endl;
    fout << mod << endl;
    fout.close();
    cout << "Press enter to continue.";
    cin.get();
}
void ItemIO::makeBoots() {
    string name;
    int mod;
    makeItem(name, mod);

    string type;
    bool cont = true;
    int ind = 0;
    char in = '+';

    string  out;
    out = "Choose the stat the item impacts (Enter space to confirm): \n";
    out = out + (ind == 0 ? "-ArmorClass\n" : " ArmorClass\n");
    out = out + (ind == 1 ? "-Dexterity\n" : " Dexterity\n");

    system("cls");
    cout << out << endl;

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
            if (ind < 1)
                ind++;
        }

        out = "Choose the stat the item impacts (Enter space to confirm): \n";
        out = out + (ind == 0 ? "-ArmorClass\n" : " ArmorClass\n");
        out = out + (ind == 1 ? "-Dexterity\n" : " Dexterity\n");

        system("cls");
        cout << out << endl;

        if (in == ' ')
        {
            if (ind == 0)
                type = "ArmorClass";
            if (ind == 1)
                type = "Dexterity";
            break;
        }
    }

    ofstream fout;
    fout.open("saves/items/" + name + ".txt");
    fout << name << endl;
    fout << "Boots" << endl;
    fout << type << endl;
    fout << mod << endl;
    fout.close();
    cout << "Press enter to continue.";
    cin.get();
}
void ItemIO::makeHelmet() {
    string name;
    int mod;
    makeItem(name, mod);
    
    string type;
    bool cont = true;
    int ind = 0;
    char in = '+';

    string  out;
    out = "Choose the stat the item impacts (Enter space to confirm): \n";
    out = out + (ind == 0 ? "-ArmorClass\n" : " ArmorClass\n");
    out = out + (ind == 1 ? "-Wisdom\n" : " Wisdom\n");
    out = out + (ind == 2 ? "-Intelligence\n" : " Intelligence\n");

    system("cls");
    cout << out << endl;

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
            if (ind < 2)
                ind++;
        }

        out = "Choose the stat the item impacts (Enter space to confirm): \n";
        out = out + (ind == 0 ? "-ArmorClass\n" : " ArmorClass\n");
        out = out + (ind == 1 ? "-Wisdom\n" : " Wisdom\n");
        out = out + (ind == 2 ? "-Intelligence\n" : " Intelligence\n");

        system("cls");
        cout << out << endl;

        if (in == ' ')
        {
            if (ind == 0)
                type = "ArmorClass";
            if (ind == 1)
                type = "Wisdom";
            if (ind == 2)
                type = "Intelligence";
            break;
        }
    }

    ofstream fout;
    fout.open("saves/items/" + name + ".txt");
    fout << name << endl;
    fout << "Helmet" << endl;
    fout << type << endl;
    fout << mod << endl;
    fout.close();
    cout << "Press enter to continue.";
    cin.get();
}
void ItemIO::makeRing() {
    string name;
    int mod;
    makeItem(name, mod);

    string type;
    bool cont = true;
    int ind = 0;
    char in = '+';

    string  out;
    out = "Choose the stat the item impacts (Enter space to confirm): \n";
    out = out + (ind == 0 ? "-ArmorClass\n" : " ArmorClass\n");
    out = out + (ind == 1 ? "-Constitution\n" : " Constitution\n");
    out = out + (ind == 2 ? "-Wisdom\n" : " Wisdom\n");
    out = out + (ind == 3 ? "-Intelligence\n" : " Intelligence\n");
    out = out + (ind == 4 ? "-Charisma\n" : " Charisma\n");

    system("cls");
    cout << out << endl;

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

        out = "Choose the stat the item impacts (Enter space to confirm): \n";
        out = out + (ind == 0 ? "-ArmorClass\n" : " ArmorClass\n");
        out = out + (ind == 1 ? "-Constitution\n" : " Constitution\n");
        out = out + (ind == 2 ? "-Wisdom\n" : " Wisdom\n");
        out = out + (ind == 3 ? "-Intelligence\n" : " Intelligence\n");
        out = out + (ind == 4 ? "-Charisma\n" : " Charisma\n");

        system("cls");
        cout << out << endl;

        if (in == ' ')
        {
            if (ind == 0)
                type = "ArmorClass";
            if (ind == 1)
                type = "Constitution";
            if (ind == 2)
                type = "Wisdom";
            if (ind == 3)
                type = "Intelligence";
            if (ind == 4)
                type = "Charisma";
            break;
        }
    }

    ofstream fout;
    fout.open("saves/items/" + name + ".txt");
    fout << name << endl;
    fout << "Ring" << endl;
    fout << type << endl;
    fout << mod << endl;
    fout.close();
    cout << "Press enter to continue.";
    cin.get();
}
void ItemIO::makeShield() {
    string name;
    int mod;
    makeItem(name, mod);

    ofstream fout;
    fout.open("saves/items/" + name + ".txt");
    fout << name << endl;
    fout << "Shield" << endl;
    fout << "ArmorClass" << endl;
    fout << mod << endl;
    fout.close();
    cout << "Press enter to continue.";
    cin.get();
}
void ItemIO::makeWeapon() {
    string name;
    int mod;
    makeItem(name, mod);

    string type;
    bool cont = true;
    int ind = 0;
    char in = '+';

    string  out;
    out = "Choose the stat the item impacts (Enter space to confirm): \n";
    out = out + (ind == 0 ? "-AttackBonus\n" : " AttackBonus\n");
    out = out + (ind == 1 ? "-DamageBonus\n" : " DamageBonus\n");

    system("cls");
    cout << out << endl;

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
            if (ind < 1)
                ind++;
        }

        out = "Choose the stat the item impacts (Enter space to confirm): \n";
        out = out + (ind == 0 ? "-AttackBonus\n" : " AttackBonus\n");
        out = out + (ind == 1 ? "-DamageBonus\n" : " DamageBonus\n");

        system("cls");
        cout << out << endl;

        if (in == ' ')
        {
            if (ind == 0)
                type = "AttackBonus";
            if (ind == 1)
                type = "DamageBonus";
            break;
        }
    }
    cout << "Press enter to continue.";
    cin.get();

    string weaponType;
    cont = true;
    ind = 0;
    in = '+';

    out = "Choose the stat the item impacts (Enter space to confirm): \n";
    out = out + (ind == 0 ? "-Sword\n" : " Sword\n");
    out = out + (ind == 1 ? "-Bow\n" : " Bow\n");
    out = out + (ind == 2 ? "-GrapplingHook\n" : " GrapplingHook\n");

    system("cls");
    cout << out << endl;

    inputTime = GetTickCount();
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
            if (ind < 2)
                ind++;
        }

        string  out;
        out = "Choose the stat the item impacts (Enter space to confirm): \n";
        out = out + (ind == 0 ? "-Sword\n" : " Sword\n");
        out = out + (ind == 1 ? "-Bow\n" : " Bow\n");
        out = out + (ind == 2 ? "-GrapplingHook\n" : " GrapplingHook\n");

        system("cls");
        cout << out << endl;

        if (in == ' ')
        {
            if (ind == 0)
                weaponType = "Sword";
            if (ind == 1)
                weaponType = "Bow";
            if (ind == 2)
                weaponType = "GrapplingHook";
            break;
        }
    }

    ofstream fout;
    fout.open("saves/items/" + name + ".txt");
    fout << name << endl;
    fout << "Weapon" << endl;
    fout << weaponType << endl;
    fout << type << endl;
    fout << mod << endl;
    fout.close();
    cout << "Press enter to continue.";
    cin.get();
}