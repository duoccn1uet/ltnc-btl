#ifndef GAME_H
#define GAME_H

#include "CommonFunc.h"
#include "ImgProcess.h"
#include "Platform.h"
#include "Character.h"
#include "Timer.h"
#include "Map.h"
#include "Text.h"
#include "Menu.h"
#include "Motion.h"

class Game
{
public:

    /// whenever adding an element, please add new defition in main.cpp

    ImgProcess background;
    Character character;
    Platform platform;
    Timer timer;
    Map _map;
    Text show_score;
    Menu menu;
    Mix_Music *menu_sound = nullptr;

    string MAP_NAME;

    Game();
    Game(const string& _MAP_NAME);
    ~Game();

    void Init(SDL_Renderer* renderer);
    void ShowScore(SDL_Renderer* renderer);
    void LoadOption(SDL_Renderer* renderer, const MenuOption& option, const string& font_path, const string& menu_path);
    void ShowMenu(SDL_Renderer* renderer, const string& font_path, const string& menu_path);

private:
};

#endif // GAME_H

