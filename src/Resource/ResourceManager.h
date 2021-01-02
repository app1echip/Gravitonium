#ifndef GRAVITONIUM_RESOURCEMANAGER_H
#define GRAVITONIUM_RESOURCEMANAGER_H

#include "ResourceManager/TextureManager.h"
#include "ResourceManager/FontManager.h"
#include "ResourceManager/SoundManager.h"

class ResourceManager {
private:
    ResourceManager();

    ~ResourceManager();

    TextureManager &textureManager = TextureManager::getInstance();
    FontManager &fontManager = FontManager::getInstance();
    SoundManager &soundManager = SoundManager::getInstance();
public:
    static ResourceManager &getInstance();
};

#endif //GRAVITONIUM_RESOURCEMANAGER_H