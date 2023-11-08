#include "grid.hpp"


void Grid::init(){

    //Textures
    redBrickTex = LoadTexture("res/textures/red_brick.png");
    blueBrickTex = LoadTexture("res/textures/blue_brick.png");
    transparentTex = LoadTexture("res/textures/transparent.png");
    bombTex = LoadTexture("res/textures/bomb.png");
    wallTex = LoadTexture("res/textures/wall.png");
    cornerTex = LoadTexture("res/textures/corner.png");
    doorTex = LoadTexture("res/textures/door.png");
    windowTex = LoadTexture("res/textures/window.png");
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

    // Initialize first layer grid and rotation
    firstLayer.grid = new int*[gridSize];
    firstLayer.rotate = new int*[gridSize];
    for (int i = 0; i < gridSize; i++) {
        firstLayer.grid[i] = new int[gridSize];
        firstLayer.rotate[i] = new int[gridSize];
        for (int j = 0; j < gridSize; j++) {
            firstLayer.grid[i][j] = 0;
            firstLayer.rotate[i][j] = 0;
        }
    }

    // Initialize second layer grid and rotation
    secondLayer.grid = new int*[gridSize];
    secondLayer.rotate = new int*[gridSize];
    for (int i = 0; i < gridSize; i++) {
        secondLayer.grid[i] = new int[gridSize];
        secondLayer.rotate[i] = new int[gridSize];
        for (int j = 0; j < gridSize; j++) {
            secondLayer.grid[i][j] = 0;
            secondLayer.rotate[i][j] = 0;
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
            setTileTextureAndRotation(x, y, 2, 1);
        }
    }
}


