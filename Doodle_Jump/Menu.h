#ifndef MENU_H
#define MENU_H

#include "CommonFunc.h"
#include "ImgProcess.h"
#include "Text.h"
#include "Option.h"

enum class MenuOption : short
{
    PLAY, HELP, EXIT, nMenuOption
};

enum class HelpOption: short
{
    HOME, nHelpOption, QUIT
};

enum class CurrentOption: short
{
    MENU, HELP
};

/// Menu
const string MenuOptionText[] = {"PLAY", "HELP", "EXIT"};
const int MenuOptionX[] = {230, 230, 239};
const int MenuOptionY[] = {255, 341, 427};

/// Help
const string HelpImg[] = {"home"};
const int HelpOptionX[] = {10};
const int HelpOptionY[] = {10};

class Menu : public ImgProcess
{
public:

    Menu();
    ~Menu();

    MenuOption HandleMenuEvent(SDL_Renderer*& renderer);
    MenuOption ShowMenu(SDL_Renderer* renderer, const string& font_path, const string& menu_path);
    void SetMenuOption(SDL_Renderer* renderer, const int& x, const int& y, const int& i, const string& content, const string& path, const int& font_size);
    void OptionOn(SDL_Renderer* renderer, const CurrentOption& o, const int& i, string MAP_NAME = "");
    void OptionOff(SDL_Renderer* renderer, const CurrentOption& o, const int& i, string MAP_NAME = "");
    bool PointToOption(const int& x_mouse, const int& y_mouse, auto& option);
    HelpOption Help(const string& MAP_NAME, SDL_Renderer*& renderer);

private:

    ImgProcess d_help;
    Option d_help_option[uint16_t(HelpOption::nHelpOption)];
    ///OptionStatus d_help_option_status[uint16_t(HelpOption::nHelpOption)];
    Text d_menu_option[uint32_t(MenuOption::nMenuOption)];
    OptionStatus d_menu_option_status[uint32_t(MenuOption::nMenuOption)];
};

#endif // MENU_H
