#ifndef GRAVITONIUM_BULLET_H
#define GRAVITONIUM_BULLET_H

#include "BaseObject.h"

class Bullet : public BaseObject {
private:
    float speed;
public:
    Bullet(b2World *, const b2Vec2 &, Direction, float);
};

#endif //GRAVITONIUM_BULLET_H