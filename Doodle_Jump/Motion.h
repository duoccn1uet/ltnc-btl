#ifndef MOTION_H
#define MOTION_H

#include "CommonFunc.h"

namespace Motion
{
    template <class T> void JumpUp(T& y, const float& v0, const int& t, const float& g)
    {
        /// y(t) = v0sina*t - 0.5gt^2
        T deltaY = v0 - g*t + 0.5*g;
        y -= deltaY;
        ///cout << "up\n" << ' ' << deltaY << endl;
    }

    template <class T> void Cross(T& x, const float& v0, const float& alpha, const int& t, const float& g)
    {
        /// vx = v0 * cosa
        /// vy = v0*sina - gt;
        /// x = v0*cosa*t
        float vx = (v0-g*t) / tan(alpha);
        T deltaX = vx + 0.5*(abs(alpha) > pi/2? -push_force : push_force);
        x += deltaX;
    }
    ///void JumpCross(int& x, const int& t)
};

using namespace Motion;

#endif /// MOTION_H