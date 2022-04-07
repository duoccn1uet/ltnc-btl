#ifndef TIMER_H
#define TIMER_H

#include "CommonFunc.h"

class Timer
{
public:

    Timer();
    ~Timer();

    void Start();
    int GetTicks();

private:

    int d_start_tick;

};
#endif // TIMER_H
