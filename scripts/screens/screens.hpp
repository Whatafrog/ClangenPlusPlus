#pragma once

#include <iostream>
#include <map>

#include <SDL2/SDL_image.h>

#include <scripts/game.hpp>



class BaseScreen {
    public:
        BaseScreen() {};
        ~BaseScreen() {};

        virtual void openScreen() = 0;
        virtual void exitScreen() = 0;
        virtual void rebuild() = 0;
        virtual void update() = 0;
        virtual void hover(const int x, const int y) = 0;
        virtual void click(const int x, const int y) = 0;
};


class BaseSubscreen{
    public:
        BaseSubscreen() {};
        ~BaseSubscreen() {};
};