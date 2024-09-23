#include "concreteCharacterObserver.h"
#include "character.h"
#include "characterType.h"
#include <string>
using namespace std;

ConcreteCharacterObserver::ConcreteCharacterObserver()
{
    hitPoints = 0;
}

void ConcreteCharacterObserver::notify(Character* character)
{
    hitPoints = character->getHitpoints();
    cout << character->getName() << " has " << hitPoints << " hitpoints " << endl; 
}
