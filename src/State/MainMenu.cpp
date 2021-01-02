#include "MainMenu.h"
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <chrono>
#include "Play/Play.h"
#include "MultiPlay/Server.h"
#include "MultiPlay/Client.h"
#include "Help.h"
#include "../Resource/ResourceManager/TextureManager.h"
#include "../Resource/ResourceManager/SoundManager.h"

extern const float WindowScale;

MainMenu::MainMenu(Game *pGame) {
    game = pGame;

    FILE *fp = fopen("data/Layout/MainMenu.json", "rb");
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
        widget.push_back(std::move(ptr));
    }

    srand((unsigned int) (std::time(nullptr)));
    auto selected = rand() % 7+1;
    auto &textureManager = TextureManager::getInstance();
    background.setTexture(textureManager.getTexture("BG" + std::to_string(selected)));

    auto &soundManger = SoundManager::getInstance();
    bgm.setBuffer(soundManger.getSound("MainMenuBgm"));
    bgm.setVolume(30.f);
    bgm.setLoop(true);
    bgm.play();
    moveOver.setBuffer(soundManger.getSound("MoveOver"));
}

void MainMenu::handleInput() {
    sf::Event event;
    while (game->window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                game->window.close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        game->window.close();
                        break;
                }
                break;
            case sf::Event::MouseButtonPressed:
                auto mousePos = sf::Mouse::getPosition(game->window);
                mousePos = sf::Vector2i(mousePos.x / WindowScale, mousePos.y / WindowScale);
                for (const auto &item:widget)
                    if (item->contain(mousePos)) {
                        switch (item->call) {
                            case 0:
                                bgm.pause();
                                game->pushState(new Play(game));
                                break;
                            case 1:
                                game->pushState(new Server(game));
                                break;
                            case 2:
                                game->pushState(new Client(game));
                                break;
                            case 3:
                                system("explorer.exe data\\GameConfig.json");
                                break;
                            case 4:
                                game->pushState(new Help(game));
                                break;
                            case 5:
                                game->window.close();
                                break;
                        }
                        break;
                    }
                break;
        }
    }
}

void MainMenu::update(float) {
    auto mousePos = sf::Mouse::getPosition(game->window);
    mousePos = sf::Vector2i(mousePos.x / WindowScale, mousePos.y / WindowScale);
    for (const auto &item:widget) {
        item->boxVisible = item->contain(mousePos);
    }
}

void MainMenu::draw() const {
    game->window.draw(background);
    for (const auto &item:widget)
        game->window.draw(*item);
}