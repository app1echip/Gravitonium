#include "Help.h"
#include "../Resource/ResourceManager/TextureManager.h"

Help::Help(Game *pGame) {
    game = pGame;
    auto &texmgr = TextureManager::getInstance();
    helpPage.setTexture(texmgr.getTexture("HelpPage"));
}

void Help::handleInput() {
    sf::Event event;
    while (game->window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                game->window.close();
                break;
            case sf::Event::MouseButtonPressed:
                game->popState();
                return;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        game->popState();
                        return;
                }
                break;
        }
    }
}

void Help::update(float dt) {}

void Help::draw() const {
    game->window.draw(helpPage);
}