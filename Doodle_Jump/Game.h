#ifndef GAME_H
#define GAME_H

#include "CommonFunc.h"
#include "ImgProcess.h"
#include "Platform.h"
#include "Character.h"
#include "Timer.h"
#include "Text.h"
#include "Menu.h"
#include "Motion.h"
#include "Item.h"

const int MAX_PLATFORMS_PER_FRAME = 20;
const int MIN_PLATFORMS_PER_FRAME = 10;

const int DIFFICULTY = 5000;

const int SCROLL_LINE = SCREEN_HEIGHT / 4;

class Game
{
public:

    /// whenever adding an element, please add new defition in main.cp

    Game();
    Game(const string& _MAP_NAME);
    ~Game();

    void ShowMenu(SDL_Renderer*& renderer);

private:

    /// Variables
    ImgProcess background;
    Character character;
    
    /// Platform
    Platform platforms[MAX_PLATFORMS_PER_FRAME];
    int low_dist = 10;
    int high_dist = d_JumpHeight/3;
    int n_platforms;

    Timer timer;

    /// score
    Text show_score;
    int d_score = 0;

    /// menu
    Menu menu;
    Mix_Music *menu_sound = nullptr;

    string MAP_NAME;

    /// Functions
    void Init(SDL_Renderer*& renderer);
    void GenPlatform(int i, SDL_Renderer*& renderer);
    void InitPlatform(SDL_Renderer*& renderer);
    void ShowScore(SDL_Renderer*& renderer);
    bool LoadOption(SDL_Renderer*& renderer, const MenuOption& option);
    int ScrollMap(SDL_Renderer*& renderer);
    void PlayGame(SDL_Renderer*& renderer);
    void EndGame(SDL_Renderer*& renderer);
};

#endif // GAME_H

