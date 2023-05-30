#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <map>

class Game {
    public:
        Game();
        ~Game();

        short init(int width, int height);

        void handleEvents();
        void update();
        void render();
        void clean();
        bool running();

        void loadImageCache(SDL_Renderer *__renderer);
        SDL_Texture * getImage(std::string image_id);
        SDL_Texture * getImage(unsigned int id);

        float frameLimit = 60.0f;
        float deltaTime = .0f;

    private:
        bool fullscreenState = false;
        bool isRunning;

        SDL_Renderer *renderer = nullptr;
        SDL_Window *window = nullptr;

        std::map<unsigned int, SDL_Texture *> image_cache;
        std::map<std::string, unsigned int> image_cache_map;
};

Game* game = nullptr;

#endif