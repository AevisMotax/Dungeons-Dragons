#include "loggerObserver.h"

void LoggerObserver::draw()
{
    int in = -3;
    while (in != -1)
    {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string line;

            while (std::getline(file, line)) {
                int startPos = line.find("[");
                int endPos = line.find("]", startPos);
                string sourceName = line.substr(startPos + 1, endPos - startPos - 1);
                Logger::Source source = Logger::Source("Unknown");
                source.switchSource();
                for (int i = 0; i < NUMBER_OF_SOURCES; i++)
                {
                    if (sources[i].name == sourceName)
                        source = sources[i];
                }
                if (source.is_active)
                    std::cout << line << std::endl;
            }
            file.close();
        }
        else {
            std::cerr << "Failed to open log file: " << filename << std::endl;
        }
        cout << endl << endl;
        for (int i = 0; i < NUMBER_OF_SOURCES; i++)
        {
            cout << i << ":" << sources[i].name << endl;
        }
        cout << "Enter -1 to exit or the number a source to enable/disable it:";
        cin >> in;
        if (in > -1 && in < NUMBER_OF_SOURCES)
        {
            sources[in].switchSource();
        }
    }
}