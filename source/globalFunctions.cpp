#include "globalFunctions.h"
#include "source/player/characterType.h"
#include <string>


//Get character Type
std::string characterTypeToString(const CharacterType& type) {
    switch (type) {
    case CharacterType::Hero:
        return "Hero";
    case CharacterType::Bully:
        return "Bully";
    case CharacterType::Nimble:
        return "Nimble";
    case CharacterType::Tank:
        return "Tank";
    case CharacterType::Dragon:
        return "Dragon";
    case CharacterType::Goblin:
        return "Goblin";
    default:
        return "Unknown";
    }
}

//brief trim a filename to remove whitespaces from  both sides
//inline std::string trim(std::string& fname)
//{
//    size_t first = fname.find_first_not_of(' \t\n\r');
//    if (std::string::npos == first)
//    {
//        return fname;
//    }
//    size_t last = fname.find_last_not_of(' \t\n\r');
//    if (std::string::npos == last)
//    {
//        return fname;
//    }
//
//    return fname.substr(first, (last - first + 1));
//}



// brief trim a filename to remove .txt mention 
std::string removeExtension(std::string& filename, std::string extension) 
{
    size_t found = filename.find(extension);

    if (found != std::string::npos) 
    {
        filename.erase(found, extension.size());
    }

    return filename;
}


//Remove all whitespaces in string
std::string removeWhitespaces(std::string& name) 
{
    std::string::iterator end_pos = std::remove(name.begin(), name.end(), ' ');
    name.erase(end_pos, name.end());

    return name;
}

//Clear buffer anytime we need
//inline void clearInputBuffer()
//{
//    std::cin.clear();
//    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//}

//Get current time
//inline std::string getCurrentDateTime() {
//    // Get current time
//    auto now = std::chrono::system_clock::now();
//    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
//
//    // Convert current time to struct tm
//    //auto now = std::time(nullptr);
//    struct tm tm_time;
//    localtime_s(&tm_time, &now_time);
//
//    // Format date and time
//    std::ostringstream oss;
//
//    oss << std::put_time(&tm_time, "%Y-%m-%d-%H-%M-%S");
//    return oss.str();
//}