#ifndef OPTIONS_PACK_H
#define OPTIONS_PACK_H

#include "CommonFunc.h"
#include "Text.h"
#include "Option.h"

extern vector <Option> options;

const int Distance_between_two_options = 30;
const int Distance_between_header_and_options = 20;

class OptionsPack
{
public:

    Text header_name;
    ImgProcess background;

    OptionsPack();
    ~OptionsPack();

    void AlignOptionsRect();
    void AlignBackgroundRect();
    void SetRect(const int& x, const int& y);
    void AddOption(const OPTION& option);
    Option* GetRefOption(const OPTION& option);
    void Render();

private:

    vector <OPTION> options_pack;
};

#endif /// OPTIONS_PACK_H;