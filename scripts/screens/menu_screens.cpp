#include <scripts/game.hpp>
#include <scripts/screens/screens.hpp>
#include <scripts/engine/ui/elements.hpp>


class SettingsScreen : public BaseScreen {
    public:
        using BaseScreen::BaseScreen;

        UiImage* button_settings;
        UiImage* button_settings_save;
        UiImage* button_settings_relation;
        UiImage* button_language;
        UiImage* button_info;

        void openScreen() {
            SDL_RenderFillRect(game.renderer, NULL);
        };
        void exitScreen() {

        };
        void rebuild() {

        };
        void update() {

        };
        void hover(const int x, const int y) {

        };
        void click(const int x, const int y)  {

        };
};

BaseScreen* settings_screen = new SettingsScreen();



class StartScreen : public BaseScreen {
    public:
        using BaseScreen::BaseScreen;

        SDL_Texture* base_texture;
        SDL_Rect base_texture_rect;

        UiElement* hoveredElement;

        UiImage* button_continue;
        UiImage* button_clan_switch;
        UiImage* button_clan_new;
        UiImage* button_settings;
        UiImage* button_quit;
        UiImage* social_twitter;
        UiImage* social_tumblr;
        UiImage* social_discord;

        void openScreen() {
            base_texture = game.getTexture("menu.png", true);

            SDL_QueryTexture(base_texture, NULL, NULL, &(base_texture_rect.w), &(base_texture_rect.h));

            button_continue = new UiImage(
                70, 310, 192, 35, game.getTexture("buttons.continue.png", false), game.getTexture("buttons.continue_hover.png", false), game.getTexture("buttons.continue_unavailable.png", false), 
                [](const int x, const int y){}
            );
            button_continue->enabled = false;

            button_clan_switch = new UiImage(
                70, 355, 192, 35, game.getTexture("buttons.switch_clan.png", false), game.getTexture("buttons.switch_clan_hover.png", false), game.getTexture("buttons.switch_clan_unavailable.png", false),
                [](const int x, const int y){}
            );
            button_clan_switch->enabled = false;

            button_clan_new = new UiImage(
                70, 400, 192, 35, game.getTexture("buttons.new_clan.png", false), game.getTexture("buttons.new_clan_hover.png", false), game.getTexture("buttons.new_clan_unavailable.png", false),
                [](const int x, const int y){}
            );
            button_settings = new UiImage(
                70, 445, 192, 35, game.getTexture("buttons.settings.png", false), game.getTexture("buttons.settings_hover.png", false), game.getTexture("buttons.settings_unavailable.png", false),
                [](const int x, const int y){game.switchScreen(settings_screen);}
            );
            button_quit = new UiImage(
                70, 490, 192, 35, game.getTexture("buttons.quit.png", false), game.getTexture("buttons.quit_hover.png", false), game.getTexture("buttons.quit_unavailable.png", false),
                [](const int x, const int y){game.quit();}
            );
            social_twitter = new UiImage(
                15, 650, 40, 40, game.getTexture("buttons.twitter.png", false), game.getTexture("buttons.twitter_hover.png", false), game.getTexture("buttons.twitter_unavailable.png", false),
                [](const int x, const int y){SDL_OpenURL("https://twitter.com/OfficialClangen");}
            );
            social_tumblr = new UiImage(
                60, 650, 40, 40, game.getTexture("buttons.tumblr.png", false), game.getTexture("buttons.tumblr_hover.png", false), game.getTexture("buttons.tumblr_unavailable.png", false),
                [](const int x, const int y){SDL_OpenURL("https://officialclangen.tumblr.com/");}
            );
            social_discord = new UiImage(
                105, 650, 40, 40, game.getTexture("buttons.discord.png", false), game.getTexture("buttons.discord_hover.png", false), game.getTexture("buttons.discord_unavailable.png", false),
                [](const int x, const int y){SDL_OpenURL("https://discord.com/invite/clangen");}
            );
        }
        void exitScreen() {
            SDL_DestroyTexture(base_texture);

            delete button_continue, button_clan_switch, button_clan_new, button_settings, button_quit, social_twitter, social_tumblr, social_discord;
        }
        void rebuild() {
            SDL_RenderCopy(game.renderer, base_texture, &base_texture_rect, NULL);

            SDL_SetRenderTarget(game.renderer, base_texture);

            for (auto element : {button_continue, button_clan_switch, button_clan_new, button_settings, button_quit, social_twitter, social_tumblr, social_discord})
                SDL_RenderCopy(game.renderer, element->getImage(), &base_texture_rect, &element->rect);

            SDL_SetRenderTarget(game.renderer, NULL);
        }
        void update() {

        }
        void hover(const int x, const int y) {
            for (auto element : {button_continue, button_clan_switch, button_clan_new, button_settings, button_quit, social_twitter, social_tumblr, social_discord}) {
                if (element->enabled) {
                    SDL_Rect rect = element->rect;
                    bool isHovered = rect.x < x && rect.y < y && x <= (rect.w + rect.x) && y <= (rect.h + rect.y);

                    if (isHovered) {
                        element->hovered = true;
                        hoveredElement = element;
                        SDL_RenderCopy(game.renderer, element->hover_image, &base_texture_rect, &rect);
                        game.renderState = 2;
                    }
                    else if (!isHovered && element->hovered) {
                        element->hovered = false;
                        SDL_RenderCopy(game.renderer, element->image, &base_texture_rect, &rect);
                        game.renderState = 2;

                        if (hoveredElement == element)
                            hoveredElement = NULL;
                    }
                }
            }
        }
        void click(const int x, const int y) {
            if (hoveredElement)
                hoveredElement->onClick(x, y);
        }
};

BaseScreen* start_screen = new StartScreen();