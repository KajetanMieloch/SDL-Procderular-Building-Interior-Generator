#include "menu.hpp"
#include <iostream>

Menu::Menu(SDL_Renderer* renderer, TTF_Font* font) : renderer(renderer), font(font), isRunning(true) {

    playButton.x = 100;
    playButton.y = 100;
    playButton.w = 200;
    playButton.h = 50;

    quitButton.x = 100;
    quitButton.y = 200;
    quitButton.w = 200;
    quitButton.h = 50;

}

Menu::~Menu() {
    // Clean up any resources if needed
}


void Menu::render() {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Set background color to red
    SDL_RenderClear(renderer);


    drawText("Main Menu", 100, 50, 200, 50);
    drawText("Play", playButton.x, playButton.y, playButton.w, playButton.h);
    drawText("Quit", quitButton.x, quitButton.y, quitButton.w, quitButton.h);

    SDL_RenderPresent(renderer);
}
void Menu::drawText(const char* text, int x, int y, int w, int h) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect destRect = {x, y, w, h};

    SDL_RenderCopy(renderer, textTexture, NULL, &destRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void Menu::handleEvents(SDL_Event& event) {
    if (event.type == SDL_QUIT) {
        isRunning = false;
    }
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            int mouseX = event.button.x;
            int mouseY = event.button.y;
            if (mouseX >= playButton.x && mouseX <= playButton.x + playButton.w &&
                mouseY >= playButton.y && mouseY <= playButton.y + playButton.h) {
                std::cout << "Play button clicked" << std::endl;
                isRunning = false;
            } else if (mouseX >= quitButton.x && mouseX <= quitButton.x + quitButton.w &&
                       mouseY >= quitButton.y && mouseY <= quitButton.y + quitButton.h) {
                std::cout << "Quit button clicked" << std::endl;
                quit = true;
            }
        }
    }
}
