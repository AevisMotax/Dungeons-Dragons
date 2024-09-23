#ifndef CHARACTER_OBSERVER_H
#define CHARACTER_OBSERVER_H
#define _HAS_STD_BYTE 0
class Character;

class CharacterObserver {
public:
    virtual ~CharacterObserver() {}
    virtual void notify(Character* character) = 0;
};

#endif /* CHARACTER_OBSERVER_H */
