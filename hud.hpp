#ifndef HUD_HPP
#define HUD_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <string>

class HUD {
private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    int renderLayer = 3;
public:
    SDL_Window* window;
    HUD(SDL_Renderer* renderer, SDL_Window* window);
    ~HUD();
    void init();
    void generateHUD();
    int returnHudY();
    int returnHudWidth();
    void changeLayer(int layer, SDL_Surface*& textLayer);

    int getRenderLayer() const {
        return renderLayer;
    }

};

#endif /* HUD_HPP */