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
    n1Tex = LoadTexture("res/textures/1.png");
    n2Tex = LoadTexture("res/textures/2.png");
    n3Tex = LoadTexture("res/textures/3.png");
    n4Tex = LoadTexture("res/textures/4.png");
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
    firstLayer.readyToBeLinked = new bool*[gridSize];
    for (int i = 0; i < gridSize; i++) {
        firstLayer.grid[i] = new int[gridSize];
        firstLayer.rotate[i] = new int[gridSize];
        firstLayer.readyToBeLinked[i] = new bool[gridSize];
        for (int j = 0; j < gridSize; j++) {
            firstLayer.grid[i][j] = 0;
            firstLayer.rotate[i][j] = 0;
            firstLayer.readyToBeLinked[i][j] = false;
        }
    }

    // Initialize second layer grid and rotation
    secondLayer.grid = new int*[gridSize];
    secondLayer.rotate = new int*[gridSize];
    secondLayer.readyToBeLinked = new bool*[gridSize];
    for (int i = 0; i < gridSize; i++) {
        secondLayer.grid[i] = new int[gridSize];
        secondLayer.rotate[i] = new int[gridSize];
        secondLayer.readyToBeLinked[i] = new bool[gridSize];
        for (int j = 0; j < gridSize; j++) {
            secondLayer.grid[i][j] = 0;
            secondLayer.rotate[i][j] = 0;
            secondLayer.readyToBeLinked[i][j] = false;
        }
    }

    // Initialize third layer grid and rotation
    thirdLayer.grid = new int*[gridSize];
    thirdLayer.rotate = new int*[gridSize];
    thirdLayer.readyToBeLinked = new bool*[gridSize];
    for (int i = 0; i < gridSize; i++) {
        thirdLayer.grid[i] = new int[gridSize];
        thirdLayer.rotate[i] = new int[gridSize];
        thirdLayer.readyToBeLinked[i] = new bool[gridSize];
        for (int j = 0; j < gridSize; j++) {
            thirdLayer.grid[i][j] = 0;
            thirdLayer.rotate[i][j] = 0;
            thirdLayer.readyToBeLinked[i][j] = false;
        }
    }

}

Grid::~Grid() {
    for (int i = 0; i < gridSize; i++) {
        delete[] grid[i];
    }
    delete[] grid;
}


int Grid::getTileTexture(int x, int y, int layer) {
    if (x >= 0 && x < gridSize && y >= 0 && y < gridSize) {
        switch (layer) {
            case 1:
                return firstLayer.grid[x][y];
            case 2:
                return secondLayer.grid[x][y];
            case 3:
                return thirdLayer.grid[x][y];
            default:
                return 0;
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
            case 3:
                return thirdLayer.rotate[x][y];
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
            case 3:
                thirdLayer.grid[x][y] = id;
                thirdLayer.rotate[x][y] = rotate;
            default:
                grid[x][y] = id;
                break;
        }
    }
}

void Grid::rotateTile(int x, int y, int layer){
    if (x >= 0 && x < gridSize && y >= 0 && y < gridSize) {
        switch (layer) {
            case 1:
                if(firstLayer.rotate[x][y] == 270){
                    firstLayer.rotate[x][y] = 0;
                }else{
                    firstLayer.rotate[x][y] += 90;
                }
                break;
            case 2:
                if(secondLayer.rotate[x][y] == 270){
                    secondLayer.rotate[x][y] = 0;
                }else{
                    secondLayer.rotate[x][y] += 90;
                }
                break;
            case 3:
                if(thirdLayer.rotate[x][y] == 270){
                    thirdLayer.rotate[x][y] = 0;
                }else{
                    thirdLayer.rotate[x][y] += 90;
                }
            default:
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
        }else if (id >= 100 && id < 200){
            setTileTextureAndRotation(x,y,id,2, rotate);
        }else if (id >= 200){
            setTileTextureAndRotation(x,y,id,3,rotate);
        }
    }
}

void Grid::markTileAsReadyToBeLinked(int x, int y, int layer){
    if (x >= 0 && x < gridSize && y >= 0 && y < gridSize) {
        switch (layer) {
            case 1:
                firstLayer.readyToBeLinked[x][y] = true;
                break;
            case 2:
                secondLayer.readyToBeLinked[x][y] = true;
                break;
            case 3:
                thirdLayer.readyToBeLinked[x][y] = true;
            default:
                break;
        }
    }
}

