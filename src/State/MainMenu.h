#ifndef GRAVITONIUM_MAINMENU_H
#define GRAVITONIUM_MAINMENU_H

#include "../State.h"
#include <vector>
#include <SFML/Audio.hpp>
#include "Widget.h"

class MainMenu : public State {
private:
    std::vector<Widget *> widget;
    sf::Sprite background;
    sf::Sound bgm,moveOver;

public:
    virtual void handleInput();

    virtual void update(float);

    virtual void draw() const;

    MainMenu(Game *);
};

#endif //GRAVITONIUM_MAINMENU_H