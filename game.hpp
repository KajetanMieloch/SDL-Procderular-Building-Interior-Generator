#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

class Game {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    bool isRunning;
    SDL_Texture* start;
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;

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
    void drawText(const char* text, int x, int y, int w, int h);
    bool getRunning();
    void setRunning(bool running);
};


#endif /* GAME_HPP */
