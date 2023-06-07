#pragma once

#include <functional>
#include <iostream>

#include <SDL2/SDL_image.h>



class UiToolTip {
    public:
        std::string text;

};



class UiElement {
    public:
        UiElement() {};
        ~UiElement() {};

        bool enabled = true;
        bool hovered = false;
        bool visible = false;

        short layer;

        SDL_Rect rect;
        UiToolTip* tooltip;


        std::function<void (const int x, const int y)> onClick;
        std::function<void (const int x, const int y)> onClickOff;
        std::function<void (const int x, const int y)> ClickHold;

        std::function<void (const int x, const int y)> onHover;
        std::function<void (const int x, const int y)> onHoverOff;
        std::function<void (const int x, const int y)> duringHover;

};



class UiImage : public UiElement {
    public:
        UiImage(const int x, const int y, const int w, const int h, SDL_Texture *n_image, SDL_Texture *n_hover_image, SDL_Texture *n_unavailable_image, std::function<void (const int x, const int y)> callback);
        ~UiImage();

        SDL_Texture* image;
        SDL_Texture* hover_image;
        SDL_Texture* unavailable_image;

        bool enabled = true;
        bool hovered = false;

        void setDimenseon(const short new_width, const short new_height);

        SDL_Texture* getImage();

};