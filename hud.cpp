#include "hud.hpp"

HUD::HUD(SDL_Renderer* renderer, SDL_Window* window) {
    this->renderer = renderer;
    this->window = window;
    // Other initialization code...
}

void HUD::generateHUD() {
    int windowHeight;
    int windowWidth;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    // Calculate the y position of the hud
    int hudHeight = 80; // Replace with the actual height of your hud
    int hudY = windowHeight - hudHeight;

    SDL_Rect hudRect = {0, hudY, windowWidth, hudHeight};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &hudRect);
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    SDL_RenderFillRect(renderer, &hudRect);

}