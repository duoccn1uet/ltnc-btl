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
#include "Item.h"

class Game
{
public:

    /// whenever adding an element, please add new defition in main.cp

    Game();
    Game(const string& _MAP_NAME);
    ~Game();

    void Init(SDL_Renderer*& renderer);
    void ShowScore(SDL_Renderer*& renderer);
    bool LoadOption(SDL_Renderer*& renderer, const MenuOption& option);
    void ShowMenu(SDL_Renderer*& renderer);
    void PlayGame(SDL_Renderer*& renderer);
    void EndGame(SDL_Renderer*& renderer);

private:

    ImgProcess background;
    Character character;
    Platform platform;
    Timer timer;
    Map _map;
    Text show_score;
    int d_score = 0;
    Menu menu;
    Mix_Music *menu_sound = nullptr;

    string MAP_NAME;
};

#endif // GAME_H

