#ifndef GRID_HPP
#define GRID_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <random>
#include <ctime>


class Grid {
public:
    Grid(SDL_Renderer* renderer, int tileSize, int gridSize);
    ~Grid();

    static const int TILE_SIZE = 32; // Set the desired size of each tile
    static const int GRID_SIZE = 100; // Set the desired size of the grid

    void init();
    int witchTextureTileIs(int x, int y);
    void setTileTexture(int x, int y, int id);
    void handleMouseClick(int x, int y);
    void generateRectangle(SDL_Renderer* renderer, int x, int y, int w, int h, int id);
    void setTexture(SDL_Texture* texture);
    void render(SDL_Renderer* renderer, int startX, int startY, int endX, int endY, int cameraX, int cameraY);
    void handleEvent(SDL_Event& e);
    void generateLevel(SDL_Renderer* renderer);
    SDL_Texture* LoadTexture(const std::string& filePath);

    SDL_Texture* redBrickTex;
    SDL_Texture* blueBrickTex;

private:
    SDL_Renderer* renderer;
    int tileSize;
    int gridSize;
    int visibleSize;
    int** grid;
};

#endif
