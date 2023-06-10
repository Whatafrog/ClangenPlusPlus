#include "menu_screens.hpp"



struct StartScreen : BaseScreen {
    using BaseScreen::BaseScreen;
    UiElement* hoveredElement;

    UiElement* button_continue;
    UiElement* button_clan_switch;
    UiElement* button_clan_new;
    UiElement* button_settings;
    UiElement* button_quit;
    UiElement* social_twitter;
    UiElement* social_tumblr;
    UiElement* social_discord;

    void openScreen() {
        if (!base_texture)
            base_texture = game.getTexture("menu.png", true);

        SDL_QueryTexture(base_texture, NULL, NULL, &(base_texture_rect.w), &(base_texture_rect.h));

        button_continue = new UiElement(
            70, 310, 192, 35, game.getTexture("buttons.continue.png", false), game.getTexture("buttons.continue_hover.png", false), game.getTexture("buttons.continue_unavailable.png", false), 
            [](const int x, const int y){}
        );
        button_continue->enabled = false;

        button_clan_switch = new UiElement(
            70, 355, 192, 35, game.getTexture("buttons.switch_clan.png", false), game.getTexture("buttons.switch_clan_hover.png", false), game.getTexture("buttons.switch_clan_unavailable.png", false),
            [](const int x, const int y){}
        );
        button_clan_switch->enabled = false;

        button_clan_new = new UiElement(
            70, 400, 192, 35, game.getTexture("buttons.new_clan.png", false), game.getTexture("buttons.new_clan_hover.png", false), game.getTexture("buttons.new_clan_unavailable.png", false),
            [](const int x, const int y){}
        );
        button_settings = new UiElement(
            70, 445, 192, 35, game.getTexture("buttons.settings.png", false), game.getTexture("buttons.settings_hover.png", false), game.getTexture("buttons.settings_unavailable.png", false),
            [](const int x, const int y){game.switchScreen(settings_screen);}
        );
        button_quit = new UiElement(
            70, 490, 192, 35, game.getTexture("buttons.quit.png", false), game.getTexture("buttons.quit_hover.png", false), game.getTexture("buttons.quit_unavailable.png", false),
            [](const int x, const int y){game.quit();}
        );
        social_twitter = new UiElement(
            15, 650, 40, 40, game.getTexture("buttons.twitter.png", false), game.getTexture("buttons.twitter_hover.png", false), game.getTexture("buttons.twitter_unavailable.png", false),
            [](const int x, const int y){SDL_OpenURL("https://twitter.com/OfficialClangen");}
        );
        social_tumblr = new UiElement(
            60, 650, 40, 40, game.getTexture("buttons.tumblr.png", false), game.getTexture("buttons.tumblr_hover.png", false), game.getTexture("buttons.tumblr_unavailable.png", false),
            [](const int x, const int y){SDL_OpenURL("https://officialclangen.tumblr.com/");}
        );
        social_discord = new UiElement(
            105, 650, 40, 40, game.getTexture("buttons.discord.png", false), game.getTexture("buttons.discord_hover.png", false), game.getTexture("buttons.discord_unavailable.png", false),
            [](const int x, const int y){SDL_OpenURL("https://discord.com/invite/clangen");}
        );

        for (auto element : {button_continue, button_clan_switch, button_clan_new, button_settings, button_quit, social_twitter, social_tumblr, social_discord}) {
            elements.push_back(element);
        }
    }
    void exitScreen() {
        elements.clear();
    }
    void killScreen() {
        SDL_DestroyTexture(base_texture);
    }
    void rebuild() {
        SDL_RenderCopy(game.renderer, base_texture, NULL, &base_texture_rect);
        SDL_SetRenderTarget(game.renderer, base_texture);

        for (auto element : elements)
            element->build();

        SDL_SetRenderTarget(game.renderer, NULL);
    }
    void update() {

    }
};



struct SwitchClanScreen : BaseScreen {
    using BaseScreen::BaseScreen;
    UiElement* hoveredElement;

