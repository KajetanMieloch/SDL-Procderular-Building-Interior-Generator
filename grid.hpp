#ifndef GRID_HPP
#define GRID_HPP

#include <SDL2/SDL.h>

class Grid {
public:
    Grid(SDL_Renderer* renderer, int tileSize, int gridSize);
    ~Grid();

    static const int TILE_SIZE = 12; // Set the desired size of each tile
    static const int GRID_SIZE = 250; // Set the desired size of the grid

    bool isTileClicked(int x, int y);
    void setTileClicked(int x, int y, bool clicked);
    void handleMouseClick(int x, int y);
    void setTexture(SDL_Texture* texture);
    void render(SDL_Renderer* renderer, int startX, int startY, int endX, int endY, int cameraX, int cameraY);
    void handleEvent(SDL_Event& e);

private:
    SDL_Renderer* renderer;
    int tileSize;
    int gridSize;
    int visibleSize;
    bool** grid;
};

#endif
