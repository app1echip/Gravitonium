#ifndef GRAVITONIUM_WEAPON_H
#define GRAVITONIUM_WEAPON_H

#include "BaseObject.h"
#include <vector>
#include <SFML/Audio.hpp>
#include "Bullet.h"

class Weapon : public BaseObject {
public:
    void loadData(b2Body *, const std::string &);

    void shoot();

    Weapon(b2World *);


private:
    std::string mName;
    std::vector<Bullet *> bullet;
    sf::Sound mGunfire;
    sf::Clock triggerClock;
    int lostCapacity = 0;
    float damage;
    float rof;
    unsigned int capacity;
};

#endif //GRAVITONIUM_WEAPON_H
