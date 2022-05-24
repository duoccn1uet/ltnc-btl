#include "CommonFunc.h"

long long CommonFunc :: rand(long long Left, long long Right)
{
    return Left + rd() % (Right - Left + 1);
}

bool SoundOn = true;

void CommonFunc :: show() {}

void CommonFunc :: SetMapName(const string& _MAP_NAME)
{
    MAP_NAME = _MAP_NAME;
}

bool CommonFunc :: CheckCollision(const SDL_Rect& a, const SDL_Rect& b)
{
    if (a.x > b.x + b.w || b.x > a.x + a.w)
        return false;
    if (a.y > b.y + b.h || b.y > a.y + a.h)
        return false;
    return true;
}

int CommonFunc :: SqrDist(const SDL_Rect& a, const SDL_Rect& b)
{
    return (b.y-a.y)*(b.y-a.y) + (b.x-a.x)*(b.x-a.x);
}

bool CommonFunc :: LoadSound(Mix_Music*& sound, const string& path)
{
    if (sound != nullptr)
        Mix_FreeMusic(sound);
    sound = Mix_LoadMUS(path.c_str());
    if (sound == nullptr)
    {
        cout << "Failed to load beat music from " << path << " ! SDL_mixer Error: " << Mix_GetError() << '\n';
        return false;
    }
    return true;
}

bool CommonFunc :: LoadSound(Mix_Chunk*& sound, const string& path)
{
    if (sound != nullptr)
    {
        Mix_FreeChunk(sound);
        sound = nullptr;
    }
    sound = Mix_LoadWAV(path.c_str());
    if (sound == nullptr)
    {
        cout << "Failed to load beat music " << path << " ! SDL_mixer Error: " << Mix_GetError() << '\n';
        return false;
    }
    return true;
}

void CommonFunc :: PlaySound(Mix_Music*& sound, int loop)
{
    if (SoundOn)
        Mix_PlayMusic(sound, loop);
}

void CommonFunc :: PlaySound(Mix_Chunk*& sound, int loop)
{
    if (SoundOn)
        Mix_PlayChannel(-1, sound, loop-1);
}