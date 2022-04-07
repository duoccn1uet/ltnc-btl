#include "Option.h"

Option :: Option()
{

}

Option :: ~Option()
{

}

void Option :: CreateOption(const string& path, const string& name, const int& x, const int& y, SDL_Renderer*& renderer)
{
    d_path = path;
    d_name = name;
    for(int i = 0; i < uint16_t(OptionStatus::nOptionStatus); ++i)
    {
        d_option_img[i].LoadImg(path + name + '_' + OptionText[i] + ".png", renderer);
        d_option_img[i].SetRect(x, y);
    }
    SetStatus(OptionStatus::OFF, renderer);
}

void Option :: SetStatus(const OptionStatus& status, SDL_Renderer*& renderer)
{
    if (d_status[uint16_t(status)] == true)
        return;
    for(int i = 0; i < uint16_t(OptionStatus::nOptionStatus); ++i)
        d_status[i] = false;
    d_status[uint16_t(status)] = true;
    d_option_img[uint16_t(status)].Render(renderer, nullptr);
}