    void openScreen() {

    }
    void exitScreen() {

    }
    void killScreen() {

    }
    void rebuild() {

    }
    void update() {

    }
};



struct NewClanScreen : BaseScreen {
    using BaseScreen::BaseScreen;
    UiElement* hoveredElement;

    void openScreen() {

    }
    void exitScreen() {

    }
    void killScreen() {

    }
    void rebuild() {

    }
    void update() {

    }
};



struct SettingsScreen : BaseScreen {
    using BaseScreen::BaseScreen;
    UiElement* hoveredElement;

    UiElement* button_settings;
    UiElement* button_settings_save;
    UiElement* button_settings_relation;
    UiElement* button_language;
    UiElement* button_info;
    UiElement* button_main_menu;

    void openScreen() {
        if (!base_texture)
            SDL_GetWindowSize(game.window, &base_texture_rect.w, &base_texture_rect.h);
            base_texture = SDL_CreateTexture(game.renderer, 0, 0, base_texture_rect.w, base_texture_rect.h);
        
        button_settings = new UiElement(
            100, 100, 150, 30, game.getTexture("buttons.general_settings.png", false), game.getTexture("buttons.general_settings_hover.png", false), game.getTexture("buttons.general_settings_unavailable.png", false), 
            [](const int x, const int y){}
        );
        button_settings_save = new UiElement(
            327, 550, 146, 30, game.getTexture("buttons.save_settings.png", false), game.getTexture("buttons.save_settings_hover.png", false), game.getTexture("buttons.save_settings_unavailable.png", false), 
            [](const int x, const int y){}
        );
        button_settings_relation = new UiElement(
            250, 100, 150, 30, game.getTexture("buttons.relation_settings.png", false), game.getTexture("buttons.relation_settings_hover.png", false), game.getTexture("buttons.relation_settings_unavailable.png", false), 
            [](const int x, const int y){}
        );
        button_language = new UiElement(
            550, 100, 150, 30, game.getTexture("buttons.language.png", false), game.getTexture("buttons.language_hover.png", false), game.getTexture("buttons.language_unavailable.png", false), 
            [](const int x, const int y){}
        );
        button_info = new UiElement(
            400, 100, 150, 30, game.getTexture("buttons.info.png", false), game.getTexture("buttons.info_hover.png", false), game.getTexture("buttons.info_unavailable.png", false), 
            [](const int x, const int y){}
        );
        button_main_menu = new UiElement(
            25, 25, 150, 30, game.getTexture("buttons.main_menu.png", false), game.getTexture("buttons.main_menu_hover.png", false), game.getTexture("buttons.main_menu_unavailable.png", false), 
            [](const int x, const int y){game.switchScreen(start_screen);}
        );

        for (auto element : {button_settings, button_settings_save, button_settings_relation, button_language, button_info, button_main_menu}) {
            elements.push_back(element);
        }
    };
    void exitScreen() {
        delete button_settings, button_settings_save, button_settings_relation, button_language, button_info, button_main_menu;
    };
    void killScreen() {
        SDL_DestroyTexture(base_texture);
    };
    void rebuild() {
        SDL_RenderCopy(game.renderer, base_texture, &base_texture_rect, NULL);

        SDL_SetRenderTarget(game.renderer, base_texture);

        SDL_RenderFillRect(game.renderer, NULL);

        for (auto element : {button_settings, button_settings_save, button_settings_relation, button_language, button_info, button_main_menu}) {
            SDL_RenderCopy(game.renderer, element->getImage(), &base_texture_rect, &element->rect);
        }

        SDL_SetRenderTarget(game.renderer, NULL);
    }
    void update() {

    };
};



BaseScreen* start_screen = new StartScreen();
BaseScreen* switch_clan_screen = new SwitchClanScreen();
BaseScreen* new_clan_screen = new NewClanScreen();
BaseScreen* settings_screen = new SettingsScreen();