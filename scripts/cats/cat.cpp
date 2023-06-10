#include "cat.hpp"

Cat::Cat() {
    sprite = SDL_CreateTextureFromSurface(game.renderer, SDL_CreateRGBSurface(0, 50, 50, 32, rmask, gmask, bmask, amask));
}