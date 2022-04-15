#include "Platform.h"

Platform :: Platform()
{
    type = PlatformType::nPlatformType;
}

Platform :: ~Platform()
{

}

void Platform :: LoadPlatform(const PlatformType& _type, const string& MAP_NAME, SDL_Renderer*& renderer)
{
    if (type != _type)
    {
        type = _type;
        LoadImg(PLATFORM_FOLDER + MAP_NAME + PlatformText[uint16_t(type)] + ".png", renderer);
    }
}

void Platform :: Render(SDL_Renderer*& renderer)
{
    switch (type)
    {
        case PlatformType::NORMAL:
            ImgProcess::Render(renderer, nullptr);
            break;
    }
}