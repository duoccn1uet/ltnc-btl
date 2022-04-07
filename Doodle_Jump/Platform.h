#ifndef PLATFORM_H
#define PLATFORM_H

///#define PLATFORM_H_DEBUG
#ifndef PLATFORM_H_DEBUG

#include "CommonFunc.h"
#include "ImgProcess.h"

/// number of platforms
const int MAX_PLATFORM_PER_FRAME = 17;
const int MIN_PLATFORM_PER_FRAME = 10;

/// Distance between two platforms
const int d_MIN_DIST = d_min_dist*d_min_dist;
const int d_MAX_DIST = d_JumpHeight*d_JumpHeight;

typedef SDL_Rect t_platform;

class Platform: public ImgProcess
{
public:

    Platform();
    ~Platform();

    int GetNumberOfPlatforms() const {return number_of_platforms;}
    void SetNumberOfPlatforms(int x) {number_of_platforms = x;}
    void InitPlatforms(SDL_Renderer* renderer, const string& path, const SDL_Rect& rect);
    void Render(SDL_Renderer* renderer);
    bool CharacterStandOn(const SDL_Rect& d_rect);
    bool GoodPlatform(int i);

    friend class Map;
private:

    t_platform* d_platforms = new t_platform[MAX_PLATFORM_PER_FRAME];
    int number_of_platforms;
};

#else

#include "CommonFunc.h"
#include "ImgProcess.h"

/// number of platforms
const int MAX_PLATFORM_PER_FRAME = 17;
const int MIN_PLATFORM_PER_FRAME = 10;

/// Distance between two platforms
const int d_MIN_DIST = d_min_dist*d_min_dist;
const int d_MAX_DIST = d_JumpHeight*d_JumpHeight;

typedef SDL_Rect t_platform;

class Platform: public ImgProcess
{
public:

    Platform();
    ~Platform();

    int GetNumberOfPlatforms() const {return number_of_platforms;}
    void SetNumberOfPlatforms(int x) {number_of_platforms = x;}
    void InitPlatforms(SDL_Renderer* renderer, const string& path, const SDL_Rect& rect);
    void Render(SDL_Renderer* renderer);
    bool CharacterStandOn(const SDL_Rect& d_rect);
    bool GoodPlatform(int i);

    friend class Map;
private:

    t_platform* d_platforms = new t_platform[MAX_PLATFORM_PER_FRAME];
    int number_of_platforms;
};
#endif /// DEBUG

#endif // PLATFORM_H
