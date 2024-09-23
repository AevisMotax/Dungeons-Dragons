#ifndef CONCRETECHARACTEROBSERVER_H
#define CONCRETECHARACTEROBSERVER_H
#include "CharacterObserver.h"
#include <source/items/armor.h>
#include <source/items/helmet.h>
#include <source/items/shield.h>
#include <source/items/ring.h>
#include <source/items/boots.h>
#include <source/items/weapon.h>
#include <source/items/belt.h>
#include <string>

class ConcreteCharacterObserver : public CharacterObserver {
public:
    ConcreteCharacterObserver();
    void notify(Character* character) override;
private:
    int hitPoints;
};
#endif //CONCRETECHARACTEROBSERVER_H