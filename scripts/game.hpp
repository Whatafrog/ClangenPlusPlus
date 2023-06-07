#pragma once

#include <iostream>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <scripts/screens/screens.hpp>

const struct versionInfo {
    const unsigned short major = 0; 
    const unsigned short minor = 0;
    const unsigned short revision = 0;
    const char* label = "Whole lotta effort!";
} version_info;



struct Color {
    unsigned short r = 0;
    unsigned short g = 0;
    unsigned short b = 0;

    Color() {}
    Color(int value) {
        value %= 16777216;
        r = (value & 0xFF000000) >> 24;
        g = (value & 0x00FF0000) >> 16;
        b = (value & 0x0000FF00) >> 8;
    }
    Color(int red, int green, int blue) {
        r = red;
        g = green;
        b = blue;
    }
};


struct ThemeTemplate {
    Color bg_color_light {172, 157, 114};
    Color bg_color_dark {47, 41, 24};
} default_theme;


struct ActiveTheme {
    Color bg_color {};
};



class Game {
    public:
        Game();
        ~Game();

        double deltaTime;
        unsigned int deltaTicks;
        unsigned int frameLimit = 60;
        unsigned int frameDelay = 1000 / frameLimit;

        int mouse_x, mouse_y;
        
        SDL_Renderer* renderer = nullptr;
        unsigned short renderState = 0;

        SDL_Window* window = nullptr;
        SDL_Rect windowRect;

        BaseScreen* currentScreen;
        BaseScreen* lastScreen;

        ThemeTemplate theme_template;
        ActiveTheme theme;

        bool darkModeEnabled;

        short init(short width, short height);
        short load();

        void update();
        void render();

        bool running();
        void quit();

        void toggleFullscreen();

        unsigned int hashImagePath(std::string string);
        SDL_Texture* getTexture(std::string image_id, const bool new_state);

        void switchScreen(BaseScreen* new_screen);

        void setTheme(ThemeTemplate new_theme);
        void setThemeLight();
        void setThemeDark();




    private:
        bool fullscreenState = false;
        bool isRunning;

        std::map<int, SDL_Texture*> image_registry;
        std::map<int, int> image_hash_alias;
};


Game game;