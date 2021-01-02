#ifndef GRAVITONIUM_SOUNDMANAGER_H
#define GRAVITONIUM_SOUNDMANAGER_H

#include <string>
#include <unordered_map>
#include <SFML/Audio.hpp>

class SoundManager {
private:
    SoundManager();

    ~SoundManager();

    std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>> map;
public:
    static SoundManager &getInstance();

    sf::SoundBuffer &getSound(const std::string &);
};

#endif //GRAVITONIUM_SOUNDMANAGER_H