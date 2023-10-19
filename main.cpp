#include "game.hpp"
#include "game.cpp"


Game *game = NULL;
SDL_Texture* start;


int main(int argc, const char* argv[]) {

    game = new Game();
    
    game->init("Interior generator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

    while (game->running()) {
        game->handleEvents();
        game->update();
        game->render();
    }

    game->clean();

    return 0;
}
