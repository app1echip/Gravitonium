#include "Game.h"
#include "State.h"

extern const int FPS = 60;
extern const float WindowScale = 5.f;

Game::Game() {
    auto resolution = sf::VideoMode(config.Resolution[0], config.Resolution[1]);
    auto style = config.Fullscreen ? sf::Style::Fullscreen : sf::Style::Close | sf::Style::Titlebar;
    window.create(resolution, "Gravitonium", style);
    window.setFramerateLimit(config.FPS);
    view = window.getDefaultView();
    view.setViewport(sf::FloatRect(0.f, 0.f, config.Scale, config.Scale));
    window.setView(view);
}

Game::~Game() { while (!state.empty()) popState(); }

void Game::pushState(State *pState) { state.push(pState); }

void Game::popState() {
    if (!state.empty()) {
        delete state.top();
        state.pop();
    }
}

State *Game::topState() { return state.empty() ? nullptr : state.top(); }

void Game::run() {
    sf::Clock clock;
    sf::Time elapsedTime = sf::Time::Zero;
    const sf::Time frameTime = sf::seconds(1.f / FPS);
    while (window.isOpen()) {
        elapsedTime += clock.restart();
        while (elapsedTime >= frameTime) {
            elapsedTime -= frameTime;
            window.clear();
            topState()->handleInput();
            topState()->update(frameTime.asSeconds());
            topState()->draw();
            window.display();
        }
    }
}