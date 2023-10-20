#ifndef MENU_HPP
#define MENU_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Menu {
public:
    Menu(SDL_Renderer* renderer, TTF_Font* font);
    ~Menu();

    void render();
    void handleEvents(SDL_Event& event);

    bool isMenuRunning() {
        return isRunning;
    }
    bool quitGame() {
        return quit;
    }

private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Rect playButton;
    SDL_Rect quitButton;
    SDL_Color textColor;

    bool isRunning;
    bool quit;

    void drawText(const char* text, int x, int y, int w, int h);
};

#endif // MENU_HPP
