#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "source/subject.h"
#include "source/observer.h"
#ifndef LOGGER_H
#define LOGGER_H
// Logger class (Subject/Observable)
class Logger: public Subject {
public:
    struct Source {
        bool is_active;
        string name;
        Source(string name) :name(name), is_active(true){}
        void switchSource() { is_active = !is_active; }
    };
    Logger(const std::string& filename);

    ~Logger();

    void log(const std::string& source, const std::string& message);

    void printLogs();

    Source* getSources() { return sources; }
    string getFileName() { return filename; }
    const static int getNumberOfSources() { return NUMBER_OF_SOURCES; }
    static Logger* getSingleton() { return &singleton; }

private:
    static Logger singleton;
    const static int NUMBER_OF_SOURCES = 4;
    static Source sources[NUMBER_OF_SOURCES];
    ofstream logfile;
    string filename;
    std::string getCurrentTime() const {
        time_t rawtime;
        struct tm timeinfo;
        char buffer[80];
        time(&rawtime);
        localtime_s(&timeinfo, &rawtime);
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
        return std::string(buffer);
    }
};

#endif //LOGGGER_H