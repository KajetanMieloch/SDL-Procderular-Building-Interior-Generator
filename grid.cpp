#include "grid.hpp"


void Grid::init(){
    redBrickTex = LoadTexture("res/textures/red_brick.png");
    blueBrickTex = LoadTexture("res/textures/blue_brick.png");
}

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
    grid = new int*[gridSize];
    for (int i = 0; i < gridSize; i++) {
        grid[i] = new int[gridSize];
        for (int j = 0; j < gridSize; j++) {
            grid[i][j] = 0;
        }
    }
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
            setTileTexture(x, y, 2);
        }
    }
}

int Grid::witchTextureTileIs(int x, int y) {
    return grid[x][y];
}

void Grid::setTileTexture(int x, int y, int id) {
    grid[x][y] = id;
}


void Grid::handleMouseClick(int x, int y) {
    if (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE) {
        // Mark the clicked tile
        setTileTexture(x, y, 2);
    }
}


void Grid::render(SDL_Renderer* renderer, int startX, int startY, int endX, int endY, int cameraX, int cameraY) {
        for (int x = startX; x < endX; x++) {
            for (int y = startY; y < endY; y++) {
                if (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE) {
                    SDL_Rect rect = {(x - startX) * TILE_SIZE, (y - startY) * TILE_SIZE, TILE_SIZE, TILE_SIZE};

                    //do it as switch case
                    switch (witchTextureTileIs(x, y))
                    {
                    case 1:
                        SDL_RenderCopy(renderer, redBrickTex, NULL, &rect);
                        break;
                    
                    case 2:
                        SDL_RenderCopy(renderer, blueBrickTex, NULL, &rect);
                        break;
                    
                    default:
                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White for unclicked tiles
                        SDL_RenderFillRect(renderer, &rect);
                        break;
                    }
                }
            }
        }
}

void Grid::generateLevel(SDL_Renderer* renderer) {

srand(static_cast<unsigned int>(time(nullptr)));

// Create a random number generator engine
std::mt19937 gen(rand());
std::uniform_int_distribution<int> valueDistribution(5, 30);  // Distribution for values between 5 and 30
std::uniform_int_distribution<int> binaryDistribution(1, 2);  // Distribution for values 1 or 2

generateRectangle(
    renderer,
    valueDistribution(gen),  // Generate a random value between 5 and 30
    valueDistribution(gen),  // Generate a random value between 5 and 30
    valueDistribution(gen),  // Generate a random value between 5 and 30
    valueDistribution(gen),  // Generate a random value between 5 and 30
    binaryDistribution(gen)  // Generate a random value of 1 or 2
);

}

void Grid::generateRectangle(SDL_Renderer* renderer, int x, int y, int w, int h, int id) {
    //Use it without rect. Generate rectangle with setTileTexture
    for (int i = x; i < x + w; i++) {
        for (int j = y; j < y + h; j++) {
            setTileTexture(i, j, id);
        }
    }
}