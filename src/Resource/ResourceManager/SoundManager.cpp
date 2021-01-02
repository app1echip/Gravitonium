#include "SoundManager.h"

SoundManager::SoundManager() {
    const std::string soundList[] = {
            "MainMenuBgm",
            "SelectBgm",
            "PlayBgm1",
            "PlayBgm2",
            "PlayBgm3",
            "MoveOver"};

    for (const auto &item:soundList) {
        auto ptr = std::make_unique<sf::SoundBuffer>();
        ptr->loadFromFile("asset/sound/" + item + ".wav");
        map.insert(std::make_pair(item, std::move(ptr)));
    }

    const std::string fireList[] = {
            "Airgun", "Rifle", "Shotgun", "SMG", "Sniper"
    };
    for (const auto &item:fireList) {
        auto p = std::make_unique<sf::SoundBuffer>();
        p->loadFromFile("asset/sound/Weapon/" + item + ".wav");
        map.insert(std::make_pair(item, std::move(p)));
    }
}

SoundManager::~SoundManager() {}

SoundManager &SoundManager::getInstance() {
    static SoundManager instance;
    return instance;
}

sf::SoundBuffer &SoundManager::getSound(const std::string &id) { return *map[id]; }