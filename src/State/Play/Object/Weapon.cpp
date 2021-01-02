#include "Weapon.h"
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include "../../../Resource/ResourceManager/TextureManager.h"
#include "../../../Resource/ResourceManager/SoundManager.h"

Weapon::Weapon(b2World *pWorld) : BaseObject(pWorld) {}

void Weapon::loadData(b2Body *character, const std::string &pWeapon) {
    mBody = character;
    mName = pWeapon;

    FILE *fp = fopen("data/Object/Weapon.json", "rb");
    char buffer[UINT16_MAX];
    rapidjson::FileReadStream is(fp, buffer, sizeof(buffer));
    fclose(fp);
    rapidjson::Document doc;
    doc.ParseStream(is);

    for (auto &item:doc.GetArray())
        if (item["name"].GetString() == mName) {
            const auto x = item["size"][0].GetFloat();
            const auto y = item["size"][1].GetFloat();
            loadBody("Weapon", b2Vec2(0, 0), b2Vec2(x, y));
            damage = item["damage"].GetFloat();
            capacity = item["capacity"].GetInt();
            rof = item["rof"].GetFloat();

            auto &textureManager = TextureManager::getInstance();
            mSprite.setTexture(textureManager.getTexture(mName));
            mSprite.setOrigin(x * 0.5, y * 0.5);
            auto &soundManager = SoundManager::getInstance();
            mGunfire.setBuffer(soundManager.getSound(mName));
            break;
        }
}

void Weapon::shoot() {
    if (lostCapacity < capacity && triggerClock.restart().asSeconds() >= 60.f / rof) {
        auto *piece = new Bullet(ownerWorld, mBody->GetPosition(), facing, damage);
        mGunfire.play();
        bullet.push_back(piece);
        mAttached.push_back(piece);
        lostCapacity++;
    }
}