#include "Game.h"
#include "State/MainMenu.h"

int main() {
    Game game;
    game.pushState(new MainMenu(&game));
    game.run();
    return 0;
}