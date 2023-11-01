#include "hud.hpp"

HUD::HUD(SDL_Renderer* renderer) {
    this->renderer = renderer;
    // Other initialization code...
}

void HUD::generateHUD() {
    SDL_Rect hudRect;
    hudRect.x = 0;
    hudRect.y = 0;
    hudRect.w = 800;
    hudRect.h = 50;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &hudRect);
}