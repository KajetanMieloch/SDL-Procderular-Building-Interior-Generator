#include "game.hpp"
#include <string>
#include <iostream>
#include <sstream>


Game::Game() {}
Game::~Game() {}

int cnt = 0;


void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
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
        if (TTF_Init() == -1) {
            // Handle TTF initialization failure
            std::cerr << "Failed to initialize TTF: " << TTF_GetError() << std::endl;
        } else {
            font = TTF_OpenFont("res/Arial.ttf", 30);
            if (!font) {
                // Handle font loading failure
                std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
            }
        }
    } else {
        isRunning = false;
    }

    start = IMG_LoadTexture(renderer, "res/start.png");
}

SDL_Renderer* Game::getRenderer() {
    return renderer;
}

TTF_Font* Game::getFont() {
    return font;
}
void Game::setRunning(bool running) {
    isRunning = running;
}

bool Game::getRunning() {
    return isRunning;
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
    // Add game logic here
}

void Game::drawText(const char* text, int x, int y, int w, int h) {
    SDL_Rect rect = { x, y, w, h };
    SDL_Color textColor = { 0, 0, 0, 255 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}


// Declare these variables as member variables of the Game class
int frameCount = 0;
Uint32 lastFrameTime = 0;
int fps = 0;

// Update the render function to calculate the FPS
void Game::render() {
    // Calculate the time elapsed since the last frame
    Uint32 currentFrameTime = SDL_GetTicks();
    Uint32 frameTime = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;

    // Increment the frame count
    frameCount++;

    // Update the FPS every second
    if (frameTime >= 1000) {
        fps = frameCount * 1000 / frameTime;
        frameCount = 0;
    }

    // Render the game
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, start, NULL, NULL);

    std::stringstream ss;
    ss << "FPS: " << fps;
    drawText(ss.str().c_str(), 10, 10, 100, 50);

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    TTF_CloseFont(font);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned!" << std::endl;
}