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

void Menu :: OptionOn(const CurrentOption& o, const int& i)
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
        d_help_option[i].LoadImg(OPTION_FOLDER + HelpImg[i] + "_on.png");
        d_help_option[i].Render(nullptr);
    }
}

void Menu :: OptionOff(const CurrentOption& o, const int& i)
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
        d_help_option[i].LoadImg(OPTION_FOLDER + HelpImg[i] + ".png");
        d_help_option[i].Render(nullptr);
    }
}

bool Menu :: PointToOption(const int& x_mouse, const int& y_mouse, auto& option)
{
    SDL_Rect rect = option.GetRect();
    return rect.x <= x_mouse && x_mouse <= rect.x + rect.w
        && rect.y <= y_mouse && y_mouse <= rect.y + rect.h;
}

HelpOptions Menu :: Help()
{
    help_background.LoadImg(MENU_FOLDER + "help.png");
    help_background.Render(nullptr);
    for(int i = 0; i < uint16_t(HelpOptions::nHelpOptions); ++i)
    {
        d_help_option[i].LoadImg(OPTION_FOLDER + HelpImg[i] + ".png");
        d_help_option[i].Render(nullptr);
        d_help_option_status[i] = OptionStatus::OFF;
    }
    ;
    while (true)
    {
        SDL_RenderPresent();
        if (SDL_PollEvent(&event) != 0)
        {
            switch(event.type)
            {
            case SDL_QUIT:
                return HelpOptions::QUIT;
            case SDL_MOUSEMOTION:
                for(int i = 0; i < uint16_t(HelpOptions::nHelpOptions); ++i)
                    if (PointToOption(event.x, event.y, d_help_option[i]))
                        OptionOn(CurrentOption::HELP, i);
                    else
                        OptionOff(CurrentOption::HELP, i);
                break;
            case SDL_MOUSEBUTTONDOWN:
                for(int i = 0; i < uint16_t(HelpOptions::nHelpOptions); ++i)
                    if (PointToOption(event.x, event.y, d_help_option[i]))
                        return static_cast <HelpOptions> (i);
                break;
            }
        }
        SDL_Delay(20);
    }
}

OPTION Menu :: ShowMenu(const string& font_path, const string& menu_path)
{
    LoadImg(menu_path);
    Render(nullptr);
    for(int i = 0; i < short(OPTION::nMenuOption); ++i)
        SetMenuOption(MenuOptionX[i], MenuOptionY[i], i, MenuOptionText[i], font_path, OPTION_FONT_SIZE);
    return HandleMenuEvent();
}

OPTION Menu :: HandleMenuEvent()
{
    while (true)
    {
        SDL_RenderPresent();
        while (SDL_PollEvent(&event) != 0)
        {
            switch (event.type)
            {
            case SDL_QUIT:
                return OPTION::EXIT;
            case SDL_MOUSEMOTION:
               /// int x_mouse = event.x;
                ///int y_mouse = event.y;
                ///cout << event.x << ' ' << event.y << endl;
                for(int i = 0; i < short(OPTION::nMenuOption); ++i)
                    if (PointToOption(event.x, event.y, d_menu_option[i]))
                        OptionOn(CurrentOption::MENU, i);
                    else
                        OptionOff(CurrentOption::MENU, i);
                break;
            case SDL_MOUSEBUTTONDOWN:
                for(int i = 0; i < short(OPTION::nMenuOption); ++i)
                    if (PointToOption(event.x, event.y, d_menu_option[i]))
                        return static_cast <OPTION>(i);
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

void Menu :: Init()
{
    LoadImg(MENU_FOLDER + "menu.png");
    for(int i = 0; i < MenuOption.size(); ++i)
    {
        int id = etoi(MenuOption[i]);
        options[id].SetRect(MenuOptionX[i], MenuOptionY[i]);
        ///options[id].SetStatus(OptionStatus::OFF);
        ///options[id].Render();
    }
}

OPTION Menu :: Help()
{
    if (help_background.Initialized() == false)
        help_background.LoadImg(MENU_FOLDER + "help.png");
    help_background.Render();
    for(int i = 0; i < HelpOptions.size(); ++i)
    {
        int id = etoi(HelpOptions[i]);
        options[id].SetRect(HelpOptionsX[i], HelpOptionsY[i]);
        options[id].SetStatus(OptionStatus::OFF);
        options[id].Render();
    }
    OPTION res;
    do
    {
        help_background.Render();
        res = GetChosenOption(HelpOptions);
        SDL_RenderPresent(renderer);
    } while (res == OPTION::NO_OPTION);
    return res;
}

OPTION Menu :: ShowHighScores()
{
    if (high_scores_img.Initialized() == false)
        high_scores_img.LoadImg(MENU_FOLDER + "high_scores.png");
    high_scores_img.Render();
    
    /// Show Options
    for(int i = 0; i < HighScoresOptions.size(); ++i)
    {
        int id = etoi(HighScoresOptions[i]);
        options[id].SetRect(HighScoresOptionsX[i], HighScoresOptionsY[i]);
        options[id].SetStatus(OptionStatus::OFF);
    }

    /// Show high scores
    ifstream high_scores_file(MENU_FOLDER + "high_scores.txt");
    for(int x; high_scores_file >> x; high_scores.insert(x));

    score.CreateText(SCORE_FONT, SCORE_FONT_SIZE, "dump_value", d_Text_Color::BLACK_TEXT);

    OPTION res;
    do
    {
        high_scores_img.Render();
        int y = HighScoreY;
        for(int s : high_scores)
        {
            score.SetContent(to_string(s));
            score.CreateText();
            score.SetRect(SCREEN_WIDTH-score.GetRect().w-20, y);
            y += 60;
            score.Render();
        }
        res = GetChosenOption(HighScoresOptions);
        SDL_RenderPresent(renderer);
    } while (res == OPTION::NO_OPTION);
    return res;
}

#endif /// MENU_DEBUG