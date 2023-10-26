#include "grid.hpp"

Grid::Grid(SDL_Renderer* renderer, int tileSize, int gridSize) {
    this->renderer = renderer;
    this->tileSize = tileSize;
    this->gridSize = gridSize;
    this->visibleSize = 50; // Partially visible size

    // Initialize the grid with all tiles as white
    grid = new bool*[gridSize];
    for (int i = 0; i < gridSize; i++) {
        grid[i] = new bool[gridSize];
        for (int j = 0; j < gridSize; j++) {
            grid[i][j] = false;
        }
    }
}

Grid::~Grid() {
    for (int i = 0; i < gridSize; i++) {
        delete[] grid[i];
    }
    delete[] grid;
}

void Grid::render() {
    for (int i = 0; i < visibleSize; i++) {
        for (int j = 0; j < visibleSize; j++) {
            SDL_Rect rect = {i * tileSize, j * tileSize, tileSize, tileSize};

            if (grid[i][j]) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black
            } else {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
            }

            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

void Grid::handleEvent(SDL_Event& e) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int x = e.button.x / tileSize;
        int y = e.button.y / tileSize;

        if (x >= 0 && x < visibleSize && y >= 0 && y < visibleSize) {
            grid[x][y] = true;
        }
    }
}

bool Grid::isTileClicked(int x, int y) {
    return grid[x][y];
}

void Grid::setTileClicked(int x, int y, bool clicked) {
    grid[x][y] = clicked;
}

void Grid::handleMouseClick(int x, int y) {
    if (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE) {
        // Mark the clicked tile
        grid[x][y] = true;
    }
}