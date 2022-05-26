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
#include "Threat.h"

/// Platforms
const int MAX_PLATFORMS_PER_FRAME = 20;
const int MIN_PLATFORMS_PER_FRAME = 10;
const int MAX_PLATFOMRS_DIST = 1.5*d_JumpHeight;
const int SQR_MAX_PLATFOMRS_DIST = MAX_PLATFOMRS_DIST * MAX_PLATFOMRS_DIST;

/// Items
const int MAX_ITEMS_PER_FRAME = 5;
///const string ItemTypeText[] = {"coin", "rocket", "springs"};
const int MAX_ITEM_TYPE_PER_FRAME[] = {3, 0, 2};

/// Threats
const int MAX_THREATS_PER_FRAME = 3;
/// const string ThreatTypeText[] = {"fly", "move_on_platform", "jump"};
const int MAX_THREAT_TYPE_PER_FRAME[] = {1, 1, 1};

/// Score
const float PIXEL_PER_SCORE = 3;

/// In game
const vector <OPTION> InGameOptions = {OPTION::PAUSE_BUTTON};
const int InGameOptionsX[] = {SCREEN_WIDTH-50};
const int InGameOptionsY[] = {0};
enum class InGameOptionsPack: short
{
    GAME_PAUSED, nInGameOptionsPack
};
const vector <string> InGameOptionsPackText = {"Game Paused"};
const int InGameOptionsPackX[] = {SCREEN_WIDTH/2 - 85};
const int InGameOptionsPackY[] = {SCREEN_HEIGHT/2 - 70};
const vector <vector<OPTION>> OptionsInInGameOptionsPack = {{OPTION::REPLAY_BUTTON, OPTION::RESUME_BUTTON, OPTION::HOME}};

const int SCROLL_LINE = SCREEN_HEIGHT / 4;

class Game
{
public:

    Game();
    Game(const string& _MAP_NAME);
    ~Game();

    void Start();

private:

    /// Variables
    ImgProcess background;
    ImgProcess top_frame;
    Character character;
    
    /// Platform

    Platform platforms[MAX_PLATFORMS_PER_FRAME];
    int low_y_dist = 0;
    int high_y_dist = 0;
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

    /// Threats
    Threat threats[MAX_THREATS_PER_FRAME];
    int cnt_threat[size_t(ThreatType::nThreatType)];
    int n_threats = 0;

    ThreatType GenThreatType();
    bool GenThreat(int i);
    int Gen_nThreats();
    void InitThreats();

    Timer timer;

    /// score
    Text show_score;
    int d_score = 0;

    /// menu
    Menu menu;
    Mix_Music *menu_sound = nullptr;
    OPTION ShowMenu();

    /// In game
    vector <OptionsPack> in_game_options_pack;
    OPTION PlayGame();
    void ResetGame();
    OPTION EndGame(); 

    /// Functions
    void InitOptions();
    void Init();
    void ShowScore();
    int ScrollMap();
    void GenObjects();
};

#endif // GAME_H

