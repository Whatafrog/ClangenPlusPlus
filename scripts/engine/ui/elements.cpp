#include "elements.hpp"



UiImage::UiImage(const int x, const int y, const int w, const int h, SDL_Texture *n_image, SDL_Texture *n_hover_image, SDL_Texture *n_unavailable_image, std::function<void (const int x, const int y)> callback) {
    image = n_image;
    hover_image = n_hover_image;
    unavailable_image = n_unavailable_image;

    onClick = callback;

    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}
UiImage::~UiImage() {
    SDL_DestroyTexture(image);
    SDL_DestroyTexture(hover_image);
    SDL_DestroyTexture(unavailable_image);
}

SDL_Texture* UiImage::getImage() {
    if (enabled && !hovered && image)
        return image;
    else if (!enabled && unavailable_image)
        return unavailable_image;
    else if (hover_image)
        return hover_image;
    else
        return image;
}