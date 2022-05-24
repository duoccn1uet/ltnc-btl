#ifndef MENU_H
#define MENU_H

#include "CommonFunc.h"
#include "ImgProcess.h"
#include "Text.h"
#include "Option.h"
#include "OptionsPack.h"

/// Option

extern vector <Option> options;

/// Menu
const vector <OPTION> MenuOption = {OPTION::PLAY_TEXT, OPTION::HELP, OPTION::EXIT_TEXT, 
                                    OPTION::HIGH_SCORES, OPTION::SETTINGS};
const int MenuOptionX[] = {230, 230, 239, 340, 430};
const int MenuOptionY[] = {255, 341, 427, 640, 645};

/// Help
const vector <OPTION> HelpOptions = {OPTION::HOME, OPTION::PLAY_BUTTON};
const int HelpOptionsX[] = {10, SCREEN_WIDTH-50};
const int HelpOptionsY[] = {10, 10};

/// High scores
extern set <int, greater <int>> high_scores;
const vector <OPTION> HighScoresOptions = {OPTION::HOME, OPTION::PLAY_BUTTON, OPTION::SETTINGS};
const int HighScoresOptionsX[] = {10, SCREEN_WIDTH-50, 430};
const int HighScoresOptionsY[] = {10, 10, 645};
const int HighScoreY = 230;

/// Settings
extern bool SoundOn;
extern int DIFFICULTY;
extern const int HardnessValue[];
extern set <int, greater <int>> high_scores;
const vector <OPTION> SettingsOptions = {OPTION::HOME, OPTION::PLAY_BUTTON, OPTION::RESET_HIGH_SCORES};
const int SettingsOptionsX[] = {10, SCREEN_WIDTH-50, 300};
const int SettingsOptionsY[] = {10, 10, SCREEN_HEIGHT-150};
enum class SettingsOptionsPack: short
{
    SOUND, HARDNESS, nSettingsOptionsPack
};
const vector <string> OptionsPackText = {"sound", "hardness"};
const int OptionsPackX[] = {143, 300};
const int OptionsPackY[] = {164, 323};
const vector <vector<OPTION>> OptionsInOptionsPack = {{OPTION::ON_TEXT, OPTION::OFF_TEXT}, 
                                                       {OPTION::EASY_TEXT, OPTION::MEDIUM_TEXT, OPTION::HARD_TEXT}};

class Menu : public ImgProcess
{
public:

    Menu();
    ~Menu();

    void Init();
    OPTION Help();
    OPTION ShowHighScores();
    OPTION ShowSettings();

private:

    ImgProcess help_background;

    /// High scores
    ImgProcess high_scores_img;
    Text score;

    /// Settings
    ImgProcess settings_img;
    bool settings_initialized = false;
    vector <OptionsPack> options_pack;
};

#endif // MENU_H
