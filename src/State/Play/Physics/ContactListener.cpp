#include "ContactListener.h"
#include "../Object/BaseObject.h"

void ContactListener::BeginContact(b2Contact *) {}

void ContactListener::EndContact(b2Contact *) {

}

void ContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *) {
    auto dataA = static_cast<BaseObject *>(contact->GetFixtureA()->GetUserData());
    auto dataB = static_cast<BaseObject *>(contact->GetFixtureB()->GetUserData());
    dataA->offGround = false, dataB->offGround = false;
}

void ContactListener::PreSolve(b2Contact *contact, const b2Manifold *) {
    auto dataA = static_cast<BaseObject *>(contact->GetFixtureA()->GetUserData());
    auto dataB = static_cast<BaseObject *>(contact->GetFixtureB()->GetUserData());

    BaseObject *moving, *still;
    if (dataA->label == "Ground" || dataA->label == "Platform") still = dataA, moving = dataB;
    else if (dataB->label == "Ground" || dataB->label == "Platform") still = dataB, moving = dataA;
    else return;

    if (still->label == "Ground" && moving->label == "Character") {
        moving->respawn = true;
        return;
    }

    auto isOneWay = moving->mBody->GetPosition().y + (moving->boxHeight + still->boxHeight) / 2.f / moving->PPM <
                    still->mBody->GetPosition().y;
    contact->SetEnabled(isOneWay);
    if (moving->label == "Weapon") contact->SetEnabled(false);
    if (moving->downThrough == true) contact->SetEnabled(false), moving->downThrough = false;
}