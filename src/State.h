#ifndef GRAVITONIUM_STATE_H
#define GRAVITONIUM_STATE_H

#include "Game.h"

class State {
protected:
    Game *game;
public:
    virtual void handleInput() = 0;

    virtual void update(float) = 0;

    virtual void draw() const = 0;
};

#endif //GRAVITONIUM_STATE_H