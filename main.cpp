#include "game.hpp"
#include "menu.hpp"
#include <iostream>

Game* game = NULL;
Menu* mainMenu = NULL;
bool inMenu = true;  // Initially, we start in the menu
SDL_Event event;

int main(int argc, const char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);

    game = new Game();
    game->init("Interior generator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, true);


    mainMenu = new Menu(game->getRenderer(), game->getFont());

    while (game->getRunning()) {
        while (SDL_PollEvent(&event)) {
            if (inMenu) {
                mainMenu->handleEvents(event);
                mainMenu->render();
                if (!mainMenu->isMenuRunning()) {
                    inMenu = false;  // Exit the menu
                    game->setRunning(true);  // Start the game
                }
                if (mainMenu->quitGame()) {
                    game->setRunning(false);  // Quit the game
                }
            } else {
                game->run();
                game->handleEvents();
                game->update();
                game->render();
            }
        }
    }

    game->clean();
    SDL_Quit();

    delete game;
    delete mainMenu;

    return 0;
}
