#include "GameConfig.h"
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>

GameConfig::GameConfig() {
    loadConfig();
}

GameConfig::~GameConfig() {}

void GameConfig::loadConfig() {
    FILE *fp = fopen("data/GameConfig.json", "rb");
    char buffer[UINT16_MAX];
    rapidjson::FileReadStream is(fp, buffer, sizeof(buffer));
    fclose(fp);
    rapidjson::Document document;
    document.ParseStream(is);

    Fullscreen = document["Fullscreen"].GetBool();
    Scale = document["Resolution"][0].GetFloat() / 384.f;
    FPS = document["FrameLimit"].GetInt();
    Resolution[0] = document["Resolution"][0].GetInt();
    Resolution[1]=document["Resolution"][1].GetInt();
    MainMenuBgmVolume = document["MainMenuBgmVolume"].GetFloat();
    InGameBgmVolume = document["InGameBgmVolume"].GetFloat();
    SoundEffectVolume = document["SoundEffectVolume"].GetFloat();
    ShowPlayerNameInGame = document["ShowPlayerNameInGame"].GetBool();
    MaxPlayer = document["MaxPlayer"].GetInt();
}

void GameConfig::saveConfig() {}

GameConfig &GameConfig::getInstance() {
    static GameConfig instance;
    return instance;
}