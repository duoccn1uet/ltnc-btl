#include "Character.h"

///#define CHARACTER_DEBUG
#ifndef CHARACTER_DEBUG

int max_jump_times;
float jump_speed;

Character :: Character()
{
    jump_times = 0;
    fall_times = 0;
    d_move = CharacterMoveType::RIGHT;
    for(int i = 0; i < int(CharacterMoveType::d_NumberOfMoveType); ++i)
        current_move_type[i] = false;
    current_move_type[short(CharacterMoveType::RIGHT)] = true;
    current_move_type[int(CharacterMoveType::JUMP)] = true;
}

Character :: ~Character()
{
    delete[] d_Img;
    delete[] current_move_type;
    Mix_FreeChunk(landing);
}

void Character :: Init()
{
    int i = 0;
    for(string s : d_MoveTypeImg)
        d_Img[i++].LoadImg(CHARACTER_FOLDER + s);
    d_rect = d_Img[0].GetRect();
    LoadSound(landing, SOUND_FOLDER + "landing.wav");
}

SDL_Rect Character :: GetLegsRect()
{
    int SubR, SubL;
    if (current_move_type[int(CharacterMoveType::RIGHT)])
        SubR = 24, SubL = 17; else
    if (current_move_type[int(CharacterMoveType::LEFT)])
        SubR = 17, SubL = 24;
    SDL_Rect res = {d_rect.x + SubL, d_rect.y+d_rect.h-leg_height, d_rect.w - SubR - SubL, leg_height};
    return res;
}

CharacterMoveType Character :: GetMoveType()
{
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_RIGHT:
            return CharacterMoveType::RIGHT;

        case SDLK_LEFT:
            return CharacterMoveType::LEFT;
            
        default:
            return CharacterMoveType::INVALID;
        }
    }
    return CharacterMoveType::INVALID;
}

void Character :: Render()
{
    d_Img[int(d_move)].SetRect(d_rect.x, d_rect.y);
    d_Img[int(d_move)].Render(nullptr);
}

void Character :: Cross(CharacterMoveType side)
{
    if (move_event.times != 0)
        side = move_event.key_event;
    if (side != CharacterMoveType::INVALID)
    {
        int sign = (current_move_type[uint16_t(CharacterMoveType::JUMP)] ? 1 : -1);
        float alpha = sign * pi/2;
        if (move_event.times == 0)
            move_event = {side, PRESS_FRAME};
        --move_event.times;
        d_move = side;
        if (side == CharacterMoveType::RIGHT)
        {
            alpha -= sign * delta_alpha;
            current_move_type[short(side)] = true;
            if (current_move_type[short(CharacterMoveType::LEFT)])
            {
                d_rect.x += d_MoveStep;
                current_move_type[short(CharacterMoveType::LEFT)] = false; 
            }
        }
        if (side == CharacterMoveType::LEFT)
        {
            alpha += sign * delta_alpha;
            current_move_type[short(side)] = true;
            if (current_move_type[short(CharacterMoveType::RIGHT)])
            {
                d_rect.x -= d_MoveStep;
                current_move_type[short(CharacterMoveType::RIGHT)] = false; 
            }
            
        }
        if (sign == 1)
            Motion::Cross(d_rect.x, jump_speed, alpha, jump_times);
        else
            Motion::Cross(d_rect.x, 0, alpha, fall_times);
    }
}

void Character :: Jump(int v0)
{
    current_move_type[etoi(CharacterMoveType::JUMP)] = true;
    jump_speed = v0;
    max_jump_times = jump_speed / g;
}

void Character :: Fall()
{
    JumpUp(d_rect.y, 0, ++fall_times);
}

void Character :: Move()
{
    if (current_move_type[etoi(CharacterMoveType::JUMP)] == true)
    {
        int t = ++jump_times;
        if (t > max_jump_times)
        {
            current_move_type[int(CharacterMoveType::JUMP)] = false;
            fall_times = 0;
            jump_times = 0;
            Fall();
        }
        else
            JumpUp(d_rect.y, jump_speed, t);
    }
    else
    {
        Fall();
    }
}

