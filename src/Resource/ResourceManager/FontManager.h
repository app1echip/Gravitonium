#ifndef GRAVITONIUM_FONTMANAGER_H
#define GRAVITONIUM_FONTMANAGER_H

#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>

class FontManager {
private:
    FontManager();

    ~FontManager();

    std::unordered_map<std::string, std::unique_ptr<sf::Font>> map;
public:
    static FontManager &getInstance();

    sf::Font &getFont(const std::string &);
};

#endif //GRAVITONIUM_FONTMANAGER_H