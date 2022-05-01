#include "Menu.h"

#define MENU_DEBUG
#ifndef MENU_DEBUG

Menu :: Menu()
{

}

Menu :: ~Menu()
{

}

void Menu :: SetMenuOption(const int& x, const int& y, const int& i, const string& content, const string& path, const int& font_size)
{
    d_menu_option_status[i] = OptionStatus::ON;
    d_menu_option[i].SetContent(content);
    d_menu_option[i].SetColor(d_Text_Color::WHITE_TEXT);
    d_menu_option[i].SetFont(path, font_size);
    d_menu_option[i].SetRect(x, y);
    d_menu_option[i].CreateText();
    d_menu_option[i].RenderText();
}

void Menu :: OptionOn(const CurrentOption& o, const int& i, string MAP_NAME)
{
    if (o == CurrentOption::MENU)
    {
        if (d_menu_option_status[i] == OptionStatus::ON)
            return;
        d_menu_option_status[i] = OptionStatus::ON;
        d_menu_option[i].SetColor(d_Text_Color::RED_TEXT);
        d_menu_option[i].CreateText();
        d_menu_option[i].RenderText();
    } else
    if (o == CurrentOption::HELP)
    {
        if (d_help_option_status[i] == OptionStatus::ON)
            return;
        d_help_option_status[i] = OptionStatus::ON;
        d_help_option[i].LoadImg(ICON_FOLDER + HelpImg[i] + "_on.png");
        d_help_option[i].Render(nullptr);
    }
}

void Menu :: OptionOff(const CurrentOption& o, const int& i, string MAP_NAME)
{
    if (o == CurrentOption::MENU)
    {
        if (d_menu_option_status[i] == OptionStatus::OFF)
            return;
        d_menu_option_status[i] = OptionStatus::OFF;
        d_menu_option[i].SetColor(d_Text_Color::WHITE_TEXT);
        d_menu_option[i].CreateText();
        d_menu_option[i].RenderText();
    } else
    if (o == CurrentOption::HELP)
    {
        if (d_help_option_status[i] == OptionStatus::OFF)
            return;
        ///cout << "dfasd";
        d_help_option_status[i] = OptionStatus::OFF;
        d_help_option[i].LoadImg(ICON_FOLDER + HelpImg[i] + ".png");
        d_help_option[i].Render(nullptr);
    }
}

bool Menu :: PointToOption(const int& x_mouse, const int& y_mouse, auto& option)
{
    SDL_Rect rect = option.GetRect();
    return rect.x <= x_mouse && x_mouse <= rect.x + rect.w
        && rect.y <= y_mouse && y_mouse <= rect.y + rect.h;
}

HelpOption Menu :: Help()
{
    d_help.LoadImg(MENU_FOLDER + "help.png");
    d_help.Render(nullptr);
    for(int i = 0; i < uint16_t(HelpOption::nHelpOption); ++i)
    {
        d_help_option[i].LoadImg(ICON_FOLDER + HelpImg[i] + ".png");
        d_help_option[i].Render(nullptr);
        d_help_option_status[i] = OptionStatus::OFF;
    }
    SDL_Event event;
    while (true)
    {
        SDL_RenderPresent();
        if (SDL_PollEvent(&event) != 0)
        {
            switch(event.type)
            {
            case SDL_QUIT:
                return HelpOption::QUIT;
            case SDL_MOUSEMOTION:
                for(int i = 0; i < uint16_t(HelpOption::nHelpOption); ++i)
                    if (PointToOption(event.x, event.y, d_help_option[i]))
                        OptionOn(CurrentOption::HELP, i);
                    else
                        OptionOff(CurrentOption::HELP, i);
                break;
            case SDL_MOUSEBUTTONDOWN:
                for(int i = 0; i < uint16_t(HelpOption::nHelpOption); ++i)
                    if (PointToOption(event.x, event.y, d_help_option[i]))
                        return static_cast <HelpOption> (i);
                break;
            }
        }
        SDL_Delay(20);
    }
}

MenuOption Menu :: ShowMenu(const string& font_path, const string& menu_path)
{
    LoadImg(menu_path);
    Render(nullptr);
    for(int i = 0; i < short(MenuOption::nMenuOption); ++i)
        SetMenuOption(MenuOptionX[i], MenuOptionY[i], i, MenuOptionText[i], font_path, OPTION_FONT_SIZE);
    return HandleMenuEvent();
}

MenuOption Menu :: HandleMenuEvent()
{
    while (true)
    {
        SDL_RenderPresent();
        while (SDL_PollEvent(&event) != 0)
        {
            switch (event.type)
            {
            case SDL_QUIT:
                return MenuOption::EXIT;
            case SDL_MOUSEMOTION:
               /// int x_mouse = event.x;
                ///int y_mouse = event.y;
                ///cout << event.x << ' ' << event.y << endl;
                for(int i = 0; i < short(MenuOption::nMenuOption); ++i)
                    if (PointToOption(event.x, event.y, d_menu_option[i]))
                        OptionOn(CurrentOption::MENU, i);
                    else
                        OptionOff(CurrentOption::MENU, i);
                break;
            case SDL_MOUSEBUTTONDOWN:
                for(int i = 0; i < short(MenuOption::nMenuOption); ++i)
                    if (PointToOption(event.x, event.y, d_menu_option[i]))
                        return static_cast <MenuOption>(i);
                break;
            }
        }
        SDL_Delay(20);
    }
}

