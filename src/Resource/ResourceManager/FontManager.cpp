#include "FontManager.h"

FontManager::FontManager() {
    const std::string list[] = {"m3x6","FSEX302"};
    for (const auto &item:list) {
        auto ptr = std::make_unique<sf::Font>();
        ptr->loadFromFile("asset/font/" + item + ".ttf");
        map.insert(std::make_pair(item, std::move(ptr)));
    }
}

FontManager::~FontManager() {}

FontManager &FontManager::getInstance() {
    static FontManager instance;
    return instance;
}

sf::Font &FontManager::getFont(const std::string &id) { return *map[id]; }