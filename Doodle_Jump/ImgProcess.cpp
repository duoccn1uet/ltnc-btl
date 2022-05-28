#include "ImgProcess.h"

///#define IMGPROCESS_DEBUG
#ifndef IMGPROCESS_DEBUG

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
    {
        ///SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface.format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        d_object = IMG_LoadTexture(renderer, path.c_str());
        if (d_object == nullptr)
            cout << "Unable to load image from " << path << " SDL Error: "
                 << SDL_GetError() << '\n';
        else
        {
            /**d_rect.w = load_surface->w;
            d_rect.h = load_surface->h;*/
            SDL_QueryTexture(d_object, nullptr, nullptr, &d_rect.w, &d_rect.h);
        }
    }

    return d_object != nullptr;
}

void ImgProcess :: Render(const SDL_Rect* clip)
{
    SDL_RenderCopy(renderer, d_object, clip, &d_rect);
}

void ImgProcess :: Render()
{
    is_rendering = true;
    SDL_Rect clip;
    clip.w = d_rect.w / clip_frame;
    clip.h = d_rect.h;
    clip.x = clip.w * frame_ptr;
    clip.y = 0;
    SDL_Rect temp_rect = d_rect;
    temp_rect.w = d_rect.w / clip_frame;
    temp_rect.h = d_rect.h / clip_frame;
    SDL_RenderCopy(renderer, d_object, &clip, &temp_rect);
    if (++frame_ptr == clip_frame)
        frame_ptr = 0, is_rendering = false;
    if (clip_frame > 1)
    {
        ++loop;
        if (loop < 4)
        {
            --frame_ptr;
            if (frame_ptr == -1)
                frame_ptr += clip_frame;
            is_rendering = true;
        }
        else
            loop = 0;
    }
}

void ImgProcess :: Free()
{
    clip_frame = 1;
    frame_ptr = 0;
    loop = 0;
    is_rendering = false;
    if (d_object != nullptr)
    {
        SDL_DestroyTexture(d_object);
        d_object = nullptr;
        d_rect.w = 0;
        d_rect.h = 0;
    }
}

#else

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
    {
        ///SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface.format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        d_object = IMG_LoadTexture(renderer, path.c_str());
        if (d_object == nullptr)
            cout << "Unable to load texture from " << path << " SDL Error: "
                 << SDL_GetError() << '\n';
        else
        {
            /**d_rect.w = load_surface->w;
            d_rect.h = load_surface->h;*/
            SDL_QueryTexture(d_object, nullptr, nullptr, &d_rect.w, &d_rect.h);
        }
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

#endif