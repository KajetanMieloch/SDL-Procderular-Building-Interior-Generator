#include "equipment.hpp"

Equipment::Equipment(SDL_Renderer* renderer, SDL_Window* window) {
    this->renderer = renderer;
    this->window = window;
    // Other initialization code...
}

Equipment::~Equipment() {
    // Clean up code...
}

void Equipment::init() {
    
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

    // Generate the grid for the equipment
    int cellWidth = 50;
    int cellHeight = 50;
    int gridWidth = 10;
    int gridHeight = 10;
    int startX = (windowWidth - gridWidth * cellWidth) / 2;
    int startY = (windowHeight - gridHeight * cellHeight) / 2;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int i = 0; i < gridHeight; ++i) {
        for (int j = 0; j < gridWidth; ++j) {
            SDL_Rect cellRect;
            cellRect.x = startX + j * cellWidth;
            cellRect.y = startY + i * cellHeight;
            cellRect.w = cellWidth;
            cellRect.h = cellHeight;
            SDL_RenderDrawRect(renderer, &cellRect);

            SDL_Rect innerRect;
            innerRect.x = startX + j * cellWidth + 5;
            innerRect.y = startY + i * cellHeight + 5;
            innerRect.w = cellWidth - 10;
            innerRect.h = cellHeight - 10;
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderFillRect(renderer, &innerRect);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
    }
    
}

void Equipment::toggleEquipment() {
    equipmentOpen = !equipmentOpen;
}

bool Equipment::isEquipmentOpen() {
    return equipmentOpen;
}