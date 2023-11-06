#include "equipment.hpp"

Equipment::Equipment(SDL_Renderer* renderer, SDL_Window* window) {
    this->renderer = renderer;
    this->window = window;
    // Other initialization code...
}

void Equipment::generateEquipment() {
    int windowHeight;
    int windowWidth;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    int equipmentWidth = 600;
    int equipmentHeight = 600;
    int equipmentX = (windowWidth - equipmentWidth) / 2;
    int equipmentY = (windowHeight - equipmentHeight) / 2;
    SDL_Rect equipmentRect;
    equipmentRect.x = equipmentX;
    equipmentRect.y = equipmentY;
    equipmentRect.w = equipmentWidth;
    equipmentRect.h = equipmentHeight;
    SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
    SDL_RenderFillRect(renderer, &equipmentRect);
}

void Equipment::toggleEquipment() {
    equipmentOpen = !equipmentOpen;
}

bool Equipment::isEquipmentOpen() {
    return equipmentOpen;
}