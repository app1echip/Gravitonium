#ifndef GRAVITONIUM_CHARACTER_H
#define GRAVITONIUM_CHARACTER_H

#include "BaseObject.h"
#include "Weapon.h"

class Character : public BaseObject {
public:
    Character(b2World *);

    void move(Character::Direction);

    void setCharacter(const std::string &, const std::string &);

    void shoot();

private:
    int jumpCount = 0;
    int jumpLimit = 1;
    std::string mSkin, mWeapon;

    Weapon weapon;

    friend class Server;

    friend class Client;
};

#endif //GRAVITONIUM_CHARACTER_H