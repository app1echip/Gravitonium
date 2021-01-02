#ifndef GRAVITONIUM_TEXTUREMANAGER_H
#define GRAVITONIUM_TEXTUREMANAGER_H

#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>

class TextureManager {
private:
    TextureManager();

    ~TextureManager();

    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> mMap;
public:
    static TextureManager &getInstance();

    sf::Texture &getTexture(const std::string &);
};

#endif //GRAVITONIUM_TEXTUREMANAGER_H