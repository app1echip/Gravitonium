#ifndef GRAVITONIUM_BASEOBJECT_H
#define GRAVITONIUM_BASEOBJECT_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class BaseObject : public sf::Drawable {
public:
    enum Direction {
        Left, Right, Up, Down
    };
    static constexpr float PPM = 32;

    BaseObject(b2World *);

    virtual void update();

    virtual void loadBody(const std::string &, const b2Vec2 & = b2Vec2(0, 0), const b2Vec2 & = b2Vec2(0, 0));

    void setFacing(Direction);

protected:
    b2Body *mBody;
    sf::Sprite mSprite;
    b2World *ownerWorld;
    std::vector<BaseObject *> mAttached;
    std::string label;
    Direction facing = Direction::Right;
    int horizontalIndex[2] = {-1, 1};
    bool offGround = true;
    bool downThrough = false;
    float boxHeight;
    bool respawn = false;

private:
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const;

    friend class ContactListener;

    friend class Client;

    friend class Server;
};

#endif //GRAVITONIUM_BASEOBJECT_H