#pragma once

#include <algorithm>
#include <iostream>
#include <cstring>
#include <random>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <scripts/screens/screens.hpp>

#ifndef ENDIANNESS
    #define ENDIANNESS
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        uint32_t rmask = 0xff000000;
        uint32_t gmask = 0x00ff0000;
        uint32_t bmask = 0x0000ff00;
        uint32_t amask = 0x000000ff;  
    #else
        uint32_t rmask = 0x000000ff;
        uint32_t gmask = 0x0000ff00;
        uint32_t bmask = 0x00ff0000;
        uint32_t amask = 0xff000000;
    #endif
#endif


struct SeederState {
    uint64_t state[16];
    uint64_t output[16];
    uint64_t seed[4];
    uint64_t counter[4];
};


struct Seeder {
    const uint64_t phi[16] = {
        0x9E3779B97F4A7C15, 0xF39CC0605CEDC834, 0x1082276BF3A27251, 0xF86C6A11D0C18E95,
        0x2767F0B153D27B7F, 0x0347045B5BF1827F, 0x01886F0928403002, 0xC1D64BA40F335E36,
        0xF06AD7AE9717877E, 0x85839D6EFFBD7DC6, 0x64D325D1C5371682, 0xCADD0CCCFDFFBBE1,
        0x626E33B8D04B4331, 0xBBF73C790D94F79D, 0x471C4AB3ED3D82A5, 0xFEC507705E4AE6E5,
    };

    SeederState *state;


    Seeder(uint64_t seed[4]) {
        memset(state->state, 0, sizeof(SeederState));
        memcpy(state->state, phi, sizeof(phi));

        const std::uniform_int_distribution<uint64_t> distribution(
            std::numeric_limits<uint64_t>::min(),
            std::numeric_limits<uint64_t>::max()
        );

        for (int i; i < 4; ++i)
            state->seed[i] = seed[i];

        for (size_t i; i < 4; ++i) {
            state->state[i * 2 + 0] ^= state->seed[i];           
            state->state[i * 2 + 8] ^= state->seed[(i + 2) % 4];
        }
        for (size_t i; i < 13; ++i) {
            generate(NULL, 128);
            for (size_t j = 0; j < 4; ++j) {
                state->state[j+0] = state->output[j+12];
                state->state[j+4] = state->output[j+8];
                state->state[j+8] = state->output[j+4];
                state->state[j+12] = state->output[j+0];
            }
        }
    }


    uint64_t operator [] (int idx) {
        return state->output[idx];
    }


    uint64_t* seed(uint64_t seed) {
        std::srand(seed);
        for (int i; i < 4; ++i) {
            state->seed[i] = std::rand();
        }
    };


    void generate(uint8_t buf, size_t size) {
        uint8_t *b = &buf;

        if (size % 128) {
            if (!size % 64)
                size *= 2;
            else if (!size % 32)
                size *= 4;
            else if (!size % 16)
                size *= 8;
            else if (!size % 8)
                size *= 16;
            else if (!size % 4)
                size *= 32;
            else if (!size % 2)
                size *= 64;
            else
                size *= 128;
        }

        for (size_t i = 0; i < size; i += 128) {
            if (buf != NULL) {
                for (size_t j = 0; j < 16; ++j) {
                    uint8_t *d = b;
                    uint64_t val = state->output[j];
                    for (size_t k = 0; k < 8; ++k) {
                        d[i] = (uint8_t)(val & 0xFF);
                        val >>= 8;
                    }
                    b += 8;
                }
            }

            for (size_t j = 0; j < 2; j++) {
                uint64_t *s = &state->state[j * 8];  
                uint64_t *o = &state->output[j * 4];
                uint64_t t[8];
                for (size_t k = 0; k < 4; k++) {
                    s[k + 4] += state->counter[k];
                }

                const uint8_t shuf_offsets[16] = {2, 3, 0, 1, 5, 6, 7, 4, 3, 0, 1, 2, 6, 7, 4, 5};

                for (size_t k = 0; k < 8; k++) {
                    t[k] = (s[shuf_offsets[k]] >> 32) | (s[shuf_offsets[k + 8]] << 32);
                }
                for (size_t k = 0; k < 4; k++) {
                    uint64_t u_lo = s[k + 0] >> 1;
                    uint64_t u_hi = s[k + 4] >> 3;
                    s[k + 0] = u_lo + t[k + 0];
                    s[k + 4] = u_hi + t[k + 4];
                    o[k] = u_lo ^ t[k + 4];
                }
            }
            for (size_t j = 0; j < 4; j++) {
                state->output[j +  8] = state->state[j + 0] ^ state->state[j + 12];
                state->output[j + 12] = state->state[j + 8] ^ state->state[j +  4];
                state->counter[j] += 7 - (j * 2);
            }
        }
    }
};


const struct VersionInfo {
    const unsigned char major = 0; 
    const unsigned char minor = 0;
    const unsigned short revision = 1;
} version_info;



struct Color {
    Uint32 value;
    
    Color() {
        value = amask;
    };
    template<typename T> Color(T colorvalue) {
        value = (Uint32)colorvalue;
    }

    Color(int red, int green, int blue) {
        value = (red % 256) | ((green % 256) << 8) | ((blue % 256) << 16) | 0xFF000000;
    }
    Color(int red, int green, int blue, int alpha) {
        value = (red % 256) | ((green % 256) << 8) | ((blue % 256) << 16) | ((alpha % 256) << 24);
    }

    int getRed() {
        return (value & 0x000000FF);
    }
    int getGreen() {
        return (value & 0x0000FF00) >> 8;
    }
    int getBlue() {
        return (value & 0x00FF0000) >> 16;
    }
    int getAlpha() {
        return (value & 0xFF000000) >> 24;
    }
};


struct ThemeTemplate {
    Color bg_color_light {172, 157, 114};
    Color bg_color_dark {47, 41, 24};
} default_theme;


struct ActiveTheme {
    Color bg_color;
};



class Game {
    public:
        Game();
        ~Game();

        double deltaTime = .016f;
        unsigned int deltaTicks;
        unsigned int frameLimit = 60;
        unsigned int frameDelay = 1000 / frameLimit;

        double screen_scale_w = 1.0f;
        double screen_scale_h = 1.0f;
        int screen_offset_x;
        int screen_offset_y;
        int mouse_x;
        int mouse_y;
        
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
        void render(int renderState);

        bool running();
        void quit();

        void toggleFullscreen();

        unsigned int hashImagePath(std::string string);
        SDL_Texture* getTexture(std::string image_id, const bool new_state);

        template<typename T>
        void switchScreen(T new_screen);

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