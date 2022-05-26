#include "Threat.h"

Threat :: Threat()
{
    fill(current_move_type, current_move_type+etoi(ThreatMoveType::nThreatMoveType), false);
    current_move_type[etoi(ThreatMoveType::NOT_MOVE)] = true;
}

Threat :: ~Threat()
{
    FreeThreat();
}

void Threat :: SetThreatType(const ThreatType& _type)
{
    if (type != _type)
    {
        type = _type;
        LoadImg(THREAT_FOLDER + ThreatTypeText[etoi(type)] + ".png");
    }
}

void Threat :: SetMotionType(const ThreatMotionType& mt)
{
    if (mt != motion_type)
    {
        motion_type = mt;
        switch (motion_type)
        {
            case ThreatMotionType::JUMP:
                SetMoveType(ThreatMoveType::JUMP);
                break;

            case ThreatMotionType::FLY:
            case ThreatMotionType::MOVE_ON_PLATFORM:
                SetMoveType(ThreatMoveType::RIGHT);
                break;
            
            default:
                break;
        }
    }
}

ThreatMotionType Threat :: GetDefaultMotionType()
{
    ThreatMotionType m_type;
    switch (type)
    {
        case ThreatType::FLY:
            m_type = ThreatMotionType::FLY;
            break;
        
        case ThreatType::JUMP:
            m_type = ThreatMotionType::JUMP;
            break;

        case ThreatType::MOVE_ON_PLATFORM:
            m_type = ThreatMotionType::MOVE_ON_PLATFORM;
            break;

        case ThreatType::TRAP:
            m_type = ThreatMotionType::NOT_MOVE;
            break;
    }
    return m_type;
}

void Threat :: CreateThreat(const ThreatType& _type, const ThreatMotionType& mt)
{
    SetThreatType(_type);
    SetMotionType(mt);
}

void Threat :: SetRect(const int& x, const int& y)
{
    ImgProcess::SetRect(x, y);
    t_x = d_rect.x;
    t_y = d_rect.y;
}

SDL_Rect Threat :: GetRect()
{
    d_rect.x = t_x;
    d_rect.y = t_y;
    return ImgProcess::GetRect();
}

void Threat :: SetMoveType(const ThreatMoveType mt)
{
    if (current_move_type[etoi(mt)] == true)
        return;
    fill(current_move_type, current_move_type+etoi(ThreatMoveType::nThreatMoveType), false);
    current_move_type[etoi(mt)] = true;
}

void Threat :: Move(int sign)
{
    switch (motion_type)
    {
        case ThreatMotionType::FLY:

            if (change_direction == true)
                t_y += sign*5*sin(t_x/10);
            t_x += sign*3;
            t_y += sign*5*sin(t_x/10);
            ///debug(sign*5*sin(t_x/10), d_rect.y);
            ///if (change_direction == true)
                ///t_x += sign*10;
            change_direction = false;
            ///cout << d_rect.y << endl;
            break;
        
        case ThreatMotionType::JUMP:
        {
            auto g = CurrentMoveType();
            if (g == ThreatMoveType::JUMP)
                Jump();
            if (g == ThreatMoveType::FALL)
                Fall();
            break;
        }

        case ThreatMotionType::MOVE_ON_PLATFORM:
            t_x += sign*5;
            break;

        case ThreatMotionType::NOT_MOVE:
            break;
    }
}

void Threat :: MoveLeft()
{
    SetMoveType(ThreatMoveType::LEFT);
    Move(-1);
}

void Threat :: MoveRight()
{
    SetMoveType(ThreatMoveType::RIGHT);
    Move(1);
}

void Threat :: Jump()
{
    SetMoveType(ThreatMoveType::JUMP);
    JumpUp(t_y, Threat_v0, ++jump_times, Threat_g);
    if (jump_times == MAX_JUMP_TIMES)
    {
        s_fall = 0;
        fall_times = 0;
        SetMoveType(ThreatMoveType::FALL);
    }
}

void Threat :: Fall()
{
    jump_times = 0;
    SetMoveType(ThreatMoveType::FALL);
    auto old_y = t_y;
    JumpUp(t_y, 0, ++fall_times, Threat_g);
    s_fall += abs(old_y - t_y);
    if (s_fall >= MAX_JUMP_HEIGHT)
    {
        ///t_y = old_y;
        t_y -= s_fall - MAX_JUMP_HEIGHT;
        jump_times = 0;
        SetMoveType(ThreatMoveType::JUMP);
    }
}

ThreatMoveType Threat :: CurrentMoveType()
{
    for(int i = 0; i < etoi(ThreatMoveType::nThreatMoveType); ++i)
        if (current_move_type[i])
            return static_cast <ThreatMoveType> (i);
    return ThreatMoveType::nThreatMoveType;
}

void Threat :: Render()
{
    d_rect.x = t_x;
    d_rect.y = t_y;
    LoadImg(THREAT_FOLDER + ThreatTypeText[etoi(type)] + ".png");
    ImgProcess::Render();
}

void Threat :: FreeThreat()
{
    type = ThreatType::nThreatType;
    motion_type = ThreatMotionType::nThreatMotionType;
    fill(current_move_type, current_move_type+etoi(ThreatMoveType::nThreatMoveType), false);
    change_direction = false;
    t_x = 0, t_y = 0;
    s_fall = 0;
    Free();
}