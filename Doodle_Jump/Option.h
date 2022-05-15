#ifndef OPTION_H
#define OPTION_H

#include "CommonFunc.h"
#include "ImgProcess.h"
#include "Text.h"

enum class OptionStatus : short
{
    ON = 0, OFF = 1, nOptionStatus
};

enum class RenderOptionType: short
{
    TEXT, IMAGE, nRenderOptionType
};

const string OptionStatusText[] = {"on", "off"};

class Option
{
public:

    Option();
    ~Option();

    SDL_Rect GetRect() {return option_img[0].GetRect();}
    ///void SetRenderType(RenderOptionType _type) {type = _type;}
    void SetRect(const int& x, const int& y);
    void CreateOption(const OPTION& name, const int& x = 0, const int& y = 0);
    void SetStatus(const OptionStatus& _status);
    bool PointedTo(const SDL_Event& event);
    bool IsChosen(const SDL_Event& event);
    void Render();

private:

    ImgProcess option_img[uint16_t(OptionStatus::nOptionStatus)];
    ///Text* option_text;
    OptionStatus status;
    ///RenderOptionType type;
};

namespace OptionFunc
{
    OPTION GetChosenOption(ImgProcess& background, const vector <OPTION>& option_pack);
}

using namespace OptionFunc;

#endif // OPTION_H