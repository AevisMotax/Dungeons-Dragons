#pragma once
#include "Observer.h"
#include <list>

using namespace std;

class Subject {
public:
	virtual void attach(Observer* o) {
		_observers.push_back(o);
	}

	virtual void detach(Observer* o) {
		_observers.remove(o);
	}

	virtual void notify() {
		for (auto& observer : _observers) {
			observer->update(this);
		}
	}

private:
	list<Observer*> _observers;
};
