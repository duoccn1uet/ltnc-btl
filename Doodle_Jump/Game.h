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

/// Platforms
const int MAX_PLATFORMS_PER_FRAME = 20;
const int MIN_PLATFORMS_PER_FRAME = 10;
const int MAX_PLATFOMRS_DIST = d_JumpHeight;
const int SQR_MAX_PLATFOMRS_DIST = MAX_PLATFOMRS_DIST * MAX_PLATFOMRS_DIST;

/// Items
const int MAX_ITEMS_PER_FRAME = 5;

const int DIFFICULTY = 5000;

const int SCROLL_LINE = SCREEN_HEIGHT / 4;

class Game
{
public:

    /// whenever adding an element, please add new defition in main.cp

    Game();
    Game(const string& _MAP_NAME);
    ~Game();

    void ShowMenu();

private:

    /// Variables
    ImgProcess background;
    ImgProcess top_frame;
    Character character;
    
    /// Platform

    Platform platforms[MAX_PLATFORMS_PER_FRAME];
    int low_y_dist;
    int high_y_dist;
    int n_platforms = 0;
    int highest_free_platform = 0;

    PlatformType GenPlatformType();
    void GenPlatform(int i);
    int Gen_nplatforms();
    void InitPlatforms();

    /// Items
    Item items[MAX_ITEMS_PER_FRAME];
    int cnt_item[size_t(ItemType::nItemType)];
    int n_items = 0;

    ItemType GenItemType();
    bool GenItem(int i);
    int Gen_nitems();
    void InitItems();

    Timer timer;

    /// score
    Text show_score;
    int d_score = 0;

    /// menu
    Menu menu;
    Mix_Music *menu_sound = nullptr;

    ///string MAP_NAME;

    /// Functions
    void Init();
    void ShowScore();
    bool LoadOption(const MenuOption& option);
    int ScrollMap();
    void GenObjects();
    void PlayGame();
    void EndGame();
};

#endif // GAME_H

