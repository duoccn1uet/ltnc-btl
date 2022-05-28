#ifndef IMGPROCESS_H_INCLUDED
#define IMGPROCESS_H_INCLUDED

#include "CommonFunc.h"

class ImgProcess
{
public:
    ImgProcess();
    ~ImgProcess();

    virtual void SetRect(const int& x, const int& y) {d_rect.x = x, d_rect.y = y;}
    void SetClipFrame(int cf) {clip_frame = cf;}
    int GetClipFrame() {return clip_frame;}
    int GetCurrentFrame() {return frame_ptr;}
    virtual SDL_Rect GetRect() const {return d_rect;}
    SDL_Texture* GetTexture() const {return d_object;}
    bool Initialized() {return d_object != nullptr;}

    virtual bool LoadImg(const std::string& path);
    virtual void Render(const SDL_Rect* clip);
    virtual void Render();
    bool IsRendering() {return is_rendering;}
    void Free();

protected:

    SDL_Texture* d_object;
    SDL_Rect d_rect;
    int clip_frame = 1;
    int frame_ptr = 0;
    int loop = 0;
    bool is_rendering = false;
};

#endif // IMGPROCESS_H_INCLUDED
