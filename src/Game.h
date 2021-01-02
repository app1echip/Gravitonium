#ifndef GRAVITONIUM_GAME_H
#define GRAVITONIUM_GAME_H

#include <stack>
#include <SFML/Graphics.hpp>
#include "GameConfig.h"
#include "Resource/ResourceManager.h"

class State;

class Game {
private:
    std::stack<State *> state;

public:
    GameConfig &config = GameConfig::getInstance();
    ResourceManager &resmgr = ResourceManager::getInstance();

    sf::RenderWindow window;
    sf::View view;

    Game();

    ~Game();

    void pushState(State *);

    void popState();

    State *topState();

    void run();
};

#endif //GRAVITONIUM_GAME_H