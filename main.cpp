#include "scripts/game.cpp"



int main(int argc, char *argv[]) {
    float ticks, ticks_prev, tick_delta;

    game = new Game();
    game->init(800, 700);

    ticks_prev = SDL_GetTicks64();
    while (game->running()) {
        ticks = SDL_GetTicks64();
        tick_delta = ticks - ticks_prev;
        ticks_prev = ticks;
        game->deltaTime = tick_delta;

        game->handleEvents();
        game->update();
        game->render();
    }

    game->clean();
    delete game;

    return 0;
}