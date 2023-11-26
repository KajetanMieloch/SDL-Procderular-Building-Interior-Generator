#include "game.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include "grid.hpp"
#include "hud.hpp"
#include "equipment.hpp"

bool rectangleGenerated = false;

Game::Game() {}
Game::~Game() {}


void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        }
        isRunning = true;
        if (TTF_Init() == -1) {
            // Handle TTF initialization failure
            std::cerr << "Failed to initialize TTF: " << TTF_GetError() << std::endl;
        } else {
            font = TTF_OpenFont("res/Arial.ttf", 30);
            if (!font) {
                // Handle font loading failure
                std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
            }
        }
    } else {
        isRunning = false;
    }

    // Initialize the camera position to (0, 0)
    cameraX = 0;
    cameraY = 0;

    int activeId = 0;
    //Initialize the HUD
    hud = new HUD(renderer, window);
    hud->init();

    //Initialize the equipment
    equipment = new Equipment(renderer, window);
    equipment->init();

    //Initialize the grid
    grid = new Grid(renderer, Grid::TILE_SIZE, Grid::GRID_SIZE, hud);
    grid->init();


    // Initialize the last frame time to the current time
    lastFrameTime = SDL_GetPerformanceCounter();
}

SDL_Renderer* Game::getRenderer() {
    return renderer;
}

void Game::resetLevel() {
    delete grid;
    grid = new Grid(renderer, Grid::TILE_SIZE, Grid::GRID_SIZE, hud);
    grid->init();
    grid->generateLevel(renderer);
}

void Game::run() {

    Uint64 lastFrameTime = SDL_GetPerformanceCounter();
    while (isRunning) {
        handleEvents(); // Call handleEvents() at the beginning of each frame
        update();
        render();

        // Calculate the time elapsed since the last frame
        Uint64 currentFrameTime = SDL_GetPerformanceCounter();
        double frameTime = (currentFrameTime - lastFrameTime) * 1000.0 / SDL_GetPerformanceFrequency();
        lastFrameTime = currentFrameTime;

        // Delay the loop if necessary to maintain the desired frame rate
        if (frameTime < frameDelay) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    clean();
}

TTF_Font* Game::getFont() {
    return font;
}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    
    int adjustedX = 0; // Declare the variables here with initial values
    int adjustedY = 0;

    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                case SDLK_a:
                    // Move the camera left
                    cameraX -= Grid::TILE_SIZE;
                    break;
                case SDLK_RIGHT:
                case SDLK_d:
                    // Move the camera right
                    cameraX += Grid::TILE_SIZE;
                    break;
                case SDLK_UP:
                case SDLK_w:
                    // Move the camera up
                    cameraY -= Grid::TILE_SIZE;
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    // Move the camera down
                    cameraY += Grid::TILE_SIZE;
                    break;
                //Reset the level CASE
                case SDLK_r:
                    resetLevel();
                    grid->setCoursorMode(0);
                    break;
                case SDLK_e:
                    equipment->toggleEquipment();
                    grid->setCoursorMode(0);
                    break;
                case SDLK_f: {
                    if (activeRotation == 270)
                        activeRotation = 0;
                    else{
                        activeRotation += 90;
                    }
                    grid->setCoursorMode(8);                    
                    break;
                }
                case SDLK_m:
                    grid->setCoursorMode(2);
                    break;
                default:
                    break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            // Adjust the mouse coordinates for camera position
            adjustedX = (event.button.x + cameraX) / Grid::TILE_SIZE;
            adjustedY = (event.button.y + cameraY) / Grid::TILE_SIZE;

            switch (grid -> getCoursorMode()){
            case 0:
            // Pass the raw mouse coordinates to the equipment close it and break case
            if(equipment->isEquipmentOpen()){
                activeId = equipment->processClick(event.button.x, event.button.y);
                if(activeId != -1){
                    equipment->toggleEquipment();
                    break;
                }
            }
            // Pass the adjusted mouse coordinates to the grid
            if(!equipment->isEquipmentOpen())
                grid->handleMouseClick(adjustedX, adjustedY, activeId, activeRotation);
            break;
            
            case 2:
                grid->moveTile(adjustedX, adjustedY, hud->getRenderLayer());
                break;

            case 8:
                grid->rotateTile(adjustedX, adjustedY, hud->getRenderLayer());
                break;

            default:
                break;
            }
        default:
            break;
    }
}

void Game::update() {
    // Add game logic here
}

void Game::render() {

    if (!rectangleGenerated) {
        grid->generateLevel(renderer);
        rectangleGenerated = true;
    }
    // Set the background color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Clear the screen
    SDL_RenderClear(renderer);

    // Render the visible portion of the grid based on the camera position
    int startX = cameraX / Grid::TILE_SIZE;
    int startY = cameraY / Grid::TILE_SIZE;
    int endX = startX + Grid::GRID_SIZE;
    int endY = startY + Grid::GRID_SIZE;


    grid->render(renderer, startX, startY, endX, endY, cameraX, cameraY);

    int windowHeight;
    SDL_GetWindowSize(window, NULL, &windowHeight);

    // Render the HUD
    hud->generateHUD();

    // Render the equipment
    if (equipment->isEquipmentOpen()) {
        equipment->generateEquipment();
    }

    // Don't forget to present the renderer
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    TTF_CloseFont(font);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    delete grid;
    SDL_Quit();
}