#include "grid.hpp"


void Grid::init(){
    
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

    clickedTexture = LoadTexture("src/red_brick.png");
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


SDL_Texture* Grid::getTextureFromJson(int id) {
    std::ifstream file("textures.json");
    nlohmann::json j;

    if (!file.is_open()) {
        std::cerr << "Failed to open texture.json" << std::endl;
        return NULL; // Handle the error appropriately
    }

    file >> j;
    std::cout << j << std::endl;

    auto textures = j.find("textures");
    if (textures != j.end()) {
        auto texture = std::find_if(textures->begin(), textures->end(), [id](const auto& t) {
            return t.find("id") != t.end() && t["id"] == id;
        });

        if (texture != textures->end() && texture->find("path") != texture->end()) {
            return LoadTexture((*texture)["path"]);
        }
    }

    return NULL; // Handle the error appropriately
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
                        std::cout << "1" << std::endl;
                        SDL_RenderCopy(renderer, getTextureFromJson(1), NULL, &rect);
                        break;
                    
                    case 2:
                        std::cout << "2" << std::endl;
                        SDL_RenderCopy(renderer, getTextureFromJson(2), NULL, &rect);
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

void Grid::generateRectangle(SDL_Renderer* renderer, int x, int y, int w, int h) {
    //Use it without rect. Generate border of rectangle with is tile clicked
    for (int i = 0; i < w; i++) {
        setTileTexture(x + i, y, 1);
        setTileTexture(x + i, y + h - 1, 1);
    }
    for (int i = 0; i < h; i++) {
        setTileTexture(x, y + i, 1);
        setTileTexture(x + w - 1, y + i, 1);
    }
}