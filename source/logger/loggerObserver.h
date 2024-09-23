#pragma once
#include "source/logger/logger.h"
#include "source/observer.h"

class LoggerObserver: public Observer {
public:
	LoggerObserver(Logger* logger) {
		_subject = logger;
        filename = logger->getFileName();
        sources = logger->getSources();
		_subject->attach(this);
	}

	~LoggerObserver() {
		_subject->detach(this);
	}

	void update(Subject* subject) {
		draw();
	}

	void draw();

private:
        Subject* _subject;
        string filename;
        const int NUMBER_OF_SOURCES = Logger::getNumberOfSources();
        Logger::Source* sources;
};