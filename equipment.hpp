#ifndef EQUIPMENT_HPP
#define EQUIPMENT_HPP

#include <SDL2/SDL.h>

class Equipment {
private:
    SDL_Renderer* renderer;
    bool equipmentOpen;
public:
    Equipment(SDL_Renderer* renderer);
    ~Equipment();
    void init();
    void generateEquipment();
    void toggleEquipment();
    bool isEquipmentOpen();
};

#endif /* EQUIPMENT_HPP */