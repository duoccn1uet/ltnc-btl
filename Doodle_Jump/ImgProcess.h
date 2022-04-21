#ifndef IMGPROCESS_H_INCLUDED
#define IMGPROCESS_H_INCLUDED

#include "CommonFunc.h"
#include "CreateWindow.h"

class ImgProcess
{
public:
    ImgProcess();
    ~ImgProcess();

    void SetRect(const int& x, const int& y) {d_rect.x = x, d_rect.y = y;}
    SDL_Rect GetRect() const {return d_rect;}
    SDL_Texture* GetTexture() const {return d_object;}

    bool LoadImg(const std::string& path);
    void Render(const SDL_Rect* clip = nullptr);
    void Free();

protected:

    SDL_Texture* d_object;
    SDL_Rect d_rect;
};

#endif // IMGPROCESS_H_INCLUDED
