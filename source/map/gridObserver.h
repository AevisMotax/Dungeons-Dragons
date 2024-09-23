#pragma once
#include "map/grid.h"
#include <iostream>

class GridObserver : public Observer {
public:
	GridObserver(Grid* grid) {
		_subject = grid;
		_subject->attach(this);
	}

	~GridObserver() {
		_subject->detach(this);
	}

	void update(Subject* subject) {
		if (subject == _subject)
			draw();
	}

	void draw() {
		//Print the map
		cout << _subject->toString();
	}

private:
	Grid* _subject;
};
