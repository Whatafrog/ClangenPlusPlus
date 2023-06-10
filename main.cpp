#include <scripts/game.cpp>

int main(int argc, char *argv[]) {
    //SystemInit(system_info);
    std::filesystem::current_path(SDL_GetBasePath());

    if (game.init(800, 700) || game.load()) {
        return -1;
    }

    float deltaTime;
    int frameTime;
    Uint64 newTicks, currentTicks = SDL_GetTicks64();

    game.switchScreen(start_screen);
    game.setTheme(default_theme);
    
    while (game.running()) {

        newTicks = SDL_GetTicks64();
        frameTime = newTicks - currentTicks;
        currentTicks = newTicks;

        game.update();
        if (game.renderState)
            game.render(game.renderState);

        SDL_Delay(16); //temporary fix to overuse of gpu and cpu (equivilent of 100 fps)
    }

    return 0;
}