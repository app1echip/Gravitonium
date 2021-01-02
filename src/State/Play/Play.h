#ifndef GRAVITONIUM_PLAY_H
#define GRAVITONIUM_PLAY_H

#include "../../State.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <Box2D/Box2D.h>
#include "Object/Map.h"
#include "Object/Character.h"
#include "../Widget.h"

class Play : public State {
protected:
    std::string mID;
    enum Status {
        SelectMap, SelectCharacter, Playing
    };
    Status status;
    b2World world;
    Map map;
    std::unordered_map<std::string, std::unique_ptr<Character>> character;
    std::vector<Widget *> widget;

    void setWidget(const std::string &);

    sf::Sound bgmSelect, bgmPlaying;
    sf::Sprite SelectBgPic;

public:

    Play(Game *);

    virtual void handleInput();

    virtual void update(float);

    virtual void draw() const;

    void addCharacter(const std::string &);

    void handleInputSelectMap();

    void handleInputSelectCharacter();

    virtual void handleInputPlaying();

    void updateSelectMap(float);

    void updateSelectCharacter(float);

    void updatePlaying(float);

    void drawSelectMap() const;

    void drawSelectCharacter() const;

    void drawPlaying() const;
};

#endif //GRAVITONIUM_PLAY_H