#ifndef EQUIPMENT_HPP
#define EQUIPMENT_HPP

#include <SDL2/SDL.h>

class Equipment {
private:
    SDL_Renderer* renderer;
    SDL_Window* window;
    bool equipmentOpen = false;
public:
    Equipment(SDL_Renderer* renderer, SDL_Window* window);
    ~Equipment();
    void init();
    void generateEquipment();
    void toggleEquipment();
    bool isEquipmentOpen();
};

#endif /* EQUIPMENT_HPP */