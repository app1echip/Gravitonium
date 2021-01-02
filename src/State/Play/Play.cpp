#include "Play.h"
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include "Physics/ContactListener.h"
#include "../../Resource/ResourceManager/SoundManager.h"
#include "../../Resource/ResourceManager/TextureManager.h"

extern const float WindowScale;

Play::Play(Game *pGame) : world(b2Vec2(0.f, 9.8f)), map(&world), status(Play::Status::SelectMap) {
    world.SetContactListener(new ContactListener);
    game = pGame;
    setWidget("SelectMap");
    auto &soundManger = SoundManager::getInstance();
    bgmSelect.setBuffer(soundManger.getSound("SelectBgm"));
    bgmSelect.play();
    auto &textureManager = TextureManager::getInstance();
    SelectBgPic.setTexture(textureManager.getTexture("SelectBackground"));
}

void Play::handleInput() {
    switch (status) {
        case Play::Status::SelectMap:
            handleInputSelectMap();
            break;
        case Play::Status::SelectCharacter:
            handleInputSelectCharacter();
            break;
        case Play::Status::Playing:
            handleInputPlaying();
            break;
    }
}

void Play::handleInputSelectMap() {
    sf::Event event;
    while (game->window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                game->window.close();
                break;
            case sf::Event::MouseButtonPressed:
                auto mousePos = sf::Mouse::getPosition(game->window);
                mousePos = sf::Vector2i(mousePos.x / WindowScale, mousePos.y / WindowScale);
                for (const auto &item:widget)
                    if (item->contain(mousePos)) {
                        map.setMap(item->getMessage());
                        status = Play::Status::SelectCharacter;
                        setWidget("SelectCharacter");
                        break;
                    }
                break;
        }
    }
}

void Play::handleInputSelectCharacter() {
    sf::Event event;
    while (game->window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                game->window.close();
                break;
            case sf::Event::MouseButtonPressed:
                auto mousePos = sf::Mouse::getPosition(game->window);
                mousePos = sf::Vector2i(mousePos.x / WindowScale, mousePos.y / WindowScale);
                for (const auto &item:widget)
                    if (item->contain(mousePos)) {
                        mID = "Pedro";
                        if (character.find(mID) == character.end()) {
                            addCharacter(mID);
                            character[mID]->setCharacter(item->getMessage(), "SMG");
                        }
                        status = Playing;
                        setWidget("Play");
                        break;
                    }
                break;
        }
    }
}

void Play::handleInputPlaying() {
    sf::Event event;
    while (game->window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                game->window.close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::W:
                    case sf::Keyboard::Space:
                        character["Pedro"]->move(Character::Direction::Up);
                        break;
                    case sf::Keyboard::A:
                        character["Pedro"]->move(Character::Direction::Left);
                        break;
                    case sf::Keyboard::D:
                        character["Pedro"]->move(Character::Direction::Right);
                        break;
                    case sf::Keyboard::S:
                        character["Pedro"]->move(Character::Direction::Down);
                        break;
                    case sf::Keyboard::K:
                        character["Pedro"]->shoot();
                        break;
                    case sf::Keyboard::Escape:
                        game->popState();
                        return;
                }
                break;
        }
    }
}

void Play::update(float dt) {
    switch (status) {
        case Play::Status::SelectMap:
            updateSelectMap(dt);
            break;
        case Play::Status::SelectCharacter:
            updateSelectCharacter(dt);
            break;
        case Play::Status::Playing:
            updatePlaying(dt);
            break;
    }
}

void Play::updateSelectMap(float dt) {
    auto mousePos = sf::Mouse::getPosition(game->window);
    mousePos = sf::Vector2i(mousePos.x / WindowScale, mousePos.y / WindowScale);
    for (const auto &item:widget) {
        if (item->contain(mousePos)) {
            auto previewName = item->getMessage();
            widget[0]->setTexture(previewName);
            widget[0]->boxVisible = true;
        }
    }
}

void Play::updateSelectCharacter(float dt) {

}

void Play::updatePlaying(float dt) {
    world.Step(dt, 8, 3);
    for (auto &single:character)
        single.second->update();
}

void Play::draw() const {
    switch (status) {
        case Play::Status::SelectMap:
            drawSelectMap();
            break;
        case Play::Status::SelectCharacter:
            drawSelectCharacter();
            break;
        case Play::Status::Playing:
            drawPlaying();
            break;
    }
}

void Play::drawSelectMap() const {
    game->window.draw(SelectBgPic);
    for (const auto &item:widget)
        game->window.draw(*item);
}

void Play::drawSelectCharacter() const {
    for (const auto &item:widget)
        game->window.draw(*item);
}

void Play::drawPlaying() const {
    game->window.draw(map);
    for (const auto &single:character)
        game->window.draw(*single.second);
    for (const auto &item:widget)
        game->window.draw(*item);
}

void Play::addCharacter(const std::string &name) {
    character.insert(std::make_pair(name, std::make_unique<Character>(&world)));
}

void Play::setWidget(const std::string &statusName) {
    widget.clear();

    auto filePath = "data/Layout/" + statusName + ".json";
    FILE *fp = fopen(filePath.c_str(), "rb");
    char buffer[UINT16_MAX];
    rapidjson::FileReadStream is(fp, buffer, sizeof(buffer));
    fclose(fp);
    rapidjson::Document document;
    document.ParseStream(is);

    for (auto &item:document.GetArray()) {
        auto posX = item["position"][0].GetFloat();
        auto posY = item["position"][1].GetFloat();
        auto width = item["boxSize"][0].GetFloat();
        auto height = item["boxSize"][1].GetFloat();
        auto fontFace = item["fontFace"].GetString();
        auto fontSize = item["fontSize"].GetFloat();
        auto message = item["message"].GetString();
        auto call = item["call"].GetInt();
        auto ptr = new Widget(sf::Vector2f(posX, posY), sf::Vector2f(width, height), fontFace, fontSize,
                              message, call);
        widget.push_back(ptr);
    }
}