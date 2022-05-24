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
        res = GetChosenOption(HelpOptions, SDL_PollEvent(&event));
        SDL_RenderPresent(renderer);
    } while (res == OPTION::NO_OPTION);
    return res;
}

OPTION Menu :: ShowHighScores()
{
    if (high_scores_img.Initialized() == false)
        high_scores_img.LoadImg(MENU_FOLDER + "high_scores.png");
    high_scores_img.Render();

    options[etoi(OPTION::HIGH_SCORES)].SetStatus(OptionStatus::OFF);
    
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
    high_scores_file.close();

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
        res = GetChosenOption(HighScoresOptions, SDL_PollEvent(&event) != 0);
        SDL_RenderPresent(renderer);
    } while (res == OPTION::NO_OPTION);
    return res;
}


OPTION Menu :: ShowSettings()
{
    if (settings_initialized == false)
    {
        options_pack.resize(OptionsPackText.size());
        for(int i = 0; i < options_pack.size(); ++i)
        {
            options_pack[i].SetRect(OptionsPackX[i], OptionsPackY[i]);
            options_pack[i].header_name.CreateText(OPTION_FONT, OPTION_FONT_SIZE, OptionsPackText[i], d_Text_Color::BLACK_TEXT);
            for(OPTION o : OptionsInOptionsPack[i])
                options_pack[i].AddOption(o);
        }
        auto g = options[etoi(OPTION::EASY_TEXT)].GetRect();
        options[etoi(OPTION::EASY_TEXT)].SetRect(g.x, g.y+9);
        settings_img.LoadImg(MENU_FOLDER + "settings.png");
        settings_initialized = true;
    }
    for(int i = 0; i < SettingsOptions.size(); ++i)
    {
        int id = etoi(SettingsOptions[i]);
        options[id].SetRect(SettingsOptionsX[i], SettingsOptionsY[i]);
        options[id].SetStatus(OptionStatus::OFF);
    }

    options[etoi(OPTION::SETTINGS)].SetStatus(OptionStatus::OFF);
        
    OPTION res;
    do
    {
        settings_img.Render();
        bool has_event = SDL_PollEvent(&event) != 0;
        res = GetChosenOption(SettingsOptions, has_event);
        if (res == OPTION::RESET_HIGH_SCORES)
        {
            ofstream high_scores_file(MENU_FOLDER + "high_scores.txt");
            high_scores_file << "";
            high_scores_file.close();
            high_scores.clear();
            ///SDL_Delay(1000);
            res = OPTION::HOME;
        }
        if (res == OPTION::NO_OPTION)
        {
            for(int i = 0; i < OptionsInOptionsPack.size(); ++i)
                {
                    res = GetChosenOption(OptionsInOptionsPack[i], has_event);
                    for(auto o : OptionsInOptionsPack[i])
                        options[etoi(o)].SetStatus(OptionStatus::OFF);
                    switch (res)
                    {
                        case OPTION::ON_TEXT:
                            SoundOn = true;
                            Mix_ResumeMusic();
                            break;
                        
                        case OPTION::OFF_TEXT:
                            SoundOn = false;
                            Mix_PauseMusic();
                            break;
                        
                        case OPTION::EASY_TEXT:
                        case OPTION::MEDIUM_TEXT:
                        case OPTION::HARD_TEXT:
                            int i = etoi(SettingsOptionsPack::HARDNESS);
                            for(int j = 0; j < OptionsInOptionsPack[i].size(); ++j)
                                if (OptionsInOptionsPack[i][j] == res)
                                    DIFFICULTY = HardnessValue[j];
                            break;
                    }
                }
            if (SoundOn) 
                options[etoi(OPTION::ON_TEXT)].SetStatus(OptionStatus::ON);
            if (SoundOn == false) 
                options[etoi(OPTION::OFF_TEXT)].SetStatus(OptionStatus::ON);

            for(int i = 0; i < OptionsInOptionsPack[etoi(SettingsOptionsPack::HARDNESS)].size(); ++i)
                if (DIFFICULTY == HardnessValue[i])
                    options[etoi(OptionsInOptionsPack[etoi(SettingsOptionsPack::HARDNESS)][i])].SetStatus(OptionStatus::ON);
            res = OPTION::NO_OPTION;
        }
        for(int i = 0; i < SettingsOptions.size(); ++i)
            options[etoi(SettingsOptions[i])].Render();
        for(int i = 0; i < options_pack.size(); ++i)
            options_pack[i].Render();
        SDL_RenderPresent(renderer);
    } while (res == OPTION::NO_OPTION);
    return res;
}

#endif /// MENU_DEBUG