bool Character :: DoOutOfFrame()
{
    int visible_area = d_rect.h * (min(d_rect.x+d_rect.w, SCREEN_WIDTH) - max(0, d_rect.x));
    int real_area = d_rect.h * d_rect.w;
    if (float(visible_area) / real_area < d_VisibleRatio)
    {
        if (d_rect.x < 0) /// out of left side
            d_rect.x = SCREEN_WIDTH - d_rect.w;
        else
            d_rect.x = 0; /// out of right side
        return true;
    }
    return false;
}

bool Character :: CollectItem(Item& item)
{
    if (item.GetStatus() != ItemStatus::SHOW)
        return false;
    switch (item.GetType())
    {
        case ItemType::COIN:
            if (CheckCollision(d_rect, item.GetRect()))
            {
                item.SetItem(item.GetType(), ItemStatus::APPLY);
                item.RenderSound();
                return true;
            }
            break;
        case ItemType::SPRINGS:
            if (current_move_type[etoi(CharacterMoveType::JUMP)] == false && CheckCollision(GetLegsRect(), item.GetRect()))
            {
                SDL_Rect show_rect = item.GetRect();
                item.SetItem(item.GetType(), ItemStatus::APPLY);
                SDL_Rect apply_rect = item.GetRect();
                item.SetRect(show_rect.x, show_rect.y - (apply_rect.h - show_rect.h));
                item.RenderSound();
                Jump(HighSpeed);
                return true;
            }
        default:
            break;
    }
    return false;
}

#else

Character :: Character()
{
    jump_times = 0;
    fall_times = 0;
    d_move = CharacterMoveType::RIGHT;
    for(int i = 0; i < int(CharacterMoveType::d_NumberOfMoveType); ++i)
        current_move_type[i] = false;
    current_move_type[short(CharacterMoveType::RIGHT)] = true;
    current_move_type[int(CharacterMoveType::JUMP)] = true;
}

Character :: ~Character()
{
    delete[] d_Img;
    delete[] current_move_type;
    Mix_FreeChunk(landing);
}

void Character :: Init(const string& path)
{
    int i = 0;
    for(string s : d_MoveTypeImg)
        d_Img[i++].LoadImg(path + s);
    d_rect = d_Img[0].GetRect();
    LoadSound(landing, SOUND_FOLDER + "landing.wav");
}

SDL_Rect Character :: GetLegsRect()
{
    int SubR, SubL;
    if (current_move_type[int(CharacterMoveType::RIGHT)])
        SubR = 24, SubL = 17; else
    if (current_move_type[int(CharacterMoveType::LEFT)])
        SubR = 17, SubL = 24;
    /**if (current_move_type[int(CharacterMoveType::LEFT)])
        cout << "left\n";
    if (current_move_type[CharacterMoveType : : RIGHT])
        cout << "right\n";*/
    SDL_Rect res = {d_rect.x + SubL, d_rect.y+d_rect.h-8, d_rect.w - SubR - SubL, 1};
    return res;
}

bool Character :: OnPlatform(Platform& platform)
{
    /**int d_LeftToLegs = d_SidesToLegs[int(CharacterMoveType::LEFT)];
    int d_RightToLegs = d_SidesToLegs[CharacterMoveType : : RIGHT];
    if (current_move_type[int(CharacterMoveType::LEFT)] == true)
        swap(d_LeftToLegs, d_RightToLegs);
    SDL_Rect g = {d_rect.x + d_LeftToLegs, d_rect.y+d_rect.h-8, d_rect.w - d_RightToLegs - d_LeftToLegs, 1};*/
    ///cout << g.x << ' ' << g.y << ' ' << g.w << ' ' << g.h << endl;
    return platform.CharacterStandOn(GetLegsRect());
}

