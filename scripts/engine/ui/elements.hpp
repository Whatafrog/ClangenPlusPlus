#pragma once

#include <functional>
#include <iostream>

#include <SDL2/SDL_image.h>

void NOCALLBACK (const int x, const int y) {};



class UiToolTip {
    public:
        std::string text;

};



class UiElement {
    public:
        bool enabled = true;
        bool visible = false;
        bool hovered = false;

        short layer;
        long int hoverTicks;

        SDL_Rect rect;
        UiToolTip* tooltip;
        
        UiElement() {};
        ~UiElement() {};

        std::string getId() {
            if (id) {
                return *id;
            } else {
                return NULL;
            }
        }
        SDL_Rect getDestinationRect() {
            return rect;
        }

        void setPosition(const short new_x, const short new_y) {
            rect.x = new_x;
            rect.y = new_y;
        }
        void setDimenseon(const short new_width, const short new_height) {
            rect.w = new_width; 
            rect.h = new_height;
        }
        void setLayer(short new_layer) { 
            layer = new_layer; 
        }

        std::function<void (const int x, const int y)> onClick;

        std::function<void (const int x, const int y)> onHover;
        std::function<void (const int x, const int y)> onHoverOff;
        std::function<void (const int x, const int y)> hoverUpdate;

    protected:
        std::string* id = nullptr;
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