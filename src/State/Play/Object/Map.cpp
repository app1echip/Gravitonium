//
// Created by aya on 6/29/2019.
//

#include "Map.h"
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include "../../../Resource/ResourceManager/TextureManager.h"

Map::Map(b2World *pWorld) : BaseObject(pWorld) {}

void Map::setMap(const std::string &pMap) {
    mName = pMap;

    FILE *fp = fopen("data/Object/Map.json", "rb");
    char buf[UINT16_MAX];
    rapidjson::FileReadStream is(fp, buf, sizeof(buf));
    fclose(fp);
    rapidjson::Document doc;
    doc.ParseStream(is);

    for (auto &mapItem:doc.GetArray())
        if (mapItem["name"].GetString() == mName) {
            for (auto &item:mapItem["platform"].GetArray()) {
                b2Vec2 size(item["size"][0].GetFloat(), item["size"][1].GetFloat());
                b2Vec2 origin(item["origin"][0].GetFloat(), item["origin"][1].GetFloat());
                BaseObject *p = new BaseObject(ownerWorld);
                p->loadBody("Platform", origin, size);
                mAttached.push_back(p);
            }
            break;
        }

    loadBody("Ground");
    TextureManager &texMgr = TextureManager::getInstance();
    mSprite.setTexture(texMgr.getTexture(mName));
}

void Map::update() {}

std::string Map::getMapName() const { return mName; }