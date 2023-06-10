#pragma once

#include <iostream>
#include <vector>
#include <map>

#include <SDL2/SDL_image.h>

#include <scripts/engine/ui/elements.hpp>



struct BaseScreen {
    BaseScreen() {};
    ~BaseScreen() {};

    SDL_Texture* base_texture;
    SDL_Rect base_texture_rect;

    UiElement* hoveredElement;
    std::vector<UiElement*> elements;

    virtual void openScreen() = 0;
    virtual void exitScreen() = 0;
    virtual void killScreen() = 0;
    virtual void rebuild() = 0;
    virtual void update() = 0;

    void click(const int x, const int y) {}
};



struct BaseSubscreen{
    BaseSubscreen() {};
    ~BaseSubscreen() {};
};