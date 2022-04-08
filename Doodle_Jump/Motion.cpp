#include "Motion.h"

Motion :: Motion()
{

}

Motion :: ~Motion()
{

}

void Motion :: JumpUp(int& x, int& y, const float& v0, const float& alpha, const int& t, bool cross)
{
    /// y(t) = v0sina*t - 0.5gt^2
    /// vx = v0 * cosa
    /// vy = v0*sina - gt;
    /// x = v0*cosa*t
    int deltaY = v0 - g*t + 0.5*g;
    y -= deltaY;
    if (cross)
    {
        float vx = (v0-g*t) / tan(alpha);
        int deltaX = vx + 0.5*(alpha > pi/2? -push_force : push_force);
        x += deltaX;
        if (vx*deltaX < 0)
            cout << "up\n" << vx << ' ' << deltaX << endl;
    }
    ///cout << "up\n" << ' ' << deltaY << endl;
}

void Motion :: FallDown(int& x, int& y, const float& alpha, const int& t, bool cross)
{
    /// Fall: y(t) = 0.5gt^2
    /// vy = gt;
    int deltaY = g*t-0.5*g;
    y += deltaY;
    if (cross)
    {
        float vx = g*t / tan(alpha);
        int deltaX = vx + 0.5*(alpha > pi/2 ? -push_force : push_force);
        x += deltaX;
        if (vx*deltaX < 0)
            cout << "down\n" << vx << ' ' << deltaX << endl;
    }
   /// cout << "down\n" << ' ' << deltaY << endl;
}