#include "Option.h"

extern vector <Option> options;

Option :: Option()
{
    
}

Option :: ~Option()
{
    /**if (option_img != nullptr)
    {
        delete[] option_img;
        option_img = nullptr;
    }
    if (option_text != nullptr)
    {
        delete[] option_text;
        option_text = nullptr;
    }*/
}

void Option :: SetRect(const int& x, const int& y)
{
    for(int i = 0; i < etoi(OptionStatus::nOptionStatus); ++i)
        option_img[i].SetRect(x, y);
}

void Option :: CreateOption(const OPTION& name, const int& x, const int& y)
{
    string s = OptionText[etoi(name)];
    for(int i = 0; i < uint16_t(OptionStatus::nOptionStatus); ++i)
    {
        option_img[i].LoadImg(OPTION_FOLDER + s + '_' + OptionStatusText[i] + ".png");
        option_img[i].SetRect(x, y);
    }
    SetStatus(OptionStatus::OFF);
}

void Option :: SetStatus(const OptionStatus& _status)
{
    status = _status;
}

bool Option :: PointedTo()
{
    if (event.type != SDL_MOUSEMOTION)
        return false;
    SDL_Rect rect = GetRect();
    int x = event.motion.x;
    int y = event.motion.y;
    return rect.x <= x && x <= rect.x + rect.w
        && rect.y <= y && y <= rect.y + rect.h;
}

bool Option :: IsChosen()
{
    if (event.type != SDL_MOUSEBUTTONDOWN)
        return false;
    SDL_Rect rect = GetRect();
    int x = event.motion.x;
    int y = event.motion.y;
    return rect.x <= x && x <= rect.x + rect.w
        && rect.y <= y && y <= rect.y + rect.h;
}

void Option :: Render()
{
    option_img[etoi(status)].Render();
}

OPTION OptionFunc :: GetChosenOption(const vector <OPTION>& option_pack, bool has_event)
{
    if (has_event)
    {
        if (event.type == SDL_QUIT)
            return OPTION::EXIT_GAME;
        for(auto option : option_pack)
        {
            int id = etoi(option);
            if (options[id].IsChosen())
                return option;
            if (options[id].PointedTo())
                options[id].SetStatus(OptionStatus::ON);
            else
                options[id].SetStatus(OptionStatus::OFF);
        }
    }
    for(auto option : option_pack)
        options[etoi(option)].Render();
    ///SDL_Delay(20);
    return OPTION::NO_OPTION;
}