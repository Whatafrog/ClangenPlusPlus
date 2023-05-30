#include <filesystem>
#include <algorithm>
#include <iostream>
#include <string>

#include <SDL2/SDL_image.h>

#include "game.hpp"

short systemInfo::getSystem() {
    #ifdef _WIN32
    return win32;
    #elif _WIN64
    return win64;
    #elif __APPLE__ || __MACH__
    return macOS;
    #elif __linux__
    return linux;
    #elif __unix || __unix__
    return unix;
    #else
    return NULL;
    #endif
} 

std::string systemInfo::getName(const int type) {
    switch (type) {
        case win32:
            return "Windows 32-bit";
        case win64:
            return "Windows 64-bit";
        case macOS:
            return "macOS";
        case linux:
            return "Linux";
        case unix:
            return "Unix";
        default:
            return "Unsupported System";
    }
}



Game::Game() {}
Game::~Game() {}

short Game::init(int width, int height) {

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow("Clangen++", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
        renderer = SDL_CreateRenderer(window, -1, 0);

        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        } else {
            std::cout << "Error during SDL_Renderer creation: " << SDL_GetError() << "\n";
            return -2;
        }

        isRunning = true;
        std::cout << "SDL2 lib initialised!\n";
    } 
    else {
        isRunning = false;
        std::cout << "Error during SDL2 lib initialisation: " << SDL_GetError() << "\n";
        return -1;
    }

    loadImageCache(renderer);
    return 0;
}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;

        case SDL_KEYUP:
            switch (event.key.keysym.sym) {
                case SDLK_F11:
                    SDL_SetWindowFullscreen(window, ((fullscreenState) ? 0 : SDL_WINDOW_FULLSCREEN_DESKTOP));
                    fullscreenState = !fullscreenState;
                    break;
                
                default:
                    break;
            }
            break;
        
        default:
            break;
    }
}

void Game::update() {
}

void Game::render() {
    SDL_RenderClear(renderer);

    SDL_Rect texture_rect;
    texture_rect.x = 0;
    texture_rect.y = 0;
    texture_rect.w = 800;
    texture_rect.h = 700;

    SDL_RenderCopy(renderer, getImage("menu.png"),  NULL, &texture_rect);

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

bool Game::running() {
    return isRunning;
}

void Game::loadImageCache(SDL_Renderer *__renderer) {
    std::string image_id;
    const char * strPath {};
    unsigned int id;

    for (auto & file : std::filesystem::recursive_directory_iterator("resources\\images")) {
        std::filesystem::path filePath = file;

        if (filePath.extension() == ".png") {
            SDL_Texture* texture = IMG_LoadTexture(__renderer, filePath.string().c_str());

            if (!texture) {
                std::cout << "Failed to load image " << filePath << ", error: " << SDL_GetError() << "\n";
            }

            image_id = filePath.string();
            std::replace(image_id.begin(), image_id.end(), '\\', '.');
            image_id = image_id.substr(17);

            image_cache[++id] = texture;
            image_cache_map[image_id] = id;
        }
    }
}

SDL_Texture * Game::getImage(std::string image_id) {
    if (image_cache_map.count(image_id)) {
        return image_cache[image_cache_map[image_id]];
    } else {
        return NULL;
    }
}

SDL_Texture * Game::getImage(unsigned int id) {
    if (image_cache.count(id)) {
        return image_cache[id];
    } else {
        return NULL;
    }
}

