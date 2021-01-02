#include "ResourceManager.h"

ResourceManager::ResourceManager() {}

ResourceManager::~ResourceManager() {}

ResourceManager &ResourceManager::getInstance() {
    static ResourceManager instance;
    return instance;
}