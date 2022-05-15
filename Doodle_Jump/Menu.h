#ifndef MENU_H
#define MENU_H

#include "CommonFunc.h"
#include "ImgProcess.h"
#include "Text.h"
#include "Option.h"

/// Option

extern vector <Option> options;

/// Menu
const vector <OPTION> MenuOption = {OPTION::PLAY_TEXT, OPTION::HELP, OPTION::EXIT_TEXT};
const int MenuOptionX[] = {230, 230, 239};
const int MenuOptionY[] = {255, 341, 427};

/// Help
const vector <OPTION> HelpOptions = {OPTION::HOME, OPTION::PLAY_BUTTON};
const int HelpOptionsX[] = {10, SCREEN_WIDTH-50};
const int HelpOptionsY[] = {10, 10};

class Menu : public ImgProcess
{
public:

    Menu();
    ~Menu();

    OPTION ShowMenu();
    OPTION Help();

private:

    ImgProcess d_help;
};

#endif // MENU_H
