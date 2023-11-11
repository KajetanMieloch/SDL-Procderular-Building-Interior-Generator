#include "equipment.hpp"

Equipment::Equipment(SDL_Renderer* renderer, SDL_Window* window) {
    this->renderer = renderer;
    this->window = window;
    // Other initialization code...
}

Equipment::~Equipment() {
    // Clean up code...
}

void Equipment::init() {

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

SDL_Texture* Equipment::LoadTexture(const std::string& filePath) {
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

int Equipment::processClick(int mouseX, int mouseY){
    int windowHeight;
    int windowWidth;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    int cellWidth = 50;
    int cellHeight = 50;
    int gridWidth = 10;
    int gridHeight = 10;
    int startX = (windowWidth - gridWidth * cellWidth) / 2;
    int startY = (windowHeight - gridHeight * cellHeight) / 2;

    int clickedI = (mouseY - startY) / cellHeight;
    int clickedJ = (mouseX - startX) / cellWidth;

    // Return the texture ID based on the clicked cell
    if (clickedI == 0) {
        switch (clickedJ) {
            case 0:
                return 0;
            case 1:
                return 1;
            case 2:
                return 2;
            case 3:
                return -1;
            case 4:
                return 101;
            case 5:
                return 102;
            case 6:
                return 103;
            case 7:
                return 104;
            case 8:
                return 105;
            case 9:
                return 3;
            default:
                return -1;
        }
    } else if (clickedI == 1){
        switch (clickedJ){

            case 0:
                return 110;
            case 1:
                return 111;
            case 2:
                return 108;
            case 3:
                return 109;
            case 4:
                return 106;
            case 5:
                return 107;
            case 6:
                return 112;
            case 7:
                return 113;
            case 8:
                return 119;
            case 9:
                return 120;
            default:
                return -1;
        }
    } else if (clickedI == 2){
        switch (clickedJ){
        case 0:
            return 116;
        case 1:
            return 117;
        case 2:
            return 118;
        case 3:
            return 208;
        case 4:
            return 211;
        case 5:
            return 209;
        case 6:
            return 210;
        case 7:
            return 4;
        case 8:
            return 5;        
        default:
            return -1;
        }
    }
    else {
        return -1;
    }
}

void Equipment::generateEquipment() {
    int windowHeight;
    int windowWidth;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    int equipmentWidth = 600;
    int equipmentHeight = 600;
    int equipmentX = (windowWidth - equipmentWidth) / 2;
    int equipmentY = (windowHeight - equipmentHeight) / 2;
    SDL_Rect equipmentRect;
    equipmentRect.x = equipmentX;
    equipmentRect.y = equipmentY;
    equipmentRect.w = equipmentWidth;
    equipmentRect.h = equipmentHeight;
    SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
    SDL_RenderFillRect(renderer, &equipmentRect);

    // Generate the grid for the equipment
    int cellWidth = 50;
    int cellHeight = 50;
    int gridWidth = 10;
    int gridHeight = 10;
    int startX = (windowWidth - gridWidth * cellWidth) / 2;
    int startY = (windowHeight - gridHeight * cellHeight) / 2;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int i = 0; i < gridHeight; ++i) {
        for (int j = 0; j < gridWidth; ++j) {
            SDL_Rect cellRect;
            cellRect.x = startX + j * cellWidth;
            cellRect.y = startY + i * cellHeight;
            cellRect.w = cellWidth;
            cellRect.h = cellHeight;
            SDL_RenderDrawRect(renderer, &cellRect);

            //For each cell, draw the appropriate texture
            if (i == 0) {
                switch (j) {
                    case 0:
                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
                        SDL_RenderFillRect(renderer, &cellRect);
                        break;
                    case 1:
                        SDL_RenderCopy(renderer, redBrickTex, NULL, &cellRect);
                        break;
                    case 2:
                        SDL_RenderCopy(renderer, blueBrickTex, NULL, &cellRect);
                        break;
                    case 3:
                        SDL_RenderCopy(renderer, transparentTex, NULL, &cellRect);
                        break;
                    case 4:
                        SDL_RenderCopy(renderer, bombTex, NULL, &cellRect);
                        break;
                    case 5:
                        SDL_RenderCopy(renderer, cornerTex, NULL, &cellRect);
                        break;
                    case 6:
                        SDL_RenderCopy(renderer, wallTex, NULL, &cellRect);
                        break;
                    case 7:
                        SDL_RenderCopy(renderer, doorTex, NULL, &cellRect);
                        break;
                    case 8:
                        SDL_RenderCopy(renderer, windowTex, NULL, &cellRect);
                        break;
                    case 9:
                        SDL_RenderCopy(renderer, snowBrickTex, NULL, &cellRect);
                        break;
                    default:
                        // Handle other cases, if necessary
                        break;
                }
            }
            if (i == 1) {
                switch (j) {
                    case 0:
                        SDL_RenderCopy(renderer, bedTex, NULL, &cellRect);
                        break;
                    case 1:
                        SDL_RenderCopy(renderer, bed2Tex, NULL, &cellRect);
                        break;
                    case 2:
                        SDL_RenderCopy(renderer, chairTex, NULL, &cellRect);
                        break;
                    case 3:
                        SDL_RenderCopy(renderer, chair2Tex, NULL, &cellRect);
                        break;
                    case 4:
                        SDL_RenderCopy(renderer, tableTex, NULL, &cellRect);
                        break;
                    case 5:
                        SDL_RenderCopy(renderer, tableWhiteTex, NULL, &cellRect);
                        break;
                    case 6:
                        SDL_RenderCopy(renderer, sinkTex, NULL, &cellRect);
                        break;
                    case 7:
                        SDL_RenderCopy(renderer, sinkDirtyTex, NULL, &cellRect);
                        break;
                    case 8:
                        SDL_RenderCopy(renderer, fridgeClosedTex, NULL, &cellRect);
                        break;
                    case 9:
                        SDL_RenderCopy(renderer, fridgeOpenTex, NULL, &cellRect);
                        break;
                    default:
                        // Handle other cases, if necessary
                        break;
                }
            }
            if(i == 2) {
                switch (j) {
                    case 0:
                        SDL_RenderCopy(renderer, gasStoveTex, NULL, &cellRect);
                        break;
                    case 1:
                        SDL_RenderCopy(renderer, gasStoveOnTex, NULL, &cellRect);
                        break;
                    case 2:
                        SDL_RenderCopy(renderer, electricStoveTex, NULL, &cellRect);
                        break;
                    case 3:
                        SDL_RenderCopy(renderer, potTex, NULL, &cellRect);
                        break;
                    case 4:
                        SDL_RenderCopy(renderer, potWaterTex, NULL, &cellRect);
                        break;
                    case 5:
                        SDL_RenderCopy(renderer, potBoilingTex, NULL, &cellRect);
                        break;
                    case 6:
                        SDL_RenderCopy(renderer, potTomatoTex, NULL, &cellRect);
                        break;
                    case 7:
                        SDL_RenderCopy(renderer, meteoriteBrickTex, NULL, &cellRect);
                        break;
                    case 8:
                        SDL_RenderCopy(renderer, pearlstoneBrickTex, NULL, &cellRect);
                        break;
                    case 9:
                        SDL_RenderCopy(renderer, platinumBrickTex, NULL, &cellRect);
                        break;
                    default:
                        // Handle other cases, if necessary
                        break;
                        
                }
            }
        }
    }
}

void Equipment::toggleEquipment() {
    equipmentOpen = !equipmentOpen;
}

bool Equipment::isEquipmentOpen() {
    return equipmentOpen;
}