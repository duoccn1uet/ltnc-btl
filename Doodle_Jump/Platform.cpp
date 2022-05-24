#include "Platform.h"

Platform :: Platform()
{
    type = PlatformType::nPlatformType;
}

Platform :: ~Platform()
{
    FreePlatform();
}

void Platform :: LoadPlatform(const PlatformType& _type)
{
    if (type != _type)
    {
        type = _type;
        LoadImg(PLATFORM_FOLDER + PlatformText[uint16_t(type)] + ".png");
    }
}

void Platform :: Render()
{
    switch (type)
    {
        case PlatformType::NORMAL:
            ImgProcess::Render(nullptr);
            break;
    }
}

void Platform :: FreePlatform()
{
    Free();
    type = PlatformType::nPlatformType;
}