void Character :: ChangePosition(CharacterMoveType MoveType, bool change_side)
{
    /**int t = (current_move_type[int(CharacterMoveType::JUMP)] == true ? jump_times : fall_times);
    int vy = (current_move_type[int(CharacterMoveType::JUMP)] == true ? v0 - g*t : g*t);
    int deltaX = (vy + 10) * cosa;
    ///deltaX = 10;
    ///if (change_side) cout << deltaX << endl;
    if (MoveType == CharacterMoveType::RIGHT)
    {
        if (change_side)
            d_rect.x += d_MoveStep;
        d_rect.x += deltaX;
    } else
    if (MoveType == CharacterMoveType::LEFT)
    {
        if (change_side)
            d_rect.x -= d_MoveStep;
        d_rect.x -= deltaX;
    }*/
}

CharacterMoveType Character :: GetMoveType()
{
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_RIGHT:
                return CharacterMoveType::RIGHT;

        case SDLK_LEFT:
                return CharacterMoveType::LEFT;
        default:
            return CharacterMoveType::INVALID;
        }
    }
    return CharacterMoveType::INVALID;
}

CharacterMoveType Character :: GetMoveType(const int& key)
{
    /**switch (int(key))
        {
        case SDLK_RIGHT:
                return CharacterMoveType::RIGHT;

        case SDLK_LEFT:
                return CharacterMoveType::LEFT;
        default:
            return CharacterMoveType::INVALID;
        }*/
    if (key == SDLK_RIGHT)
        return CharacterMoveType::RIGHT;
    if (key == SDLK_LEFT)
        return CharacterMoveType::LEFT;
    return CharacterMoveType::INVALID;
}

void Character :: Render()
{
    d_Img[int(d_move)].SetRect(d_rect.x, d_rect.y);
    d_Img[int(d_move)].Render(nullptr);
}

bool Character :: DoJump(Platform& platform)
{
    bool move = false;
    float alpha = pi/2;
    CharacterMoveType side = CharacterMoveType::INVALID;
    if (event_queue.size())
    {
        side = GetMoveType(event_queue.front().key_event);
        if (!--event_queue.front().times)
            event_queue.pop();
    }
    if (side != CharacterMoveType::INVALID)
    {
        d_move = side;
        if (side == CharacterMoveType::RIGHT)
        {
            alpha -= delta_alpha, move = true;
            current_move_type[short(side)] = true;
            if (current_move_type[short(CharacterMoveType::LEFT)])
            {
                d_rect.x += d_MoveStep;
                current_move_type[short(CharacterMoveType::LEFT)] = false; 
            }
        }
        if (side == CharacterMoveType::LEFT)
        {
            alpha += delta_alpha, move = true;
            current_move_type[short(side)] = true;
            if (current_move_type[short(CharacterMoveType::RIGHT)])
            {
                d_rect.x -= d_MoveStep;
                current_move_type[short(CharacterMoveType::RIGHT)] = false; 
            }
            
        }
    }
    if (current_move_type[int(CharacterMoveType::JUMP)])
    {
        ++jump_times;
        JumpUp(d_rect.x, d_rect.y, v0, alpha, jump_times, move);
        if (jump_times > max_jump_times)
        {
            current_move_type[int(CharacterMoveType::JUMP)] = false;
            fall_times = 0;
        }
    }
    else
    {
        FallDown(d_rect.x, d_rect.y, alpha, ++fall_times, move);
        if (OnPlatform(platform))
        {
            SDL_Delay(SHORT_DELAY);
            PlaySound(landing, 1);
            current_move_type[int(CharacterMoveType::JUMP)] = true;
            jump_times = 0;
            return true;
        }
    }
    return false;
}

bool Character :: DoOutOfFrame()
{
    int visible_area = d_rect.h * (min(d_rect.x+d_rect.w, SCREEN_WIDTH) - max(0, d_rect.x));
    int real_area = d_rect.h * d_rect.w;
    if (float(visible_area) / real_area < d_VisibleRatio)
    {
        if (d_rect.x < 0) /// out of left side
            d_rect.x = SCREEN_WIDTH - d_rect.w;
        else
            d_rect.x = 0; /// out of right side
        return true;
    }
    return false;
}

void Character :: DoActions(Platform& platform)
{
    DoJump(platform);
    DoOutOfFrame();
}

void Character :: PushAction()
{
    event_queue.emplace(event.key.keysym.sym, PRESS_FRAME);
}

#endif /// CHARACTER_DEBUG