#include "TextureManager.h"

TextureManager::TextureManager() {
    const std::string list[] = {"weapon", "bullet", "SelectBackground", "HelpPage", "Option"};
    for (const auto &item:list) {
        auto p = std::make_unique<sf::Texture>();
        p->loadFromFile("asset/image/" + item + ".png");
        mMap.insert(std::make_pair(item, std::move(p)));
    }

    const std::string mapList[] = {"Cyberpunk", "Forest", "Industrial", "Mountain", "Polar", "Space", "Underwater"};
    for (const auto &item:mapList) {
        auto p = std::make_unique<sf::Texture>();
        p->loadFromFile("asset/image/Map/" + item + ".png");
        mMap.insert(std::make_pair(item, std::move(p)));
    }

    const std::string charList[] = {"Hacker", "RedBoy", "Shade", "Skeleton"};
    for (const auto &item:charList) {
        auto p = std::make_unique<sf::Texture>();
        p->loadFromFile("asset/image/Character/" + item + ".png");
        mMap.insert(std::make_pair(item, std::move(p)));
    }

    const std::string weaponList[] = {"Airgun", "Rifle", "Shotgun", "SMG", "Sniper"};
    for (const auto &item:weaponList) {
        auto p = std::make_unique<sf::Texture>();
        p->loadFromFile("asset/image/Weapon/" + item + ".png");
        mMap.insert(std::make_pair(item, std::move(p)));
    }

    const std::string bgList[] = {"BG1", "BG2", "BG3", "BG4", "BG5", "BG6", "BG7"};
    for (const auto &item:bgList) {
        auto p = std::make_unique<sf::Texture>();
        p->loadFromFile("asset/image/Background/" + item + ".png");
        mMap.insert(std::make_pair(item, std::move(p)));
    }
}

TextureManager::~TextureManager() {}

TextureManager &TextureManager::getInstance() {
    static TextureManager instance;
    return instance;
}

sf::Texture &TextureManager::getTexture(const std::string &id) {
    return *mMap[id];
}