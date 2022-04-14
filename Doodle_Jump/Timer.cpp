#include "Timer.h"

Timer :: Timer()
{
    d_start_tick = 0;
}

Timer :: ~Timer()
{

}

void Timer :: Start()
{
    d_start_tick = SDL_GetTicks();
}

int Timer :: GetTicks()
{
    return SDL_GetTicks() - d_start_tick;
}
