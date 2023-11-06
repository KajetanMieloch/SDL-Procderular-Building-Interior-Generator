#ifndef EQUIPMENT_HPP
#define EQUIPMENT_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

class Equipment {
private:
    SDL_Renderer* renderer;
    SDL_Window* window;
    bool equipmentOpen = false;

    SDL_Texture* LoadTexture(const std::string& filePath);

    SDL_Texture* redBrickTex;
    SDL_Texture* blueBrickTex;
    SDL_Texture* transparentTex;
    SDL_Texture* bombTex;
    SDL_Texture* wallTex;
    SDL_Texture* cornerTex;

public:
    Equipment(SDL_Renderer* renderer, SDL_Window* window);
    ~Equipment();
    void init();
    void generateEquipment();
    void toggleEquipment();
    bool isEquipmentOpen();
};

#endif /* EQUIPMENT_HPP */