#include "elements.hpp"

#include <scripts/game.hpp>

UiElement::UiElement(const int x, const int y, const int w, const int h, SDL_Texture *n_image, SDL_Texture *n_hover_image, SDL_Texture *n_unavailable_image, std::function<void (const int x, const int y)> callback) {
    rect = SDL_Rect {x, y, w, h};
    
    image = n_image;
    hover_image = n_hover_image;
    unavailable_image = n_unavailable_image;

    onClick = callback;
}


void UiElement::onHover(const int x, const int y) {
    SDL_RenderCopy(game.renderer, hover_image, NULL, &rect);
};
void UiElement::onHoverOff(const int x, const int y) {
    SDL_RenderCopy(game.renderer, image, NULL, &rect);
};
void UiElement::build() {
    SDL_RenderCopy(game.renderer, getImage(), NULL, &rect);
};