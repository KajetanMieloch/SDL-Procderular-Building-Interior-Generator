#include "game.hpp"
#include <string>
#include <iostream>
#include <sstream>


Game::Game() {}
Game::~Game() {}

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
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
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

    // Initialize the camera position to (0, 0)
    cameraX = 0;
    cameraY = 0;

    // Initialize the last frame time to the current time
    lastFrameTime = SDL_GetPerformanceCounter();
}

SDL_Renderer* Game::getRenderer() {
    return renderer;
}

void Game::run() {
    Uint64 lastFrameTime = SDL_GetPerformanceCounter();
    while (isRunning) {
        handleEvents(); // Call handleEvents() at the beginning of each frame
        update();
        render();

        // Calculate the time elapsed since the last frame
        Uint64 currentFrameTime = SDL_GetPerformanceCounter();
        double frameTime = (currentFrameTime - lastFrameTime) * 1000.0 / SDL_GetPerformanceFrequency();
        lastFrameTime = currentFrameTime;

        // Delay the loop if necessary to maintain the desired frame rate
        if (frameTime < frameDelay) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    clean();
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
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                case SDLK_a: // Detect the 'A' key
                    // Move the camera left
                    cameraX -= 10;
                    break;
                case SDLK_RIGHT:
                case SDLK_d: // Detect the 'D' key
                    // Move the camera right
                    cameraX += 10;
                    break;
                case SDLK_UP:
                case SDLK_w: // Detect the 'W' key
                    // Move the camera up
                    cameraY -= 10;
                    break;
                case SDLK_DOWN:
                case SDLK_s: // Detect the 'S' key
                    // Move the camera down
                    cameraY += 10;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void Game::update() {
    // Add game logic here
}

void Game::render() {
    // Get the current time
    Uint64 currentFrameTime = SDL_GetPerformanceCounter();

    // Calculate the time elapsed since the last frame
    double frameTime = (currentFrameTime - lastFrameTime) * 1000.0 / SDL_GetPerformanceFrequency();
    lastFrameTime = currentFrameTime;

    // Set the background color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Clear the screen
    SDL_RenderClear(renderer);

    // Render the white rectangle in the middle of the screen, adjusted for the camera position
    SDL_Rect rect = { 245 - cameraX, 245 - cameraY, 10, 10 };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);

    // Render the FPS
    std::stringstream ss;
    ss << "FPS: " << 1000.0 / frameTime;

    // Update the screen
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    TTF_CloseFont(font);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned!" << std::endl;
}