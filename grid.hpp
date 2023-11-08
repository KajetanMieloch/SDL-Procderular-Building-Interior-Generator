#ifndef GRID_HPP
#define GRID_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <random>
#include <ctime>
#include "hud.hpp"

class FirstLayer {
public:
    int** grid;
    int** rotate;
    // Add any other necessary methods and variables for this layer
private:
    // Add any necessary methods and variables for this layer
};

class SecondLayer {
public:
    int** grid;
    int** rotate;
    // Add any other necessary methods and variables for this layer
private:
    // Add any necessary methods and variables for this layer
};

class Grid {
public:
    Grid(SDL_Renderer* renderer, int tileSize, int gridSize, HUD* hud);
    ~Grid();

    static const int TILE_SIZE = 36; // Set the desired size of each tile
    static const int GRID_SIZE = 52; // Set the desired size of the grid

    void init();
    int getTileTexture(int x, int y, int layer);
    int getTileRotation(int x, int y, int layer);
    void setTileTextureAndRotation(int x, int y, int id, int layer, int rotate = 0);
    void handleMouseClick(int x, int y, int id, int rotate = 0);
    void generateRectangle(SDL_Renderer* renderer, int x, int y, int w, int h, int id);
    void setTexture(SDL_Texture* texture);
    void render(SDL_Renderer* renderer, int startX, int startY, int endX, int endY, int cameraX, int cameraY);
    void handleEvent(SDL_Event& e);
    void generateLevel(SDL_Renderer* renderer);
    bool chceckBorderingTilesForId(int x, int y, int id, int layer);
    int getRotationOfBorderingTileWithId(int x, int y, int id, int layer);
    
    SDL_Texture* LoadTexture(const std::string& filePath);

    SDL_Texture* redBrickTex;
    SDL_Texture* blueBrickTex;
    SDL_Texture* transparentTex;
    SDL_Texture* bombTex;
    SDL_Texture* wallTex;
    SDL_Texture* cornerTex;
    SDL_Texture* doorTex;
    SDL_Texture* windowTex;

private:
    SDL_Renderer* renderer;
    FirstLayer firstLayer;
    SecondLayer secondLayer;
    HUD* hud;
    SDL_Window* window;
    int tileSize;
    int gridSize;
    int visibleSize;
    int** grid;
};

#endif