void Grid::moveTile(int x, int y, int layer){
    //Delete existing tile
    if(!isTileSelected){
    idOfTileBeingMoved = getTileTexture(x, y, layer);
    rotationOfTileBeingMoved = getTileRotation(x, y, layer);
    isTileSelected = true;
    setTileTextureAndRotation(x, y, 0, layer);
    }else{
        setTileTextureAndRotation(x, y, idOfTileBeingMoved, layer, rotationOfTileBeingMoved);
        idOfTileBeingMoved = -1;
        isTileSelected = false;
    }
    //Click on another tile and replace it with coursor texture
    //Coursor is now mode 2
}

void Grid::setCoursorMode(int mode){
    coursorMode = mode;
    SDL_Cursor* cursor;
    switch(mode){
        case 0:
            cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
            SDL_SetCursor(cursor);
            break;
        case 1:
            cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
            SDL_SetCursor(cursor);
            break;
        case 2:
            cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL);
            SDL_SetCursor(cursor);
            break;
        case 3:
            cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENS);
            SDL_SetCursor(cursor);
            break;
        case 4:
            cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE);
            SDL_SetCursor(cursor);
            break;
        case 5:
            cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENESW);
            SDL_SetCursor(cursor);
            break;
        case 6:
            cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENWSE);
            SDL_SetCursor(cursor);
            break;
        case 7:
            cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL);
            SDL_SetCursor(cursor);
            break;
        case 8: {
            SDL_Surface* surface = IMG_Load("res/rotate.png");
            cursor = SDL_CreateColorCursor(surface, 0, 0);
            SDL_SetCursor(cursor);
            break;
        }
        default:
            cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
            SDL_SetCursor(cursor);
            break;
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
                                SDL_RenderCopyEx(renderer, platinumBrickTex, NULL, &firstLayerRect, firstLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 5:
                                SDL_RenderCopyEx(renderer, meteoriteBrickTex, NULL, &firstLayerRect, firstLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 6:
                                SDL_RenderCopyEx(renderer, pearlstoneBrickTex, NULL, &firstLayerRect, firstLayerRotation, NULL, SDL_FLIP_NONE);
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
                            case 119:
                                SDL_RenderCopyEx(renderer, fridgeClosedTex, NULL, &secondLayerRect, secondLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 120:
                                SDL_RenderCopyEx(renderer, fridgeOpenTex, NULL, &secondLayerRect, secondLayerRotation, NULL, SDL_FLIP_NONE);
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
                            case 212:
                                SDL_RenderCopyEx(renderer, n1Tex, NULL, &thirdLayerRect, thirdLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 213:
                                SDL_RenderCopyEx(renderer, n2Tex, NULL, &thirdLayerRect, thirdLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 214:
                                SDL_RenderCopyEx(renderer, n3Tex, NULL, &thirdLayerRect, thirdLayerRotation, NULL, SDL_FLIP_NONE);
                                break;
                            case 215:
                                SDL_RenderCopyEx(renderer, n4Tex, NULL, &thirdLayerRect, thirdLayerRotation, NULL, SDL_FLIP_NONE);
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
std::uniform_int_distribution<int> roomSizeGenerator(10, 20);
std::uniform_int_distribution<int> roomDistribution(1, 2);
std::uniform_int_distribution<int> kitchenDistribution(3, 4);
std::uniform_int_distribution<int> bathroomDistribution(5,6);

auto [doorX, doorY, doorRot] = generateRoomWithAllVariations(
    renderer,
    roomSizeGenerator(gen),  // Generate a random value between 5 and 30
    roomSizeGenerator(gen),  // Generate a random value between 5 and 30
    roomSizeGenerator(gen),  // Generate a random value between 5 and 30
    roomSizeGenerator(gen),  // Generate a random value between 5 and 30
    roomDistribution(gen)    // Generate a random value between 1 and 2
);
std::cout<<doorX<<std::endl;
generateKitchen(
    renderer,
    roomSizeGenerator(gen) * 1.8,
    roomSizeGenerator(gen) * 1.8,
    roomSizeGenerator(gen),
    roomSizeGenerator(gen),
    kitchenDistribution(gen)
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

std::tuple<int, int, int> Grid::generateRoomWithAllVariations(SDL_Renderer* renderer, int x, int y, int w, int h, int id){
    //Generate rectangle with setTileTextureAndRotation
    std::vector<std::pair<int, int>> tiles;
    int posXOfFirstDoor;
    int posYOfFirstDoor;
    int rotationOfFirstDoor;
    for (int i = x; i < x + w; i++) {
        for (int j = y; j < y + h; j++) {

            setTileTextureAndRotation(i, j, id, 1);
            //On random not taken tiles render all furniture
            if (i != x && i != x + w - 1 && j != y && j != y + h - 1) {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> distrib(0, 200);
                int random = distrib(gen);

                //random rotation (0,90,180,270)
                std::uniform_int_distribution<> distrib3(0, 3);
                int random3 = distrib3(gen);
                int rotation = 0;
                switch (random3) {
                    case 0:
                        rotation = 0;
                        break;
                    case 1:
                        rotation = 90;
                        break;
                    case 2:
                        rotation = 180;
                        break;
                    case 3:
                        rotation = 270;
                        break;
                }
                
                if (random < 30) {
                    setTileTextureAndRotation(i, j, 106, 2, rotation);
                } else if (random < 35) {
                    setTileTextureAndRotation(i, j, 107, 2, rotation);
                } else if (random < 40) {
                    setTileTextureAndRotation(i, j, 108, 2, rotation);
                } else if (random < 45) {
                    setTileTextureAndRotation(i, j, 109, 2, rotation);
                } else if (random < 50) {
                    setTileTextureAndRotation(i, j, 110, 2, rotation);
                } else if (random < 55) {
                    setTileTextureAndRotation(i, j, 111, 2, rotation);
                } else if (random < 60) {
                    setTileTextureAndRotation(i, j, 112, 2, rotation);
                } else if (random < 65) {
                    setTileTextureAndRotation(i, j, 113, 2, rotation);
                } else if (random < 70) {
                    setTileTextureAndRotation(i, j, 114, 2, rotation);
                } else if (random < 75) {
                    setTileTextureAndRotation(i, j, 115, 2, rotation);
                } else if (random < 80) {
                    setTileTextureAndRotation(i, j, 116, 2, rotation);
                } else if (random < 85) {
                    setTileTextureAndRotation(i, j, 117, 2, rotation);
                } else if (random < 90) {
                    setTileTextureAndRotation(i, j, 118, 2, rotation);
                } else if (random < 95) {
                    setTileTextureAndRotation(i, j, 119, 2, rotation);
                } else if (random < 100) {
                    setTileTextureAndRotation(i, j, 120, 2, rotation);
                }

                //New random number for third layer
                std::uniform_int_distribution<> distrib2(0, 1000);
                int random2 = distrib2(gen);
                if (random2 < 5) {
\
                    setTileTextureAndRotation(i, j, 201, 3, rotation);
                } else if (random2 < 10) {
                    setTileTextureAndRotation(i, j, 202, 3, rotation);
                } else if (random2 < 15) {
                    setTileTextureAndRotation(i, j, 203, 3, rotation);
                } else if (random2 < 20) {
                    setTileTextureAndRotation(i, j, 204, 3, rotation);
                } else if (random2 < 25) {
                    setTileTextureAndRotation(i, j, 205, 3, rotation);
                } else if (random2 < 30) {
                    setTileTextureAndRotation(i, j, 206, 3, rotation);
                } else if (random2 < 35) {
                    setTileTextureAndRotation(i, j, 207, 3, rotation);
                } else if (random2 < 40) {
                    setTileTextureAndRotation(i, j, 208, 3, rotation);
                } else if (random2 < 45) {
                    setTileTextureAndRotation(i, j, 209, 3, rotation);
                } else if (random2 < 50) {
                    setTileTextureAndRotation(i, j, 210, 3, rotation);
                } else if (random2 < 55) {
                    setTileTextureAndRotation(i, j, 211, 3, rotation);
                }

            } 
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
    //Generate door (id 104), and second door (id 104), on another x or y axis
    for(int i = 0; i < tiles.size(); i++){
        if(getTileTexture(tiles[i].first, tiles[i].second, 2) == 103){
            int rotation = getTileRotation(tiles[i].first, tiles[i].second, 2);
            //Set the tile to a door
            setTileTextureAndRotation(tiles[i].first, tiles[i].second, 104, 2, rotation);
            posXOfFirstDoor= tiles[i].first;
            posYOfFirstDoor = tiles[i].second;
            rotationOfFirstDoor = rotation;
            
            // Generate a random index for the second door
            int randomIndex = distrib(gen);
            if (randomIndex != i && randomIndex < tiles.size()) { // Ensure the second door is not at the same position as the first
                int newRotation = getTileRotation(tiles[randomIndex].first, tiles[randomIndex].second, 2);
                setTileTextureAndRotation(tiles[randomIndex].first, tiles[randomIndex].second, 104, 2, newRotation);
            }

            // Generate a random index for the third door
            int randomIndex2 = distrib(gen);
            if (randomIndex2 != i && randomIndex2 != randomIndex && randomIndex2 < tiles.size()) { // Ensure the third door is not at the same position as the first or second
                int newRotation = getTileRotation(tiles[randomIndex2].first, tiles[randomIndex2].second, 2);
                setTileTextureAndRotation(tiles[randomIndex2].first, tiles[randomIndex2].second, 104, 2, newRotation);
            }

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
    return std::make_tuple(posXOfFirstDoor, posYOfFirstDoor, rotationOfFirstDoor);
}

void Grid::generateKitchen(SDL_Renderer* renderer, int x, int y, int w, int h, int id){
   //Generate rectangle with setTileTextureAndRotation
    std::vector<std::pair<int, int>> tiles;
    for (int i = x; i < x + w; i++) {
        for (int j = y; j < y + h; j++) {

            setTileTextureAndRotation(i, j, id, 1);
            //On random not taken tiles render all furniture
            if (i != x && i != x + w - 1 && j != y && j != y + h - 1) {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> distrib(0, 1000);
                int random = distrib(gen);

                //random rotation (0,90,180,270)
                std::uniform_int_distribution<> distrib3(0, 3);
                int random3 = distrib3(gen);
                int rotation = 0;
                switch (random3) {
                    case 0:
                        rotation = 0;
                        break;
                    case 1:
                        rotation = 90;
                        break;
                    case 2:
                        rotation = 180;
                        break;
                    case 3:
                        rotation = 270;
                        break;
                }
                
                if (random < 30) {
                    setTileTextureAndRotation(i, j, 106, 2, rotation);
                } else if (random < 35) {
                    setTileTextureAndRotation(i, j, 107, 2, rotation);
                } else if (random < 60) {
                    setTileTextureAndRotation(i, j, 112, 2, rotation);
                } else if (random < 65) {
                    setTileTextureAndRotation(i, j, 113, 2, rotation);
                } else if (random < 70) {
                    setTileTextureAndRotation(i, j, 114, 2, rotation);
                } else if (random < 75) {
                    setTileTextureAndRotation(i, j, 115, 2, rotation);
                } else if (random < 80) {
                    setTileTextureAndRotation(i, j, 116, 2, rotation);
                } else if (random < 85) {
                    setTileTextureAndRotation(i, j, 117, 2, rotation);
                } else if (random < 90) {
                    setTileTextureAndRotation(i, j, 118, 2, rotation);
                } else if (random < 95) {
                    setTileTextureAndRotation(i, j, 119, 2, rotation);
                } else if (random < 100) {
                    setTileTextureAndRotation(i, j, 120, 2, rotation);
                }

                //New random number for third layer
                std::uniform_int_distribution<> distrib2(0, 1000);
                int random2 = distrib2(gen);
                if (random2 < 5) {
\
                    setTileTextureAndRotation(i, j, 201, 3, rotation);
                } else if (random2 < 10) {
                    setTileTextureAndRotation(i, j, 202, 3, rotation);
                } else if (random2 < 15) {
                    setTileTextureAndRotation(i, j, 203, 3, rotation);
                } else if (random2 < 20) {
                    setTileTextureAndRotation(i, j, 204, 3, rotation);
                } else if (random2 < 25) {
                    setTileTextureAndRotation(i, j, 205, 3, rotation);
                } else if (random2 < 30) {
                    setTileTextureAndRotation(i, j, 206, 3, rotation);
                } else if (random2 < 35) {
                    setTileTextureAndRotation(i, j, 207, 3, rotation);
                } else if (random2 < 40) {
                    setTileTextureAndRotation(i, j, 208, 3, rotation);
                } else if (random2 < 45) {
                    setTileTextureAndRotation(i, j, 209, 3, rotation);
                } else if (random2 < 50) {
                    setTileTextureAndRotation(i, j, 210, 3, rotation);
                } else if (random2 < 55) {
                    setTileTextureAndRotation(i, j, 211, 3, rotation);
                }

            } 
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
    //Generate door (id 104), and second door (id 104), on another x or y axis
    for(int i = 0; i < tiles.size(); i++){
        if(getTileTexture(tiles[i].first, tiles[i].second, 2) == 103){
            int rotation = getTileRotation(tiles[i].first, tiles[i].second, 2);
            //Set the tile to a door
            setTileTextureAndRotation(tiles[i].first, tiles[i].second, 104, 2, rotation);
            
            // Generate a random index for the second door
            int randomIndex = distrib(gen);
            if (randomIndex != i && randomIndex < tiles.size()) { // Ensure the second door is not at the same position as the first
                int newRotation = getTileRotation(tiles[randomIndex].first, tiles[randomIndex].second, 2);
                setTileTextureAndRotation(tiles[randomIndex].first, tiles[randomIndex].second, 104, 2, newRotation);
            }

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