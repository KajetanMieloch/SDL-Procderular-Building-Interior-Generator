#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

class Rectangle {
private:
    SDL_Rect rect;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    int x;
    int y;
    int w;
    int h;

public:
    Rectangle(SDL_Renderer* renderer, int x, int y, int w, int h);
    ~Rectangle();
    void render();
    void setX(int x);
    void setY(int y);
    void setW(int w);
    void setH(int h);
    int getX() { return x; }
    int getY() { return y; }
    int getW() { return w; }
    int getH() { return h; }

};


#endif /* GAME_HPP */
