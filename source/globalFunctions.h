#ifndef GLOBALFUNCTIONS_H
#define GLOBALFUNCTIONS_H
#define RESET          "\033[0m"
#define BLACK          "\033[30m"
#define RED            "\033[31m"
#define GREEN          "\033[32m"
#define YELLOW         "\033[33m"
#define BLUE           "\033[34m"
#define MAGENTA        "\033[35m"
#define CYAN           "\033[36m"
#define WHITE          "\033[37m"
#define BRIGHT_BLACK   "\033[90m"
#define BRIGHT_RED     "\033[91m"
#define BRIGHT_GREEN   "\033[92m"
#define BRIGHT_YELLOW  "\033[93m"
#define BRIGHT_BLUE    "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN    "\033[96m"
#define BRIGHT_WHITE   "\033[97m"
#define BG_BLACK       "\033[40m"
#define BG_RED         "\033[41m"
#define BG_GREEN       "\033[42m"
#define BG_YELLOW      "\033[43m"
#define BG_BLUE        "\033[44m"
#define BG_MAGENTA     "\033[45m"
#define BG_CYAN        "\033[46m"
#define BG_WHITE       "\033[47m"
#define BG_BRIGHT_BLACK   "\033[100m"
#define BG_BRIGHT_RED     "\033[101m"
#define BG_BRIGHT_GREEN   "\033[102m"
#define BG_BRIGHT_YELLOW  "\033[103m"
#define BG_BRIGHT_BLUE    "\033[104m"
#define BG_BRIGHT_MAGENTA "\033[105m"
#define BG_BRIGHT_CYAN    "\033[106m"
#define BG_BRIGHT_WHITE   "\033[107m"

#include "source/player/characterType.h"
#include <ios> //Streamsize
#include <limits> // Needed for numeric_limits
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include <chrono>
#include<ctime>
#include <iomanip>
#include<sstream>

/**
 * @file GlobalFunctions.h
 * @brief Declaration of global utility functions.
 */

/**
* @brief //A concrete vector of names to be able to create names
*/
const inline std::vector<std::string> ENEMY_NAMES = {
    "Darkrai", "Kratos", "Zoroark", "Kragson", "Urzogginia", "Goar", "Dora", "Mimikyu", "Mog", "Rizz", "Slog", "Snag", "Krak"
};

/**
* @brief //Transform character Type to name
*/
std::string characterTypeToString(const CharacterType& type);



struct ColoredText {
    std::string text;
    std::string color;
    std::string bgColor;
};


/**
 * @brief Trim a filename to remove whitespaces from both sides.
 * @param fname The filename to be trimmed.
 * @return Trimmed filename without leading and trailing whitespaces.
 */
//inline std::string trim(std::string& fname);
inline std::string trim(std::string& fname)
{
    const std::string whiteSpaces(" \f\n\r\t\v");

    std::string::size_type first = fname.find_first_not_of(whiteSpaces);
    if (std::string::npos == first)
    {
        return fname;
    }

    std::string::size_type last = fname.find_last_not_of(whiteSpaces);

    if (std::string::npos == last)
    {
        return fname;
    }

    return fname.substr(first, (last - first + 1));
}

/**
 * @brief Trim a filename to remove a specific file extension.
 * @param filename The filename to be processed.
 * @param extension The file extension to be removed.
 * @return Filename without the specified extension.
 */
std::string removeExtension(std::string& filename, std::string extension);

/**
 * @brief Trim a name to remove all whitespaces.
 * @param name The filename to be processed.
 * @return a name without any whitespace.
 */
std::string removeWhitespaces(std::string& name);


/**
 * @brief clear input buffer
 */
//inline void clearInputBuffer();
//Clear buffer anytime we need
inline void clearInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/**
 * @brief get current Date Time
 * @return the date time in string
 */
inline std::string getCurrentDateTime() {
    // Get current time
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    // Convert current time to struct tm
    //auto now = std::time(nullptr);
    struct tm tm_time;
    localtime_s(&tm_time, &now_time);

    // Format date and time
    std::ostringstream oss;

    oss << std::put_time(&tm_time, "%Y-%m-%d-%H-%M-%S");
    return oss.str();
}
//inline std::string getCurrentDateTime();


#endif //GLOBALFUNCTIONS_H

