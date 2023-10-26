#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "grid.hpp"

class Game {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    Grid* grid;
    bool isRunning;
    SDL_Texture* start;
    const int FPS = 60;
    const double frameDelay = 1000.0 / FPS;
    Uint64 lastFrameTime;
    int cameraX;
    int cameraY;

public:
    Game();
    ~Game();
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    SDL_Renderer* getRenderer();
    TTF_Font* getFont();
    void handleEvents();
    void update();
    void render();
    void clean();
    void run();
    bool getRunning() { return isRunning; }
    void setRunning(bool running) { isRunning = running; }
};


#endif /* GAME_HPP */
