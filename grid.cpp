#include "grid.hpp"


void Grid::init(){

    //Textures
    bed2Tex = LoadTexture("res/textures/bed2.png");
    bedTex = LoadTexture("res/textures/bed.png");
    blueBrickTex = LoadTexture("res/textures/blue_brick.png");
    bombTex = LoadTexture("res/textures/bomb.png");
    chair2Tex = LoadTexture("res/textures/chair2.png");
    chairTex = LoadTexture("res/textures/chair.png");
    cornerTex = LoadTexture("res/textures/corner.png");
    doorTex = LoadTexture("res/textures/door.png");
    electricStoveTex = LoadTexture("res/textures/electric_stove.png");
    fridgeClosedTex = LoadTexture("res/textures/fridge_closed.png");
    fridgeOpenTex = LoadTexture("res/textures/fridge_open.png");
    gasStoveOnTex = LoadTexture("res/textures/gas_stove_on.png");
    gasStoveTex = LoadTexture("res/textures/gas_stove.png");
    meteoriteBrickTex = LoadTexture("res/textures/meteorite_brick.png");
    pearlstoneBrickTex = LoadTexture("res/textures/pearlstone_brick.png");
    plateDirtyMuchTex = LoadTexture("res/textures/plate_dirty_much.png");
    plateDirtyTex = LoadTexture("res/textures/plate_dirty.png");
    plateMeatTex = LoadTexture("res/textures/plate_meat.png");
    platePotatoTex = LoadTexture("res/textures/plate_potato.png");
    plateTomatoLowTex = LoadTexture("res/textures/plate_tomato_low.png");
    plateTomatoTex = LoadTexture("res/textures/plate_tomato.png");
    plateTex = LoadTexture("res/textures/plate.png");
    platinumBrickTex = LoadTexture("res/textures/platinum_brick.png");
    potBoilingTex = LoadTexture("res/textures/pot_boiling.png");
    potTomatoTex = LoadTexture("res/textures/pot_tomato.png");
    potTex = LoadTexture("res/textures/pot.png");
    potWaterTex = LoadTexture("res/textures/pot_water.png");
    redBrickTex = LoadTexture("res/textures/red_brick.png");
    sinkDirtyTex = LoadTexture("res/textures/sink_dirty.png");
    sinkTex = LoadTexture("res/textures/sink.png");
    snowBrickTex = LoadTexture("res/textures/snow_brick.png");
    tableTex = LoadTexture("res/textures/table.png");
    tableWhiteTex = LoadTexture("res/textures/table_white.png");
    transparentTex = LoadTexture("res/textures/transparent.png");
    wallTex = LoadTexture("res/textures/wall.png");
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

    // Initialize third layer grid and rotation
    thirdLayer.grid = new int*[gridSize];
    thirdLayer.rotate = new int*[gridSize];
    for (int i = 0; i < gridSize; i++) {
        thirdLayer.grid[i] = new int[gridSize];
        thirdLayer.rotate[i] = new int[gridSize];
        for (int j = 0; j < gridSize; j++) {
            thirdLayer.grid[i][j] = 0;
            thirdLayer.rotate[i][j] = 0;
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


                    if (hud->getRenderLayer() == 1 || hud->getRenderLayer() == 4) {
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
                            case 3:
                                SDL_RenderCopyEx(renderer, snowBrickTex, NULL, &firstLayerRect, firstLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 4:
                                SDL_RenderCopyEx(renderer, meteoriteBrickTex, NULL, &firstLayerRect, firstLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 5:
                                SDL_RenderCopyEx(renderer, pearlstoneBrickTex, NULL, &firstLayerRect, firstLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 6:
                                SDL_RenderCopyEx(renderer, platinumBrickTex, NULL, &firstLayerRect, firstLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            default:
                                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White for unclicked tiles
                                SDL_RenderFillRect(renderer, &firstLayerRect);
                                break;
                    }}

                    if (hud->getRenderLayer() == 2 || hud->getRenderLayer() == 4) {
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
                            case 106:
                                SDL_RenderCopyEx(renderer, tableTex, NULL, &secondLayerRect, secondLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 107:
                                SDL_RenderCopyEx(renderer, tableWhiteTex, NULL, &secondLayerRect, secondLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 108:
                                SDL_RenderCopyEx(renderer, chairTex, NULL, &secondLayerRect, secondLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 109:
                                SDL_RenderCopyEx(renderer, chair2Tex, NULL, &secondLayerRect, secondLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 110:
                                SDL_RenderCopyEx(renderer, bedTex, NULL, &secondLayerRect, secondLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 111:
                                SDL_RenderCopyEx(renderer, bed2Tex, NULL, &secondLayerRect, secondLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 112:
                                SDL_RenderCopyEx(renderer, sinkTex, NULL, &secondLayerRect, secondLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 113:
                                SDL_RenderCopyEx(renderer, sinkDirtyTex, NULL, &secondLayerRect, secondLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 114:
                                SDL_RenderCopyEx(renderer, tableWhiteTex, NULL, &secondLayerRect, secondLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 115:
                                SDL_RenderCopyEx(renderer, electricStoveTex, NULL, &secondLayerRect, secondLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 116:
                                SDL_RenderCopyEx(renderer, gasStoveTex, NULL, &secondLayerRect, secondLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 117:
                                SDL_RenderCopyEx(renderer, gasStoveOnTex, NULL, &secondLayerRect, secondLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 118:
                                SDL_RenderCopyEx(renderer, electricStoveTex, NULL, &secondLayerRect, secondLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            default:
                                SDL_RenderCopy(renderer, transparentTex, NULL, &secondLayerRect);
                                break;
                        }
                    }
                    if(hud->getRenderLayer() == 3 || hud->getRenderLayer() == 4){
                        // Render the third layer
                        int thirdLayerTile = getTileTexture(x, y, 3);
                        int thirdLayerRotation = getTileRotation(x, y, 3);
                        SDL_Rect thirdLayerRect = {(x - startX) * tileSize, (y - startY) * tileSize, tileSize, tileSize};
                        switch (thirdLayerTile) {
                            case 201:
                                SDL_RenderCopyEx(renderer, plateTex, NULL, &thirdLayerRect, thirdLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 202:
                                SDL_RenderCopyEx(renderer, plateDirtyTex, NULL, &thirdLayerRect, thirdLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 203:
                                SDL_RenderCopyEx(renderer, plateDirtyMuchTex, NULL, &thirdLayerRect, thirdLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 204:
                                SDL_RenderCopyEx(renderer, plateMeatTex, NULL, &thirdLayerRect, thirdLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 205:
                                SDL_RenderCopyEx(renderer, platePotatoTex, NULL, &thirdLayerRect, thirdLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 206:
                                SDL_RenderCopyEx(renderer, plateTomatoTex, NULL, &thirdLayerRect, thirdLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 207:
                                SDL_RenderCopyEx(renderer, plateTomatoLowTex, NULL, &thirdLayerRect, thirdLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 208:
                                SDL_RenderCopyEx(renderer, potTex, NULL, &thirdLayerRect, thirdLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 209:
                                SDL_RenderCopyEx(renderer, potBoilingTex, NULL, &thirdLayerRect, thirdLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 210:
                                SDL_RenderCopyEx(renderer, potTomatoTex, NULL, &thirdLayerRect, thirdLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 211:
                                SDL_RenderCopyEx(renderer, potWaterTex, NULL, &thirdLayerRect, thirdLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            default:
                                SDL_RenderCopy(renderer, transparentTex, NULL, &thirdLayerRect);
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
std::uniform_int_distribution<int> valueDistribution(5, 10);  // Distribution for values between 5 and 30
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

int Grid::getRotationOfBorderingTileWithId(int x, int y, int id, int layer){
    for(int i = 0; i < 4; i++){
        switch(i){
            case 0:
                if(getTileTexture(x, y - 1, layer) == id){
                    return getTileRotation(x, y - 1, layer);
                }
                break;
            case 1:
                if(getTileTexture(x, y + 1, layer) == id){
                    return getTileRotation(x, y + 1, layer);
                }
                break;
            case 2:
                if(getTileTexture(x - 1, y, layer) == id){
                    return getTileRotation(x - 1, y, layer);
                }
                break;
            case 3:
                if(getTileTexture(x + 1, y, layer) == id){
                    return getTileRotation(x + 1, y, layer);
                }
                break;
        }
    }
    return 45;
}

//Room generator

void Grid::generateRectangle(SDL_Renderer* renderer, int x, int y, int w, int h, int id) {
    //Generate rectangle with setTileTextureAndRotation
    std::vector<std::pair<int, int>> tiles;
    for (int i = x; i < x + w; i++) {
        for (int j = y; j < y + h; j++) {

            setTileTextureAndRotation(i, j, id, 1);
            //On random not taken tiles render all furniture
            



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

    //Shuffle tiles
    std::shuffle(tiles.begin(), tiles.end(), std::mt19937{std::random_device{}()});

    //For evry tile next to the randomly selected coordinate, check if it is a wall
    //If it is a wall, get the rotation of the wall
    for(int i = 0; i < tiles.size(); i++){
        if(getTileTexture(tiles[i].first, tiles[i].second, 2) == 103){
            int rotation = getTileRotation(tiles[i].first, tiles[i].second, 2);
            //Set the tile to a door
            setTileTextureAndRotation(tiles[i].first, tiles[i].second, 104, 2, rotation);
            tiles.erase(tiles.begin() + i);
            break;
        }
    }
    //For every tile next to the randomly selected coordinate, check if it is a empty tile (id: 0)
    //If it is a empty tile, get the rotation of the wall and set it to a window
    //Generate a random number between 2 and 4 and place that many windows.
    std::uniform_int_distribution<> distrib2(2, 4);
    int window_count = distrib2(gen);
    for(int i = 0; i < window_count; i++){
        if(getTileTexture(tiles[i].first, tiles[i].second, 2) == 103){
            int rotation = getTileRotation(tiles[i].first, tiles[i].second, 2);
            setTileTextureAndRotation(tiles[i].first, tiles[i].second, 105, 2, rotation);
        }
    }
}