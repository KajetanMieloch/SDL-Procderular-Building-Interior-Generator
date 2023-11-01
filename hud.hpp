#ifndef HUD_HPP
#define HUD_HPP

#include <SDL2/SDL.h>

class HUD {
private:
    SDL_Renderer* renderer;
public:
    HUD(SDL_Renderer* renderer);
    ~HUD();
    void init();
    void generateHUD();
};

#endif /* HUD_HPP */