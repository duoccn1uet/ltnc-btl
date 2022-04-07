#ifndef MOTION_H
#define MOTION_H

#include "CommonFunc.h"

class Motion
{
public:

    Motion();
    ~Motion();

    void JumpUp(int& x, int& y, const float& v0, const float& alpha, const int& t, bool cross);
    void FallDown(int& x, int& y, const float& alpha, const int& t, bool cross);
    ///void JumpCross(int& x, const int& t)

private:

};

#endif /// MOTION_H