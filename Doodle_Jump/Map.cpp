///#define MAP_DEBUG
#ifndef MAP_DEBUG
#include "Map.h"

Map :: Map()
{
    d_platforms = nullptr;
    d_character = nullptr;
}

Map :: ~Map()
{

}

Map :: Map(Platform* _platform, Character* _character)
{
    LoadPlatform(_platform);
    LoadCharacter(_character);
}

int Map :: SrcollMap(const string& MAP_NAME)
{
    SDL_Rect d_char_rect = d_character->GetRect();
    ///cout << d_char_rect.y << endl;
    if (d_char_rect.y < d_scroll_boundline)
    {
        int diff = d_scroll_boundline - d_char_rect.y;
        d_character->SetRect(d_char_rect.x, d_scroll_boundline);
        int cnt = 0;
        int number_of_platforms = d_platforms->GetNumberOfPlatforms();
        int lowest_y = SCREEN_HEIGHT;
        for(int i = 0; i < number_of_platforms; ++i)
        {
            if (d_platforms->d_platforms[i].rect.y+diff < SCREEN_HEIGHT)
            {
                auto& pl = d_platforms->d_platforms[cnt];
                pl = d_platforms->d_platforms[i];
                pl.rect.y += diff;
                ++cnt;
                mini(lowest_y, pl.rect.y);
            }
        }
        int new_nop = rand(cnt, rand(0,7) == 0 ? MAX_PLATFORM_PER_FRAME : number_of_platforms);
        ///cout << number_of_platforms << ' ' << new_nop << '\n';
       /// cout << new_nop << '\n';
        int platform_w = d_platforms->GetRect().w;
        int platform_h = d_platforms->GetRect().h;
        if (lowest_y <= platform_h + d_min_dist*4/3) /// avoid not being able to random platforms
            new_nop = cnt;
        int y_bound = min(lowest_y - platform_h - 1, d_scroll_boundline - platform_h - 1);
        y_bound = y_bound * 1 / 2;
        ///cout << new_nop << endl;
        ///cout << float(y_bound) / SCREEN_HEIGHT << endl;
        for(int i = cnt; i < new_nop; ++i)
        {
            int rand_times = 0;
            do
            {
                SDL_Rect& rect = d_platforms->d_platforms[i].rect;
                rect.x = rand(0, SCREEN_WIDTH - platform_w);
                rect.y = rand(0, y_bound);
                rect.w = platform_w;
                rect.h = platform_h;
                if (++rand_times > MAX_RANDOM_TIMES)
                {
                    --new_nop;
                    --i;
                    break;
                }
            } while (!d_platforms->GoodPlatform(i));
        }
        d_platforms->SetNumberOfPlatforms(new_nop);
        return diff;
    }
    return 0;
}

#else
#include "Map.h"

Map :: Map()
{
    d_platforms = nullptr;
    d_character = nullptr;
}

Map :: ~Map()
{

}

Map :: Map(Platform* _platform, Character* _character)
{
    LoadPlatform(_platform);
    LoadCharacter(_character);
}

bool Map :: SrcollMap()
{
    SDL_Rect d_char_rect = d_character->GetRect();
    ///cout << d_char_rect.y << endl;
    if (d_char_rect.y < d_scroll_boundline)
    {
        int diff = d_scroll_boundline - d_char_rect.y;
        d_character->SetRect(d_char_rect.x, d_scroll_boundline);
        int cnt = 0;
        int number_of_platforms = d_platforms->GetNumberOfPlatforms();
        int lowest_y = SCREEN_HEIGHT;
        for(int i = 0; i < number_of_platforms; ++i)
        {
            SDL_Rect& rect = d_platforms->d_platforms[i];
            if (rect.y+diff < SCREEN_HEIGHT)
            {
                rect.y += diff;
                d_platforms->d_platforms[cnt++] = rect;
                mini(lowest_y, rect.y);
            }
        }
        int new_nop = rand(cnt, rand(0,7) == 0 ? MAX_PLATFORM_PER_FRAME : number_of_platforms);
        ///cout << number_of_platforms << ' ' << new_nop << '\n';
       /// cout << new_nop << '\n';
        int platform_w = d_platforms->GetRect().w;
        int platform_h = d_platforms->GetRect().h;
        if (lowest_y <= platform_h + 5) /// avoid not being able to random platforms
            new_nop = cnt;
        for(int i = cnt; i < new_nop; ++i)
        {
            int g = 0;
            do
            {
                SDL_Rect& rect = d_platforms->d_platforms[i];
                rect.x = rand(0, SCREEN_WIDTH - platform_w);
                rect.y = rand(0, lowest_y - platform_h - 1);
                rect.w = platform_w;
                rect.h = platform_h;
                ++g;
                ///cout << rect.x << ' ' << rect.y << endl;
            } while (!d_platforms->GoodPlatform(i, max(0,cnt-1)));
            cout << g << endl;
        }
        d_platforms->SetNumberOfPlatforms(new_nop);
        return true;
    }
    return false;
}

#endif
