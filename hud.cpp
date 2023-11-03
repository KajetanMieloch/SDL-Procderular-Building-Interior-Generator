#include "hud.hpp"

HUD::HUD(SDL_Renderer* renderer, SDL_Window* window) {
    this->renderer = renderer;
    this->window = window;
    // Other initialization code...
}

void HUD::generateHUD() {

    //Generate gray background of the HUD
    int windowHeight;
    int windowWidth;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    int hudHeight = 80; // Replace with the actual height of your hud
    int hudY = windowHeight - hudHeight;

    SDL_Rect hudRect = {0, hudY, windowWidth, hudHeight};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &hudRect);
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    SDL_RenderFillRect(renderer, &hudRect);


    //Generate the buttons

    //Button 1
    SDL_Rect buttonRect = {10, hudY + 10, 100, 60};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &buttonRect);

    //Button 2
    SDL_Rect buttonRect2 = {120, hudY + 10, 100, 60};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &buttonRect2);


    int mouseX, mouseY;
    if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        if (mouseX >= buttonRect.x && mouseX <= buttonRect.x + buttonRect.w &&
            mouseY >= buttonRect.y && mouseY <= buttonRect.y + buttonRect.h) {
            // Mouse is over buttonRect
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            SDL_RenderDrawRect(renderer, &buttonRect);
        }

        if (mouseX >= buttonRect2.x && mouseX <= buttonRect2.x + buttonRect2.w &&
            mouseY >= buttonRect2.y && mouseY <= buttonRect2.y + buttonRect2.h) {
            // Mouse is over buttonRect2
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            SDL_RenderDrawRect(renderer, &buttonRect2);
        }
    }




}