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

    SDL_Texture* bed2Tex;
    SDL_Texture* bedTex;
    SDL_Texture* blueBrickTex;
    SDL_Texture* bombTex;
    SDL_Texture* chair2Tex;
    SDL_Texture* chairTex;
    SDL_Texture* cornerTex;
    SDL_Texture* doorTex;
    SDL_Texture* electricStoveTex;
    SDL_Texture* fridgeClosedTex;
    SDL_Texture* fridgeOpenTex;
    SDL_Texture* gasStoveOnTex;
    SDL_Texture* gasStoveTex;
    SDL_Texture* meteoriteBrickTex;
    SDL_Texture* pearlstoneBrickTex;
    SDL_Texture* plateDirtyMuchTex;
    SDL_Texture* plateDirtyTex;
    SDL_Texture* plateMeatTex;
    SDL_Texture* platePotatoTex;
    SDL_Texture* plateTomatoLowTex;
    SDL_Texture* plateTomatoTex;
    SDL_Texture* plateTex;
    SDL_Texture* platinumBrickTex;
    SDL_Texture* potBoilingTex;
    SDL_Texture* potTomatoTex;
    SDL_Texture* potTex;
    SDL_Texture* potWaterTex;
    SDL_Texture* redBrickTex;
    SDL_Texture* sinkDirtyTex;
    SDL_Texture* sinkTex;
    SDL_Texture* snowBrickTex;
    SDL_Texture* tableTex;
    SDL_Texture* tableWhiteTex;
    SDL_Texture* transparentTex;
    SDL_Texture* wallTex;
    SDL_Texture* windowTex;

public:
    Equipment(SDL_Renderer* renderer, SDL_Window* window);
    ~Equipment();
    int processClick(int mouseX, int mouseY);
    void init();
    void generateEquipment();
    void toggleEquipment();
    bool isEquipmentOpen();
    int returnClickedTile(int startX, int startY, int cellWidth, int cellHeight);
};

#endif /* EQUIPMENT_HPP */