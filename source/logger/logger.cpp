#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "logger.h"
#include "source/subject.h"
#include "source/observer.h"
Logger::Source Logger::sources[Logger::NUMBER_OF_SOURCES] = { Logger::Source("game"),Logger::Source("grid"),Logger::Source("battle"),Logger::Source("dice") };
Logger Logger::singleton = Logger("logs.txt");
Logger::Logger(const std::string& filename) : filename(filename) {
    logfile.open(filename, std::ios::app);
    if (!logfile.is_open()) {
        std::cerr << "Failed to open log file: " << filename << std::endl;
        cin.get();
    }
}

Logger::~Logger() {
    if (logfile.is_open()) {
        logfile.close();
    }
}

void Logger::log(const std::string& source, const std::string& message) {
    if (logfile.is_open()) {
        std::string timestamp = getCurrentTime();
        logfile << timestamp << " [" << source << "] - " << message << std::endl;
    }
}

void Logger::printLogs() {
    notify();
}
