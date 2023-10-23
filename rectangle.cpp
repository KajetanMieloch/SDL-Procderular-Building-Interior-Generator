#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(SDL_Renderer* renderer, int x, int y, int w, int h) : renderer(renderer), x(x), y(y), w(w), h(h) {
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    texture = IMG_LoadTexture(renderer, "src/rectangle.png");
    std::cout << "Rectangle texture: " << texture << std::endl;
}

Rectangle::~Rectangle() {
    SDL_DestroyTexture(texture);
}

void Rectangle::render() {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Rectangle::setX(int x) {
    this->x = x;
    rect.x = x;
}

void Rectangle::setY(int y) {
    this->y = y;
    rect.y = y;
}

void Rectangle::setW(int w) {
    this->w = w;
    rect.w = w;
}

void Rectangle::setH(int h) {
    this->h = h;
    rect.h = h;
}