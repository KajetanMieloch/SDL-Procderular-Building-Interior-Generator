#include "hud.hpp"

std::string textRightPanel = "Displaying layer: ";

HUD::HUD(SDL_Renderer* renderer, SDL_Window* window) {
    this->renderer = renderer;
    this->window = window;
    // Other initialization code...
}

HUD::~HUD() {
    // Clean up code...
}

void HUD::init() {
    // Other initialization code...
}

void HUD::changeLayer(int layer, SDL_Surface*& textLayer) {
    if (layer == 1) {
        textRightPanel = "Displaying layer: 1";
        textLayer = TTF_RenderText_Solid(font, textRightPanel.c_str(), {255, 255, 255, 255});
        renderLayer = 1;
    } else if (layer == 2) {
        textRightPanel = "Displaying layer: 2";
        textLayer = TTF_RenderText_Solid(font, textRightPanel.c_str(), {255, 255, 255, 255});
        renderLayer = 2;
    } else if (layer == 3) {
        textRightPanel = "Displaying layer: All Layers";
        textLayer = TTF_RenderText_Solid(font, textRightPanel.c_str(), {255, 255, 255, 255});
        renderLayer = 3;
    }
}

void HUD::generateHUD() {

    TTF_Font* font = TTF_OpenFont("res/Arial.ttf", 30);

    //Generate gray background of the HUD
    int windowHeight;
    int windowWidth;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    int hudHeight = 80;
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

    // Create the text surface
    SDL_Color textColor = {255, 255, 255, 255}; // White color
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "1", textColor);

    // Create the text texture
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    // Calculate the position of the text
    SDL_Rect textRect;
    textRect.x = buttonRect.x + (buttonRect.w - textSurface->w) / 2; // Center the text horizontally
    textRect.y = buttonRect.y + (buttonRect.h - textSurface->h) / 2; // Center the text vertically
    textRect.w = textSurface->w;
    textRect.h = textSurface->h;

    // Render the text
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    // Clean up
    SDL_FreeSurface(textSurface);


    //Button 2
    SDL_Rect buttonRect2 = {120, hudY + 10, 100, 60};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &buttonRect2);
    SDL_Color textColor2 = {255, 255, 255, 255}; // White color
    SDL_Surface* textSurface2 = TTF_RenderText_Solid(font, "2", textColor2);
    SDL_Texture* textTexture2 = SDL_CreateTextureFromSurface(renderer, textSurface2);
    SDL_Rect textRect2;
    textRect2.x = buttonRect2.x + (buttonRect2.w - textSurface2->w) / 2; // Center the text horizontally
    textRect2.y = buttonRect2.y + (buttonRect2.h - textSurface2->h) / 2; // Center the text vertically
    textRect2.w = textSurface2->w;
    textRect2.h = textSurface2->h;
    SDL_RenderCopy(renderer, textTexture2, NULL, &textRect2);
    SDL_FreeSurface(textSurface2);

    //Button 3

    SDL_Rect buttonRect3 = {230, hudY + 10, 100, 60};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &buttonRect3);
    SDL_Color textColor3 = {255, 255, 255, 255}; // White color
    SDL_Surface* textSurface3 = TTF_RenderText_Solid(font, "All Layers", textColor3);
    SDL_Texture* textTexture3 = SDL_CreateTextureFromSurface(renderer, textSurface3);
    SDL_Rect textRect3;
    textRect3.x = buttonRect3.x + (buttonRect3.w - textSurface3->w) / 2; // Center the text horizontally
    textRect3.y = buttonRect3.y + (buttonRect3.h - textSurface3->h) / 2; // Center the text vertically
    textRect3.w = textSurface3->w;
    textRect3.h = textSurface3->h;
    SDL_RenderCopy(renderer, textTexture3, NULL, &textRect3);
    SDL_FreeSurface(textSurface3);


    //Max right display text
    SDL_Color textColor4 = {255, 255, 255, 255}; // White color
    SDL_Surface* textLayer = TTF_RenderText_Solid(font, textRightPanel.c_str(), textColor4);
    SDL_Texture* textTexture4 = SDL_CreateTextureFromSurface(renderer, textLayer);
    SDL_Rect textRect4;
    textRect4.x = windowWidth - textLayer->w - 10; // Center the text horizontally
    textRect4.y = hudY + 10; // Center the text vertically
    textRect4.w = textLayer->w;
    textRect4.h = textLayer->h;
    SDL_RenderCopy(renderer, textTexture4, NULL, &textRect4);
    SDL_FreeSurface(textLayer);

    // Clean up
    TTF_CloseFont(font);


    int mouseX, mouseY;
    if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        if (mouseX >= buttonRect.x && mouseX <= buttonRect.x + buttonRect.w &&
            mouseY >= buttonRect.y && mouseY <= buttonRect.y + buttonRect.h) {
            // Mouse is over buttonRect
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            SDL_RenderDrawRect(renderer, &buttonRect);
            changeLayer(1, textLayer);
        }

        if (mouseX >= buttonRect2.x && mouseX <= buttonRect2.x + buttonRect2.w &&
            mouseY >= buttonRect2.y && mouseY <= buttonRect2.y + buttonRect2.h) {
            // Mouse is over buttonRect2
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            SDL_RenderDrawRect(renderer, &buttonRect2);
            changeLayer(2, textLayer);
        }

        if (mouseX >= buttonRect3.x && mouseX <= buttonRect3.x + buttonRect3.w &&
            mouseY >= buttonRect3.y && mouseY <= buttonRect3.y + buttonRect3.h) {
            // Mouse is over buttonRect3
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            SDL_RenderDrawRect(renderer, &buttonRect3);
            changeLayer(3, textLayer);
        }
    }

}