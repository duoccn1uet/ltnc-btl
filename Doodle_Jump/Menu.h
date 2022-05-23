#ifndef MENU_H
#define MENU_H

#include "CommonFunc.h"
#include "ImgProcess.h"
#include "Text.h"
#include "Option.h"

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


class Menu : public ImgProcess
{
public:

    Menu();
    ~Menu();

    void Init();
    OPTION Help();
    OPTION ShowHighScores();

private:

    ImgProcess help_background;

    /// High scores
    ImgProcess high_scores_img;
    Text score;
};

#endif // MENU_H
