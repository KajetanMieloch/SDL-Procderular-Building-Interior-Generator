#include "equipment.hpp"

Equipment::Equipment(SDL_Renderer* renderer) {
    this->renderer = renderer;
    // Other initialization code...
}

void Equipment::generateEquipment() {
    SDL_Rect equipmentRect;
    equipmentRect.x = 50;
    equipmentRect.y = 50;
    equipmentRect.w = 500;
    equipmentRect.h = 50;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &equipmentRect);
}

void Equipment::toggleEquipment() {
    equipmentOpen = !equipmentOpen;
}

bool Equipment::isEquipmentOpen() {
    return equipmentOpen;
}