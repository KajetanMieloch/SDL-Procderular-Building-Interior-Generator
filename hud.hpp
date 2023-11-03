#ifndef HUD_HPP
#define HUD_HPP

#include <SDL2/SDL.h>

class HUD {
private:
    SDL_Renderer* renderer;
public:
    SDL_Window* window;
    HUD(SDL_Renderer* renderer, SDL_Window* window);
    ~HUD();
    void init();
    void generateHUD();
    int returnHudY();
    int returnHudWidth();
};

#endif /* HUD_HPP */