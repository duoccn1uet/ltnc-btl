#include "Motion.h"

void Motion :: JumpUp(int& y, const float& v0, const int& t)
{
    /// y(t) = v0sina*t - 0.5gt^2
    int deltaY = v0 - g*t + 0.5*g;
    y -= deltaY;
    ///cout << "up\n" << ' ' << deltaY << endl;
}

void Motion :: Cross(int& x, const float& v0, const float& alpha, const int& t)
{
    /// vx = v0 * cosa
    /// vy = v0*sina - gt;
    /// x = v0*cosa*t
    float vx = (v0-g*t) / tan(alpha);
    int deltaX = vx + 0.5*(abs(alpha) > pi/2? -push_force : push_force);
    x += deltaX;
}
