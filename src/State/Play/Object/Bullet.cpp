#include "Bullet.h"
#include "../../../Resource/ResourceManager/TextureManager.h"

Bullet::Bullet(b2World *pWorld, const b2Vec2 &pPos, Direction pFacing, float speed) : BaseObject(pWorld) {
    float v = (speed - 20) * horizontalIndex[pFacing];
    float shift = 8.1f / PPM * horizontalIndex[pFacing];

    auto &textureManager = TextureManager::getInstance();
    mSprite.setTexture(textureManager.getTexture("bullet"));
    mSprite.setTextureRect(sf::IntRect(0, 0, 2, 1));
    mSprite.setOrigin(1.f, 0.5f);

    loadBody("Bullet", b2Vec2(pPos.x * PPM + shift * PPM, pPos.y * PPM));
    mBody->ApplyLinearImpulseToCenter(mBody->GetMass() * b2Vec2(v, 0), true);
}