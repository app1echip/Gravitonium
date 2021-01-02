#include "Character.h"
#include <string>
#include "../../../Resource/ResourceManager/TextureManager.h"

Character::Character(b2World *pWorld) : BaseObject(pWorld), weapon(pWorld) {}

void Character::setCharacter(const std::string &sSkin, const std::string &sWeapon) {
    mSkin = sSkin;
    mWeapon = sWeapon;

    loadBody("Character");

    weapon.loadData(mBody, mWeapon);

    auto &textureManager = TextureManager::getInstance();
    mSprite.setTexture(textureManager.getTexture(mSkin));
    mSprite.setOrigin(8.f, 16.f);

    mAttached.push_back(&weapon);
}

void Character::move(Character::Direction direction) {
    if (respawn) {
        mBody->SetTransform(b2Vec2(100.f / PPM, 0.f), mBody->GetAngle());
        respawn = false;
    }

    const b2Vec2 v0 = mBody->GetLinearVelocity();
    const float horizontalVelocity = 3.f;
    const float verticalVelocityUp = 5.f, verticalVelocityDown = 3.f;

    b2Vec2 v1 = v0;
    if (direction == Left)
        v1.x = -horizontalVelocity, facing = Left, weapon.setFacing(Left);
    else if (direction == Right)
        v1.x = horizontalVelocity, facing = Right, weapon.setFacing(Right);
    else if (direction == Up) {
        if (offGround == false) jumpCount = 0;
        if (jumpCount < jumpLimit)
            v1.y = -verticalVelocityUp, jumpCount++, offGround = true;
    } else
        v1.y = verticalVelocityDown, downThrough = true;

    mBody->ApplyLinearImpulseToCenter(mBody->GetMass() * (v1 - v0), true);
}

void Character::shoot() { weapon.shoot(); }