#ifndef OPTION_H
#define OPTION_H

#include "CommonFunc.h"
#include "ImgProcess.h"

enum class OptionStatus : short
{
    ON = 0, OFF = 1, nOptionStatus
};

const string OptionText[] = {"on", "off"};

class Option
{
public:

    Option();
    ~Option();

    SDL_Rect GetRect() {return d_option_img[0].GetRect();}
    void CreateOption(const string& path, const string& name, const int& x, const int& y, SDL_Renderer*& renderer);
    void SetStatus(const OptionStatus& status, SDL_Renderer*& renderer);

private:

    bool d_status[uint16_t(OptionStatus::nOptionStatus)];
    string d_name;
    string d_path;
    ImgProcess d_option_img[uint16_t(OptionStatus::nOptionStatus)];
};

#endif // OPTION_H