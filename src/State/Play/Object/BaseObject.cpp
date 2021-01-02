#include "BaseObject.h"
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>

BaseObject::BaseObject(b2World *pWorld) : ownerWorld(pWorld) {}

void BaseObject::setFacing(BaseObject::Direction direction) { facing = direction; }

void BaseObject::update() {
    mSprite.setPosition(mBody->GetPosition().x * PPM, mBody->GetPosition().y * PPM);
    mSprite.setScale(horizontalIndex[facing], 1.f);
    for (auto &item:mAttached)
        item->update();
}

void BaseObject::draw(sf::RenderTarget &target, sf::RenderStates) const {
    target.draw(mSprite);
    for (auto &item:mAttached)
        target.draw(*item);
}

void BaseObject::loadBody(const std::string &pLabel, const b2Vec2 &pPos, const b2Vec2 &pSize) {
    label = pLabel;

    FILE *fp = fopen("data/Object/BaseObject.json", "rb");
    char buffer[UINT16_MAX];
    rapidjson::FileReadStream is(fp, buffer, sizeof(buffer));
    fclose(fp);
    rapidjson::Document doc;
    doc.ParseStream(is);

    for (auto &item:doc.GetArray()) {
        if (item["label"].GetString() == label) {
            if (!item["fixtureOnly"].GetBool()) {
                b2BodyDef bodyDef;
                bodyDef.position.Set((item["origin"][0].GetFloat() + pPos.x) / PPM,
                                     (item["origin"][1].GetFloat() + pPos.y) / PPM);
                bodyDef.fixedRotation = item["bodyFixedRotation"].GetBool();
                bodyDef.bullet = item["bodyBullet"].GetBool();
                std::string typeAsStr = item["bodyType"].GetString();
                if (typeAsStr == "dynamic") bodyDef.type = b2_dynamicBody;
                else if (typeAsStr == "kinematic") bodyDef.type = b2_kinematicBody;
                else bodyDef.type = b2_staticBody;
                mBody = ownerWorld->CreateBody(&bodyDef);
            }
            b2PolygonShape shape;
            shape.SetAsBox((item["size"][0].GetFloat() + pSize.x) * 0.5 / PPM,
                           ((boxHeight = item["size"][1].GetFloat()) + pSize.y) * 0.5 / PPM);
            b2FixtureDef fixtureDef;
            fixtureDef.shape = &shape;
            fixtureDef.density = item["fixtureDensity"].GetFloat();
            fixtureDef.friction = item["fixtureFriction"].GetFloat();
            fixtureDef.userData = this;
            mBody->CreateFixture(&fixtureDef);
            break;
        }
    }
}