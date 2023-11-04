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
    int** grid; // Similar to the first layer
    // Add any other necessary methods and variables for this layer
private:
    // Add any necessary methods and variables for this layer
};

class SecondLayer {
public:
    int** grid; // Similar to the first layer
    // Add any other necessary methods and variables for this layer
private:
    // Add any necessary methods and variables for this layer
};

class Grid {
public:
    Grid(SDL_Renderer* renderer, int tileSize, int gridSize, HUD* hud);
    ~Grid();

    static const int TILE_SIZE = 32; // Set the desired size of each tile
    static const int GRID_SIZE = 100; // Set the desired size of the grid

    void init();
    int witchTextureTileIs(int x, int y, int layer);
    void setTileTexture(int x, int y, int id, int layer);
    void handleMouseClick(int x, int y);
    void generateRectangle(SDL_Renderer* renderer, int x, int y, int w, int h, int id);
    void setTexture(SDL_Texture* texture);
    void render(SDL_Renderer* renderer, int startX, int startY, int endX, int endY, int cameraX, int cameraY);
    void handleEvent(SDL_Event& e);
    void generateLevel(SDL_Renderer* renderer);
    SDL_Texture* LoadTexture(const std::string& filePath);

    SDL_Texture* redBrickTex;
    SDL_Texture* blueBrickTex;
    SDL_Texture* transparentTex;
    SDL_Texture* bombTex;

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
