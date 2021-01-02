#ifndef GRAVITONIUM_HELP_H
#define GRAVITONIUM_HELP_H

#include "../State.h"

class Help : public State {
    sf::Sprite helpPage;
public:
    Help(Game *);

    virtual void handleInput();

    virtual void update(float);

    virtual void draw() const;
};


#endif //GRAVITONIUM_HELP_H
