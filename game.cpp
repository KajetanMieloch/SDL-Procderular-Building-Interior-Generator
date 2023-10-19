#include "game.hpp"

Game::Game() {}
Game::~Game() {}

int cnt = 0;


void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Subsystems initialized..." << std::endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window) {
            std::cout << "Window created!" << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created!" << std::endl;
        }
        isRunning = true;
        font = TTF_OpenFont("res/arial.ttf", 24);
        if (!font) {
            // Handle font loading failure
            std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        }
    } else {
        isRunning = false;
    }

    SDL_Surface* tmpSurface = IMG_Load("src/start.png");
    start = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
}

//Game renderer
SDL_Renderer* Game::getRenderer() {
    return renderer;
}

TTF_Font* Game::getFont() {
    return font;
}


void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

void Game::update() {
    cnt++;
}

void Game::render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, start, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    TTF_CloseFont(font); // Close the font when you're done with it
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned!" << std::endl;
}
