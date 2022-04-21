#ifndef PLATFORM_H
#define PLATFORM_H

#include "CommonFunc.h"
#include "ImgProcess.h"

enum class PlatformType
{
    NORMAL, CRACK, MOVING, nPlatformType
};

const string PlatformText[] = {"normal", "crack", "moving"};

class Platform: public ImgProcess
{
public:

    Platform();
    ~Platform();

    void LoadPlatform(const PlatformType& _type);
    void Render();

private:

    PlatformType type;

};

#endif /// PLATFORM_H