int Grid::getTileTexture(int x, int y, int layer) {
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

int Grid::getTileRotation(int x, int y, int layer) {
    if (x >= 0 && x < gridSize && y >= 0 && y < gridSize) {
        switch (layer) {
            case 1:
                return firstLayer.rotate[x][y];
            case 2:
                return secondLayer.rotate[x][y];
            default:
                return 0;
        }
    }
    return 0;
}

void Grid::setTileTextureAndRotation(int x, int y, int id, int layer, int rotate) {
    if (x >= 0 && x < gridSize && y >= 0 && y < gridSize) {
        switch (layer) {
            case 1:
                firstLayer.grid[x][y] = id;
                firstLayer.rotate[x][y] = rotate;
                break;
            case 2:
                secondLayer.grid[x][y] = id;
                secondLayer.rotate[x][y] = rotate;
                break;
            default:
                grid[x][y] = id;
                break;
        }
    }
}

void Grid::handleMouseClick(int x, int y, int id, int rotate) {

    int mouseY;
    SDL_GetMouseState(NULL, &mouseY);


    if (x >= 0 && 
        x < GRID_SIZE &&
        y >= 0 && 
        y < GRID_SIZE &&
        mouseY < 1000
    ){


        if(id < 100){
            setTileTextureAndRotation(x,y,id,1, rotate);
        }else if (id >= 100){
            setTileTextureAndRotation(x,y,id,2, rotate);
        }
    }
}


void Grid::render(SDL_Renderer* renderer, int startX, int startY, int endX, int endY, int cameraX, int cameraY) {
        for (int x = startX; x < endX; x++) {
            for (int y = startY; y < endY; y++) {
                if (x >= 0 && x < gridSize && y >= 0 && y < gridSize) {


                    if (hud->getRenderLayer() == 1 || hud->getRenderLayer() == 3) {
                        // Render the first layer
                        int firstLayerTile = getTileTexture(x, y, 1);
                        int firstLayerRotation = getTileRotation(x, y, 1);
                        SDL_Rect firstLayerRect = {(x - startX) * tileSize, (y - startY) * tileSize, tileSize, tileSize};
                        switch (firstLayerTile) {
                            case 1:
                                SDL_RenderCopyEx(renderer, redBrickTex, NULL, &firstLayerRect, firstLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 2:
                                SDL_RenderCopyEx(renderer, blueBrickTex, NULL, &firstLayerRect, firstLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            default:
                                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White for unclicked tiles
                                SDL_RenderFillRect(renderer, &firstLayerRect);
                                break;
                    }}

                    if (hud->getRenderLayer() == 2 || hud->getRenderLayer() == 3) {
                        // Render the second layer
                        int secondLayerTile = getTileTexture(x, y, 2);
                        int secondLayerRotation = getTileRotation(x, y, 2);
                        SDL_Rect secondLayerRect = {(x - startX) * tileSize, (y - startY) * tileSize, tileSize, tileSize};
                        switch (secondLayerTile) {
                            case 101:
                                SDL_RenderCopyEx(renderer, bombTex, NULL, &secondLayerRect, secondLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 102:
                                SDL_RenderCopyEx(renderer, cornerTex, NULL, &secondLayerRect, secondLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 103:
                                SDL_RenderCopyEx(renderer, wallTex, NULL, &secondLayerRect, secondLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 104:
                                SDL_RenderCopyEx(renderer, doorTex, NULL, &secondLayerRect, secondLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 105:
                                SDL_RenderCopyEx(renderer, windowTex, NULL, &secondLayerRect, secondLayerRotation, NULL, SDL_FLIP_NONE);
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


bool Grid::chceckBorderingTilesForId(int x, int y, int id, int layer){
    for(int i = 0; i < 4; i++){
        switch(i){
            case 0:
                if(getTileTexture(x, y - 1, layer) == id){
                    return true;
                }
                break;
            case 1:
                if(getTileTexture(x, y + 1, layer) == id){
                    return true;
                }
                break;
            case 2:
                if(getTileTexture(x - 1, y, layer) == id){
                    return true;
                }
                break;
            case 3:
                if(getTileTexture(x + 1, y, layer) == id){
                    return true;
                }
                break;
        }
    }
    return false;
}

//Room generator

void Grid::generateRectangle(SDL_Renderer* renderer, int x, int y, int w, int h, int id) {
    //Generate rectangle with setTileTextureAndRotation
    std::vector<std::pair<int, int>> tiles;
    for (int i = x; i < x + w; i++) {
        for (int j = y; j < y + h; j++) {

            setTileTextureAndRotation(i, j, id, 1);

            //on boreders of rectangle
            if (i == x && j != y && j != y + h - 1) {
                setTileTextureAndRotation(i, j, 103, 2, 0);
                tiles.push_back(std::make_pair(i, j));
            } else if (i == x + w - 1 && j != y && j != y + h - 1) {
                setTileTextureAndRotation(i, j, 103, 2, 0);
                tiles.push_back(std::make_pair(i, j));
            } else if (j == y && i != x && i != x + w - 1) {
                setTileTextureAndRotation(i, j, 103, 2, 90);
                tiles.push_back(std::make_pair(i, j));
            } else if (j == y + h - 1 && i != x && i != x + w - 1) {
                setTileTextureAndRotation(i, j, 103, 2, 90);
                tiles.push_back(std::make_pair(i, j));
            }

            //on corners of rectangle
            if (i == x && j == y) {
                setTileTextureAndRotation(i, j, 102, 2, 270);
            } else if (i == x + w - 1 && j == y) {
                setTileTextureAndRotation(i, j, 102, 2, 0);
            } else if (i == x && j == y + h - 1) {
                setTileTextureAndRotation(i, j, 102, 2, 180);
            } else if (i == x + w - 1 && j == y + h - 1) {
                setTileTextureAndRotation(i, j, 102, 2, 90);
            }
        }
    }

    //randomly get one coordinate of wall
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, tiles.size() - 1);

    int random_index = distrib(gen);

    const auto& element = tiles[random_index];

    //For evry tile next to the randomly selected coordinate, check if it is a wall
    //If it is a wall, get the rotation of the wall
    for(int i = 0; i < tiles.size(); i++){
        if(tiles[i].first == element.first && tiles[i].second == element.second - 1){
            if(getTileTexture(tiles[i].first, tiles[i].second, 2) == 103){
                tiles.erase(tiles.begin() + i);
                setTileTextureAndRotation(element.first, element.second, 104, 2, 0);
            }
        }else if(tiles[i].first == element.first && tiles[i].second == element.second + 1){
            if(getTileTexture(tiles[i].first, tiles[i].second, 2) == 103){
                tiles.erase(tiles.begin() + i);
                setTileTextureAndRotation(element.first, element.second, 104, 2, 0);
            }
        }else if(tiles[i].first == element.first - 1 && tiles[i].second == element.second){
            if(getTileTexture(tiles[i].first, tiles[i].second, 2) == 103){
                tiles.erase(tiles.begin() + i);
                setTileTextureAndRotation(element.first, element.second, 104, 2, 90);
            }
        }else if(tiles[i].first == element.first + 1 && tiles[i].second == element.second){
            if(getTileTexture(tiles[i].first, tiles[i].second, 2) == 103){
                tiles.erase(tiles.begin() + i);
                setTileTextureAndRotation(element.first, element.second, 104, 2, 90);
            }
        }
    }
    //For every tile next to the randomly selected coordinate, check if it is a empty tile (id: 0)
    //If it is a empty tile, get the rotation of the wall and set it to a window
    for(int i = 0; i < tiles.size(); i++){
        if(tiles[i].first == element.first && tiles[i].second == element.second - 1 && chceckBorderingTilesForId(tiles[i].first, tiles[i].second, 0, 1)){
            if(getTileTexture(tiles[i].first, tiles[i].second, 2) == 103){
                tiles.erase(tiles.begin() + i);
                setTileTextureAndRotation(element.first, element.second, 105, 2, 0);
            }
        }else if(tiles[i].first == element.first && tiles[i].second == element.second + 1 && chceckBorderingTilesForId(tiles[i].first, tiles[i].second, 0, 1)){
            if(getTileTexture(tiles[i].first, tiles[i].second, 2) == 103){
                tiles.erase(tiles.begin() + i);
                setTileTextureAndRotation(element.first, element.second, 105, 2, 0);
            }
        }else if(tiles[i].first == element.first - 1 && tiles[i].second == element.second && chceckBorderingTilesForId(tiles[i].first, tiles[i].second, 0, 1)){
            if(getTileTexture(tiles[i].first, tiles[i].second, 2) == 103){
                tiles.erase(tiles.begin() + i);
                setTileTextureAndRotation(element.first, element.second, 105, 2, 90);
            }
        }else if(tiles[i].first == element.first + 1 && tiles[i].second == element.second && chceckBorderingTilesForId(tiles[i].first, tiles[i].second, 0, 1)){
            if(getTileTexture(tiles[i].first, tiles[i].second, 2) == 103){
                tiles.erase(tiles.begin() + i);
                setTileTextureAndRotation(element.first, element.second, 105, 2, 90);
            }
        }
    }
}