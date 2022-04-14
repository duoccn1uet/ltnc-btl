///#define PlatformDebug
#ifndef PlatformDebug

#include "Platform.h"

Platform :: Platform()
{
    number_of_platforms = 0;
    for(int i = 0; i < MAX_PLATFORM_PER_FRAME; ++i)
        d_platforms[i].has_item = false;
}

Platform :: ~Platform()
{
    delete[] d_platforms;
}

bool Platform :: CharacterStandOn(const SDL_Rect& d_rect)
{
    for(int i = 0; i < number_of_platforms; ++i)
        if (CheckCollision(d_platforms[i].rect, d_rect))/// && abs(d_rect.y - d_platforms[i].y) <= 7)
        {
            ///cout << -(d_rect.y - d_platforms[i].y) << endl;
            ///cout << d_rect.x << ' ' << d_rect.y << ' ' << d_platforms[i].x << ' ' << d_platforms[i].y << endl;
            return true;
        }
    return false;
}

void Platform :: Render(SDL_Renderer* renderer)
{
    for(int i = 0; i < number_of_platforms; ++i)
    {
        SDL_RenderCopy(renderer, d_object, nullptr, &d_platforms[i].rect);
        if (d_platforms[i].has_item)
            d_platforms[i].item.Render(renderer, nullptr);
    }
}

bool Platform :: GoodPlatform(int i)
{
    if (i == 0)
        return true;
    int dist = 1e9;
    bool res = true;
    for(int j = 0; j < i; ++j)
    {
        ///cout << d_platforms[j].x << ' ' << d_platforms[j].y << endl;
        if (CheckCollision(d_platforms[i].rect, d_platforms[j].rect))
            return false;
        mini(dist, SqrDist(d_platforms[i].rect, d_platforms[j].rect));
    }
    ///cout << dist << endl;
   /// cout << d_MIN_DIST << ' ' << dist << ' ' << d_MAX_DIST << ' ' << i << endl;
    res &= (d_MIN_DIST <= dist && dist <= d_MAX_DIST);
    return res;
}

void Platform :: InitPlatforms(SDL_Renderer* renderer, const string& path, const SDL_Rect& character)
{
    number_of_platforms = rand(MIN_PLATFORM_PER_FRAME, MAX_PLATFORM_PER_FRAME);
///    debug(number_of_platforms, 1);
    LoadImg(path.c_str(), renderer);
    d_platforms[0] = {character.x, character.y, d_rect.w, d_rect.h};

    for(int i = 1; i < number_of_platforms; ++i)
    {
        SDL_Rect& platform = d_platforms[i].rect;
        platform.w = d_rect.w;
        platform.h = d_rect.h;
        do
        {
            platform.x = rand(0,SCREEN_WIDTH-platform.w);
            platform.y = rand(0,SCREEN_HEIGHT-platform.h);
        }
        while (!GoodPlatform(i));
    }
}

void Platform :: GenItems(const string& MAP_NAME, SDL_Renderer*& renderer)
{
    int cnt = 0;
    for(int i = 0; i < number_of_platforms; ++i)
    {
        auto& pl = d_platforms[i];
        SDL_Rect& ir = pl.item.GetRect();
        SDL_Rect& pr = pl.rect;
        if (pl.has_item == false)
        {
            if (rand(0, number_of_platforms/MAX_ITEMS_PER_FRAME) == 0)
            {
                ++cnt;
                pl.has_item = true;
                int item_type = rand(0, static_cast <int> (ItemType::nItemType)-1);
                pl.item.SetItemType(static_cast <ItemType> (item_type));
                pl.item.LoadImg(ITEM_FOLDER + MAP_NAME + ItemText[item_type] + ".png", renderer);
                pl.item.SetRect(rand(pr.x, pr.x+pr.w-ir.w), pr.y-ir.h-5);
            }
        }
        else
        {
            ++cnt;
            pl.item.SetRect(pl.item.GetRect().x, pr.y-ir.h-5);
        }
        if (cnt == MAX_ITEMS_PER_FRAME)
            break;
    }
}

#else

#include "Platform.h"

Platform :: Platform()
{
    number_of_platforms = 0;
}

Platform :: ~Platform()
{
    delete[] d_platforms;
}

bool Platform :: CharacterStandOn(const SDL_Rect& d_rect)
{
    for(int i = 0; i < number_of_platforms; ++i)
        if (PlatformOverlap(d_platforms[i], d_rect))
        {
           /// cout << d_rect.x << ' ' << d_rect.y << ' ' << d_platforms[i].x << ' ' << d_platforms[i].y << endl;
            return true;
        }
    return false;
}

bool Platform :: PlatformOverlap(const SDL_Rect& a, const SDL_Rect& b)
{
    if (a.x > b.x + b.w || b.x > a.x + a.w)
        return false;
    if (a.y > b.y + b.h || b.y > a.y + a.h)
        return false;
    return true;
}

void Platform :: Render(SDL_Renderer* renderer)
{
    for(int i = 0; i < number_of_platforms; ++i)
        SDL_RenderCopy(renderer, d_object, nullptr, &d_platforms[i]);
}

void Platform :: InitPlatforms(SDL_Renderer* renderer, const string& path)
{
    number_of_platforms = rand(MIN_PLATFORM_PER_FRAME, MAX_PLATFORM_PER_FRAME);
    ///cout << number_of_platforms << endl;
    LoadImg(path.c_str(), renderer);
    for(int i = 0; i < number_of_platforms; ++i)
    {
        SDL_Rect& platform = d_platforms[i];
        platform.w = d_rect.w;
        platform.h = d_rect.h;
        bool ok;
        do
        {
            platform.x = rand(0,SCREEN_WIDTH-platform.w);
            platform.y = rand(0,SCREEN_HEIGHT-platform.h);
            ok = true;
            for(int j = 0; j < i; ++j)
                if (PlatformOverlap(platform, d_platforms[j]))
                {
                    ok = false;
                    break;
                }
        }
        while (!ok);
    }
}

#endif // PlatformDebug
