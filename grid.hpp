#ifndef GRID_HPP
#define GRID_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <random>
#include <ctime>
#include "hud.hpp"
#include <algorithm>
#include <tuple>
#include <vector>

class FirstLayer {
public:
    int** grid;
    int** rotate;
    bool** readyToBeLinked;
    bool** readyToBeMoved;
    // Add any other necessary methods and variables for this layer
private:
    // Add any necessary methods and variables for this layer
};

class SecondLayer {
public:
    int** grid;
    int** rotate;
    bool** readyToBeLinked;
    bool** readyToBeMoved;
    // Add any other necessary methods and variables for this layer
private:
    // Add any necessary methods and variables for this layer
};

class ThirdLayer {
public:
    int** grid;
    int** rotate;
    bool** readyToBeLinked;
    bool** readyToBeMoved;
    // Add any other necessary methods and variables for this layer
private:
    // Add any necessary methods and variables for this layer
};

class Grid {
public:
    Grid(SDL_Renderer* renderer, int tileSize, int gridSize, HUD* hud);
    ~Grid();

    static const int TILE_SIZE = 64; // Set the desired size of each tile
    static const int GRID_SIZE = 52; // Set the desired size of the grid

    void init();
    int getTileTexture(int x, int y, int layer);
    int getTileRotation(int x, int y, int layer);
    void setTileTextureAndRotation(int x, int y, int id, int layer, int rotate = 0);
    void handleMouseClick(int x, int y, int id, int rotate = 0);
    std::tuple<int, int, int> generateRoomWithAllVariations(SDL_Renderer* renderer, int x, int y, int w, int h, int id);
    void generateKitchen(SDL_Renderer* renderer, int x, int y, int w, int h, int id);
    void setTexture(SDL_Texture* texture);
    void render(SDL_Renderer* renderer, int startX, int startY, int endX, int endY, int cameraX, int cameraY);
    void handleEvent(SDL_Event& e);
    void generateLevel(SDL_Renderer* renderer);
    bool chceckBorderingTilesForId(int x, int y, int id, int layer);
    int getRotationOfBorderingTileWithId(int x, int y, int id, int layer);
    
    void markTileAsReadyToBeLinked(int x, int y, int layer);
    void confirmLinking();
    std::vector<std::vector<std::tuple<int, int, int>>> linkedTiles;
    std::tuple<int, int, int> tile;
    int linkedGroupCounter = 0;
    
    void rotateTile(int x, int y, int layer);
    void moveTile(int x, int y, int layer);
    int idOfTileBeingMoved = -1;
    int rotationOfTileBeingMoved = 0;
    bool isTileSelected = false;

    void cloneTile(int x, int y, int layer);
    void setIsTileCloned(bool isTileCloned) { this->isTileCloned = isTileCloned; }
    int idOfTileBeingCloned = -1;
    int rotationOfTileBeingCloned = 0;
    bool isTileCloned = false;

    void setCoursorMode(int mode);
    int getCoursorMode() { return coursorMode; }

    int coursorMode = 0;

    
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
    SDL_Texture* n1Tex;
    SDL_Texture* n2Tex;
    SDL_Texture* n3Tex;
    SDL_Texture* n4Tex;

private:
    SDL_Renderer* renderer;
    FirstLayer firstLayer;
    SecondLayer secondLayer;
    ThirdLayer thirdLayer;
    HUD* hud;
    SDL_Window* window;
    int tileSize;
    int gridSize;
    int visibleSize;
    int** grid;
    int** rotate;
    bool** readyToBeLinked;
    bool** readyToBeMoved;
};

#endif