#else

Menu :: Menu()
{

}

Menu :: ~Menu()
{

}

void Menu :: SetMenuOption(const int& x, const int& y, const int& i, const string& content, const string& path, const int& font_size)
{
    d_menu_option_status[i] = OptionStatus::ON;
    d_menu_option[i].SetContent(content);
    d_menu_option[i].SetColor(d_Text_Color::WHITE_TEXT);
    d_menu_option[i].SetFont(path, font_size);
    d_menu_option[i].SetRect(x, y);
    d_menu_option[i].CreateText();
    d_menu_option[i].RenderText();
}

void Menu :: OptionOn(const CurrentOption& o, const int& i, string MAP_NAME)
{
    if (o == CurrentOption::MENU)
    {
        if (d_menu_option_status[i] == OptionStatus::ON)
            return;
        d_menu_option_status[i] = OptionStatus::ON;
        d_menu_option[i].SetColor(d_Text_Color::RED_TEXT);
        d_menu_option[i].CreateText();
        d_menu_option[i].RenderText();
    }
}

void Menu :: OptionOff(const CurrentOption& o, const int& i, string MAP_NAME)
{
    if (o == CurrentOption::MENU)
    {
        if (d_menu_option_status[i] == OptionStatus::OFF)
            return;
        d_menu_option_status[i] = OptionStatus::OFF;
        d_menu_option[i].SetColor(d_Text_Color::WHITE_TEXT);
        d_menu_option[i].CreateText();
        d_menu_option[i].RenderText();
    }
}

bool Menu :: PointToOption(const int& x_mouse, const int& y_mouse, auto& option)
{
    SDL_Rect rect = option.GetRect();
    return rect.x <= x_mouse && x_mouse <= rect.x + rect.w
        && rect.y <= y_mouse && y_mouse <= rect.y + rect.h;
}

HelpOption Menu :: Help()
{
    d_help.LoadImg(MENU_FOLDER + "help.png");
    d_help.Render(nullptr);
    for(int i = 0; i < uint16_t(HelpOption::nHelpOption); ++i)
    {
        d_help_option[i].CreateOption(ICON_FOLDER, HelpImg[i], HelpOptionX[i], HelpOptionY[i]);
        d_help_option[i].SetStatus(OptionStatus::OFF);
    }
    SDL_Event event;
    while (true)
    {
        SDL_RenderPresent(renderer);
        if (SDL_PollEvent(&event) != 0)
        {
            switch(event.type)
            {
            case SDL_QUIT:
                return HelpOption::QUIT;
            case SDL_MOUSEMOTION:
                for(int i = 0; i < uint16_t(HelpOption::nHelpOption); ++i)
                    if (PointToOption(event.motion.x, event.motion.y, d_help_option[i]))
                        d_help_option[i].SetStatus(OptionStatus::ON);
                    else
                        d_help_option[i].SetStatus(OptionStatus::OFF);
                break;
            case SDL_MOUSEBUTTONDOWN:
                for(int i = 0; i < uint16_t(HelpOption::nHelpOption); ++i)
                    if (PointToOption(event.motion.x, event.motion.y, d_help_option[i]))
                        return static_cast <HelpOption> (i);
                break;
            }
        }
        SDL_Delay(20);
    }
}

MenuOption Menu :: ShowMenu(const string& font_path, const string& menu_path)
{
    LoadImg(menu_path);
    Render(nullptr);
    for(int i = 0; i < short(MenuOption::nMenuOption); ++i)
        SetMenuOption(MenuOptionX[i], MenuOptionY[i], i, MenuOptionText[i], font_path, OPTION_FONT_SIZE);
    return HandleMenuEvent();
}

MenuOption Menu :: ShowMenu()
{
    Render(nullptr);
    for(int i = 0; i < short(MenuOption::nMenuOption); ++i)
        d_menu_option[i].RenderText();
    return HandleMenuEvent();
}


MenuOption Menu :: HandleMenuEvent()
{
    while (true)
    {
        SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&event) != 0)
        {
            switch (event.type)
            {
            case SDL_QUIT:
                return MenuOption::EXIT;
            case SDL_MOUSEMOTION:
               /// int x_mouse = event.x;
                ///int y_mouse = event.y;
                ///cout << event.x << ' ' << event.y << endl;
                for(int i = 0; i < short(MenuOption::nMenuOption); ++i)
                    if (PointToOption(event.motion.x, event.motion.y, d_menu_option[i]))
                        OptionOn(CurrentOption::MENU, i);
                    else
                        OptionOff(CurrentOption::MENU, i);
                break;
            case SDL_MOUSEBUTTONDOWN:
                for(int i = 0; i < short(MenuOption::nMenuOption); ++i)
                    if (PointToOption(event.motion.x, event.motion.y, d_menu_option[i]))
                        return static_cast <MenuOption>(i);
                break;
            }
        }
        SDL_Delay(20);
    }
}

#endif /// MENU_DEBUG