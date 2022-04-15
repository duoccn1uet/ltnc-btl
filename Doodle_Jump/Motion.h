#ifndef MOTION_H
#define MOTION_H

#include "CommonFunc.h"

namespace Motion
{
    void JumpUp(int& y, const float& v0, const int& t);
    void Cross(int& x, const float& v0, const float& alpha, const int& t);
    ///void JumpCross(int& x, const int& t)
};

using namespace Motion;

#endif /// MOTION_H