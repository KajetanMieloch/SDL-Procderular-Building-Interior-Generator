#include "grid.hpp"


void Grid::init(){

    //Textures
    redBrickTex = LoadTexture("res/textures/red_brick.png");
    blueBrickTex = LoadTexture("res/textures/blue_brick.png");
    transparentTex = LoadTexture("res/textures/transparent.png");
    bombTex = LoadTexture("res/textures/bomb.png");
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

Grid::Grid(SDL_Renderer* renderer, int tileSize, int gridSize, HUD* hud) {
    this->renderer = renderer;
    this->tileSize = tileSize;
    this->gridSize = gridSize;
    this->visibleSize = 50; // Partially visible size
    this->hud = hud;

    // Initialize the grid
    grid = new int*[gridSize];
    for (int i = 0; i < gridSize; i++) {
        grid[i] = new int[gridSize];
        for (int j = 0; j < gridSize; j++) {
            grid[i][j] = 0;
        }
    }

    // Initialize first layer grid
    firstLayer.grid = new int*[gridSize];
    for (int i = 0; i < gridSize; i++) {
        firstLayer.grid[i] = new int[gridSize];
        for (int j = 0; j < gridSize; j++) {
            firstLayer.grid[i][j] = 0;
        }
    }

    // Initialize second layer grid
    secondLayer.grid = new int*[gridSize];
    for (int i = 0; i < gridSize; i++) {
        secondLayer.grid[i] = new int[gridSize];
        for (int j = 0; j < gridSize; j++) {
            secondLayer.grid[i][j] = 0;
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
            setTileTexture(x, y, 2, 1);
        }
    }
}

int Grid::witchTextureTileIs(int x, int y, int layer) {
    if (x >= 0 && x < gridSize && y >= 0 && y < gridSize) {
        switch (layer) {
            case 1:
                return firstLayer.grid[x][y];
            case 2:
                return secondLayer.grid[x][y];
            default:
                return grid[x][y];
        }
    }
    return 0;
}

void Grid::setTileTexture(int x, int y, int id, int layer) {
    if (x >= 0 && x < gridSize && y >= 0 && y < gridSize) {
        switch (layer) {
            case 1:
                firstLayer.grid[x][y] = id;
                break;
            case 2:
                secondLayer.grid[x][y] = id;
                break;
            default:
                grid[x][y] = id;
                break;
        }
    }
}

void Grid::handleMouseClick(int x, int y) {

    int mouseY;
    SDL_GetMouseState(NULL, &mouseY);


    if (x >= 0 && 
        x < GRID_SIZE &&
        y >= 0 && 
        y < GRID_SIZE &&
        mouseY < 1000
    ){
        // Mark the clicked tile
        std::cout << hud->getRenderLayer() << std::endl;
        setTileTexture(x, y, 2, 1);
        setTileTexture(x, y, 1, 2);
    }
}


void Grid::render(SDL_Renderer* renderer, int startX, int startY, int endX, int endY, int cameraX, int cameraY) {
        for (int x = startX; x < endX; x++) {
            for (int y = startY; y < endY; y++) {
                if (x >= 0 && x < gridSize && y >= 0 && y < gridSize) {


                    if (hud->getRenderLayer() == 1 || hud->getRenderLayer() == 3) {
                        // Render the first layer
                        int firstLayerTile = witchTextureTileIs(x, y, 1);
                        SDL_Rect firstLayerRect = {(x - startX) * tileSize, (y - startY) * tileSize, tileSize, tileSize};
                        switch (firstLayerTile) {
                            case 1:
                                SDL_RenderCopy(renderer, redBrickTex, NULL, &firstLayerRect);
                                break;
                            case 2:
                                SDL_RenderCopy(renderer, blueBrickTex, NULL, &firstLayerRect);
                                break;
                            default:
                                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White for unclicked tiles
                                SDL_RenderFillRect(renderer, &firstLayerRect);
                                break;
                    }}

                    if (hud->getRenderLayer() == 2 || hud->getRenderLayer() == 3) {
                        // Render the second layer
                        int secondLayerTile = witchTextureTileIs(x, y, 2);
                        SDL_Rect secondLayerRect = {(x - startX) * tileSize, (y - startY) * tileSize, tileSize, tileSize};
                        switch (secondLayerTile) {
                            case 1:
                                SDL_RenderCopy(renderer, bombTex, NULL, &secondLayerRect);
                                break;
                            default:
                                SDL_RenderCopy(renderer, transparentTex, NULL, &secondLayerRect);
                                break;
                        }
                    }

                }
            }
        }
};

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
            setTileTexture(i, j, id, 1);
        }
    }
}