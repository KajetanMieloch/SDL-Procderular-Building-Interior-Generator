#include "grid.hpp"


SDL_Texture* Grid::LoadTexture(const std::string& filePath) {
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface) {
        // Handle the error appropriately
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        // Handle the error appropriately
    }

    return texture;
}

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

    clickedTexture = LoadTexture("src/bomb.png");
    //unclickedTexture = LoadTexture("unclicked_texture.png");
}

Grid::~Grid() {
    for (int i = 0; i < gridSize; i++) {
        delete[] grid[i];
    }
    delete[] grid;
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


void Grid::render(SDL_Renderer* renderer, int startX, int startY, int endX, int endY, int cameraX, int cameraY) {
        for (int x = startX; x < endX; x++) {
            for (int y = startY; y < endY; y++) {
                if (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE) {
                    SDL_Rect rect = {(x - startX) * TILE_SIZE, (y - startY) * TILE_SIZE, TILE_SIZE, TILE_SIZE};

                    if (isTileClicked(x, y)) {
                        SDL_RenderCopy(renderer, clickedTexture, NULL, &rect);
                    } else {
                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White for unclicked tiles
                        SDL_RenderFillRect(renderer, &rect);
                    }


                }
            }
        }
}