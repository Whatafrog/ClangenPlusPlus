#include <filesystem>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include <scripts/game.hpp>

#include <scripts/engine/ui/elements.cpp>
#include <scripts/screens/screens.cpp>
#include <scripts/screens/menu_screens.cpp>


Game::Game() {}
Game::~Game() {}

short Game::init(short width, short height) {
    const Uint32 window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
    const Uint32 renderer_flags = SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        window = SDL_CreateWindow("Clangen++", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, window_flags);
        renderer = SDL_CreateRenderer(window, -1, renderer_flags);


        isRunning = true;
        std::cout << "Running on C++ 17 SDL 2.26.3\n";
    } 
    else {
        isRunning = false;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "RuntimeError", SDL_GetError(), NULL);
        return 1;
    }
    return 0;
}

short Game::load() {
    int image_hash, new_image_hash, hash_collisions, idCounter;
    std::filesystem::path filePath;
    std::string image_id;
    
    SDL_Texture* texture;

    std::map<int, bool> used_hash;

    for (const std::filesystem::__cxx11::directory_entry file : std::filesystem::recursive_directory_iterator("resources\\images")) {
        filePath = file;

        if (filePath.extension() == ".png") {
            texture = IMG_LoadTexture(renderer, filePath.string().c_str());

            if (!texture) {
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "RuntimeError", ("Failed to load image " + filePath.string() + ", reason:\n" + SDL_GetError()).c_str(), window);
                return 1;
            }

            SDL_DestroyTexture(texture);

            image_id = (filePath.string()).substr(17);
            std::replace(image_id.begin(), image_id.end(), '\\', '.');

            image_hash = hashImagePath(image_id); 

            if (image_registry.count(image_hash)) {
                while (image_hash_alias.count(new_image_hash)) {
                    new_image_hash += 1;
                }
                if (used_hash.count(new_image_hash)) {
                    SDL_ShowSimpleMessageBox(
                        SDL_MESSAGEBOX_ERROR, "DoubleHashCollisionError", 
                        "You've received a rare double hash collision error, restart the game and it should work fine.\nIf it occurs more than 3 times- please let me know in the Clangen discord!", NULL
                    );
                    return 2;
                }
                image_hash_alias[image_hash] = new_image_hash;
                image_hash = new_image_hash;
                hash_collisions += 1;
            }

            image_registry[image_hash] = NULL;
        }
    }
    std::cout << hash_collisions << " hash collisions in resources.images when loading\n";
    image_registry.clear();
    used_hash.clear();
    return 0;
}

void Game::update() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                game.quit();
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_F11:
                        game.toggleFullscreen();
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYDOWN:
                break;
            case SDL_MOUSEMOTION:
                SDL_GetMouseState(&mouse_x, &mouse_y);
                currentScreen->hover(mouse_x, mouse_y);
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                    currentScreen->click(mouse_x, mouse_y);
                break;
            default:
                break;
        }
    }
}

void Game::render() {
    switch (renderState) {
        case 1:
            SDL_SetRenderDrawColor(renderer, theme.bg_color.r, theme.bg_color.g, theme.bg_color.b, 255);
            SDL_RenderClear(renderer);
            currentScreen->rebuild();
            SDL_RenderPresent(renderer);
            game.renderState = 0;
            break;
        case 2:
            SDL_RenderPresent(renderer);
            game.renderState = 0;
        default:
            break;
    }
}

bool Game::running() {
    return isRunning;
}

void Game::quit() {
    isRunning = false;

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    if (lastScreen)
        lastScreen->exitScreen();
    currentScreen->exitScreen();

    SDL_Quit();
}

void Game::toggleFullscreen() {
    if (fullscreenState) {
        SDL_SetWindowFullscreen(game.window, 0);
    } else {
        SDL_SetWindowFullscreen(game.window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    }
    fullscreenState = !fullscreenState;
}

unsigned int Game::hashImagePath(std::string string) {
    const unsigned int length = string.length();
    unsigned int hash;
    for (unsigned short i; i < length; ++i) {
        hash += string[i] * 129^(length-i);
        hash *= log2((short)string[i-1]);
    }
    return hash;
}

SDL_Texture* Game::getTexture(std::string image_id, const bool persistent) {
    int hash = hashImagePath(image_id);
    SDL_Texture *existing_texture;
    SDL_Texture *texture;

    if (image_hash_alias.count(hash))
        hash = image_hash_alias[hash];

    if (image_registry.count(hash)) {
        texture = image_registry[hash];
    }
    else {
        std::replace(image_id.begin(), image_id.end() - (image_id.length()-image_id.find_last_of(".")), '.', '\\');
        texture = IMG_LoadTexture(renderer, ("resources\\images\\" + image_id).c_str());
    }

    if (persistent)
        image_registry[hash] = texture;
    else
        image_registry.erase(hash);
    return texture;
}

void Game::switchScreen(BaseScreen* new_screen) {
    SDL_RenderClear(renderer);
    if (lastScreen)
        lastScreen->exitScreen();
    lastScreen = currentScreen;

    currentScreen = new_screen;
    currentScreen->openScreen();
    game.renderState = 1;
}

void Game::setTheme(ThemeTemplate new_theme) {
    theme_template = new_theme;
    if (darkModeEnabled)
        setThemeDark();
    else
        setThemeLight();
    SDL_SetRenderDrawColor(renderer, theme.bg_color.r, theme.bg_color.g, theme.bg_color.b, 0);
}
void Game::setThemeLight() {
    darkModeEnabled = false;
    theme.bg_color = theme_template.bg_color_light;
}
void Game::setThemeDark() {
    darkModeEnabled = true;
    theme.bg_color = theme_template.bg_color_dark;
}