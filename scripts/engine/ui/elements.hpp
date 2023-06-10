#pragma once

#include <functional>
#include <iostream>
#include <variant>
#include <vector>
#include <map>

#include <SDL2/SDL_image.h>


struct UiToolTip {
    std::string text;

};



struct UiElement {
    UiElement(const int x, const int y, const int w, const int h, SDL_Texture *n_image, SDL_Texture *n_hover_image, SDL_Texture *n_unavailable_image, std::function<void (const int x, const int y)> callback);
    ~UiElement() {
        SDL_DestroyTexture(image);
        SDL_DestroyTexture(hover_image);
        SDL_DestroyTexture(unavailable_image);
    }

    bool enabled = true;
    bool hovered = false;
    bool visible = false;

    SDL_Texture* image;
    SDL_Texture* hover_image;
    SDL_Texture* unavailable_image;

    SDL_Rect rect;
    UiToolTip* tooltip;

    std::function<void (const int x, const int y)> onClick;

    void onHover(const int x, const int y);
    void onHoverOff(const int x, const int y);

    void build();

    SDL_Texture* getImage() {
        if (enabled && !hovered && image)
            return image;
        else if (!enabled && unavailable_image)
            return unavailable_image;
        else if (hover_image)
            return hover_image;
        else
            return image;
    }
};