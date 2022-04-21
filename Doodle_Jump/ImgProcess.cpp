#include "ImgProcess.h"


/**void show() {}
template <typename T, typename... V> void show(T t, V... v)
{cerr << t; if (sizeof...(v)) cerr << ", "; show(v...);}*/

ImgProcess::ImgProcess()
{
    d_object = nullptr;
    d_rect.x = d_rect.y = d_rect.w = d_rect.h = 0;
}

ImgProcess::~ImgProcess()
{
    Free();
}

bool ImgProcess::LoadImg(const std::string& path)
{
    Free();
    SDL_Surface* load_surface = IMG_Load(path.c_str());

    if (load_surface == nullptr)
        cout << "Unable to load image " << path << " SDL_image Error: "
                 << IMG_GetError() << '\n';
    else
    {
        ///SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface.format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        d_object = SDL_CreateTextureFromSurface(renderer, load_surface);
        if (d_object == nullptr)
            cout << "Unable to load texture from " << path << " SDL Error: "
                 << SDL_GetError() << '\n';
        else
        {
            d_rect.w = load_surface->w;
            d_rect.h = load_surface->h;
        }
        SDL_FreeSurface(load_surface);
    }

    return d_object != nullptr;
}

void ImgProcess :: Render(const SDL_Rect* clip)
{
    SDL_RenderCopy(renderer, d_object, clip, &d_rect);
}

void ImgProcess :: Free()
{
    if (d_object != nullptr)
    {
        SDL_DestroyTexture(d_object);
        d_object = nullptr;
        d_rect.w = 0;
        d_rect.h = 0;
    }
}

