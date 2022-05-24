#ifndef OPTION_H
#define OPTION_H

#include "CommonFunc.h"
#include "ImgProcess.h"
#include "Text.h"

enum class OptionStatus : short
{
    ON = 0, OFF = 1, nOptionStatus
};

const string OptionStatusText[] = {"on", "off"};

class Option
{
public:

    Option();
    ~Option();

    SDL_Rect GetRect() {return option_img[0].GetRect();}
    void SetRect(const int& x, const int& y);
    void CreateOption(const OPTION& name, const int& x = 0, const int& y = 0);

    void SetStatus(const OptionStatus& _status);
    bool PointedTo();
    bool IsChosen();
    void Render();

private:

    ImgProcess option_img[uint16_t(OptionStatus::nOptionStatus)];
    OptionStatus status;
};

namespace OptionFunc
{
    OPTION GetChosenOption(const vector <OPTION>& option_pack, bool has_event);
}

using namespace OptionFunc;

#endif // OPTION_H