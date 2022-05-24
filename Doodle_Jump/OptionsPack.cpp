#include "OptionsPack.h"

OptionsPack :: OptionsPack()
{
    
}

OptionsPack :: ~OptionsPack()
{

}

void OptionsPack :: AlignOptionsRect()
{
    auto h_rect = header_name.GetRect();
    int total_w_of_options = 0;
    int max_h = 0;
    for(OPTION o : options_pack)
    {
        int i = etoi(o);
        total_w_of_options += options[i].GetRect().w;
        maxi(max_h, options[i].GetRect().h);
    }
    int o_x = h_rect.x + h_rect.w/2 - (total_w_of_options + (options_pack.size()-1)*Distance_between_two_options)/2;
    for(OPTION o : options_pack)
    {
        int i = etoi(o);
        auto o_rect = options[i].GetRect();
        options[i].SetRect(o_x, h_rect.y + h_rect.h + Distance_between_header_and_options + max_h - o_rect.h);
        ///cout << options[i].GetRect().y << ' ';
        o_x += o_rect.w + Distance_between_two_options;
    }
}

void OptionsPack :: AlignBackgroundRect()
{
    if (background.Initialized())
    {
        auto h_rect = header_name.GetRect();
        auto b_rect = background.GetRect();
        int x = h_rect.x + h_rect.w/2 - b_rect.w/2;
        int y = h_rect.y + 
                (h_rect.h + 
                 Distance_between_header_and_options + 
                 (options_pack.empty() ? 0 : options[etoi(options_pack[0])].GetRect().h))/2
                - b_rect.h/2;
        /**debug((h_rect.y + h_rect.h + 
                 Distance_between_header_and_options + 
                 (options_pack.empty() ? 0 : options[etoi(options_pack[0])].GetRect().h))/2);*/
        background.SetRect(x, y);
    }

}

void OptionsPack :: SetRect(const int& x, const int& y)
{
    header_name.SetRect(x, y);
    AlignOptionsRect();
    AlignBackgroundRect();
}

void OptionsPack :: AddOption(const OPTION& option)
{
    options_pack.eb(option);
    AlignOptionsRect();
    if (options_pack.size() == 1)
        AlignBackgroundRect();
}

Option* OptionsPack :: GetRefOption(const OPTION& option)
{
    for(OPTION o : options_pack)
        if (o == option)
            return &options[etoi(o)];
    cout << "Options pack doesn't have this option\n";
}

void OptionsPack :: Render()
{
    background.Render();
    header_name.Render();
    for(OPTION o : options_pack)
        options[etoi(o)].Render();
}