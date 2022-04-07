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
    if (cross)
    {
        float vy = v0 - g*t;
        int deltaX = PRESS_FRAME * vy * cos(alpha);
        x += deltaX;
        ///int deltaY = vy*sin(alpha) - g*t + 0.5*g;
        int deltaY = vy*sin(alpha) + 0.5*g;
        y -= deltaY;
        cout << "up\n" << deltaX << ' ' << deltaY << ' ' << vy << endl;
        ///y -= PRESS_FRAME*vy*sin(alpha) - PRESS_FRAME*g*t + 0.5*g;
    }
    else
    {
        int deltaY = v0 - g*t + 0.5*g;
        y -= deltaY;
    }
}

void Motion :: FallDown(int& x, int& y, const float& alpha, const int& t, bool cross)
{
    /// Fall: y(t) = 0.5gt^2
    /// vy = gt;
    if (cross)
    {
        float vy = g*t;
        ///y += vy*PRESS_FRAME + g*t*PRESS_FRAME + 0.5*g*PRESS_FRAME*PRESS_FRAME;
        int deltaY = vy*PRESS_FRAME + 0.5*g*PRESS_FRAME*PRESS_FRAME;
        y += deltaY;
        float vx = vy * tan(alpha);
        int deltaX = vx * PRESS_FRAME;
        x += deltaX;
        
        cout << "down\n" << deltaX << ' ' << deltaY << ' ' << vy << endl;
    }
    else
    {
        int deltaY = g*t-0.5*g;
        y += deltaY;
    }
}