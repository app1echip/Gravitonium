#ifndef GRAVITONIUM_GAMECONFIG_H
#define GRAVITONIUM_GAMECONFIG_H

class GameConfig {
private:
    GameConfig();

    ~GameConfig();

public:
    static GameConfig &getInstance();

    void loadConfig();

    void saveConfig();

    bool Fullscreen;
    int Resolution[2];
    float FPS;
    float Scale;
    float MainMenuBgmVolume;
    float InGameBgmVolume;
    float SoundEffectVolume;
    bool ShowPlayerNameInGame;
    int MaxPlayer;
};


#endif //GRAVITONIUM_GAMECONFIG_H
