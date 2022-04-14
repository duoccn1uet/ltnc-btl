#include "Character.h"

///#define CHARACTER_DEBUG
#ifndef CHARACTER_DEBUG

Character :: Character()
{
    d_JumpTimes = 0;
    d_FallTimes = 0;
    d_move = d_MoveType::RIGHT;
    for(int i = 0; i < int(d_MoveType::d_NumberOfMoveType); ++i)
        d_CurrentMoveType[i] = false;
    d_CurrentMoveType[short(d_MoveType::RIGHT)] = true;
    d_CurrentMoveType[int(d_MoveType::JUMP)] = true;
}

Character :: ~Character()
{
    delete[] d_Img;
    delete[] d_CurrentMoveType;
    Mix_FreeChunk(landing);
}

void Character :: Init(SDL_Renderer* renderer, const string& path)
{
    int i = 0;
    for(string s : d_MoveTypeImg)
        d_Img[i++].LoadImg(path + s, renderer);
    d_rect = d_Img[0].GetRect();
    LoadSound(landing, SOUND_FOLDER + "landing.wav");
}

SDL_Rect Character :: GetLegsRect()
{
    int SubR, SubL;
    if (d_CurrentMoveType[int(d_MoveType::RIGHT)])
        SubR = 24, SubL = 17; else
    if (d_CurrentMoveType[int(d_MoveType::LEFT)])
        SubR = 17, SubL = 24;
    SDL_Rect res = {d_rect.x + SubL, d_rect.y+d_rect.h-8, d_rect.w - SubR - SubL, 1};
    return res;
}

bool Character :: OnPlatform(Platform& platform)
{
    /**int d_LeftToLegs = d_SidesToLegs[int(d_MoveType::LEFT)];
    int d_RightToLegs = d_SidesToLegs[d_MoveType : : RIGHT];
    if (d_CurrentMoveType[int(d_MoveType::LEFT)] == true)
        swap(d_LeftToLegs, d_RightToLegs);
    SDL_Rect g = {d_rect.x + d_LeftToLegs, d_rect.y+d_rect.h-8, d_rect.w - d_RightToLegs - d_LeftToLegs, 1};*/
    ///cout << g.x << ' ' << g.y << ' ' << g.w << ' ' << g.h << endl;
    return platform.CharacterStandOn(GetLegsRect());
}

d_MoveType Character :: GetMoveType(const SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_RIGHT:
                return d_MoveType::RIGHT;

        case SDLK_LEFT:
                return d_MoveType::LEFT;
        default:
            return d_MoveType::INVALID;
        }
    }
    return d_MoveType::INVALID;
}

void Character :: Render(SDL_Renderer* renderer)
{
    d_Img[int(d_move)].SetRect(d_rect.x, d_rect.y);
    d_Img[int(d_move)].Render(renderer, nullptr);
}

bool Character :: DoJump(Platform& platform, d_MoveType move_type)
{
    bool move = false;
    float alpha = pi/2;
    if (move_event.times != 0)
        move_type = move_event.key_event;
    if (move_type != d_MoveType::INVALID)
    {
        if (move_event.times == 0)
            move_event = {move_type, PRESS_FRAME};
        --move_event.times;
        d_move = move_type;
        if (move_type == d_MoveType::RIGHT)
        {
            alpha -= delta_alpha, move = true;
            d_CurrentMoveType[short(move_type)] = true;
            if (d_CurrentMoveType[short(d_MoveType::LEFT)])
            {
                d_rect.x += d_MoveStep;
                d_CurrentMoveType[short(d_MoveType::LEFT)] = false; 
            }
        }
        if (move_type == d_MoveType::LEFT)
        {
            alpha += delta_alpha, move = true;
            d_CurrentMoveType[short(move_type)] = true;
            if (d_CurrentMoveType[short(d_MoveType::RIGHT)])
            {
                d_rect.x -= d_MoveStep;
                d_CurrentMoveType[short(d_MoveType::RIGHT)] = false; 
            }
            
        }
    }
    if (d_CurrentMoveType[int(d_MoveType::JUMP)])
    {
        ++d_JumpTimes;
        if (d_JumpTimes > d_MaxJumpTimes)
        {
            d_CurrentMoveType[int(d_MoveType::JUMP)] = false;
            d_FallTimes = 0;
        }
        else
            motion.JumpUp(d_rect.x, d_rect.y, v0, alpha, d_JumpTimes, move);
    }
    else
    {
        motion.FallDown(d_rect.x, d_rect.y, alpha, ++d_FallTimes, move);
        if (OnPlatform(platform))
        {
            SDL_Delay(SHORT_DELAY);
            PlaySound(landing, 1);
            d_CurrentMoveType[int(d_MoveType::JUMP)] = true;
            d_JumpTimes = 0;
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

void Character :: DoActions(Platform& platform, const d_MoveType& move_type)
{
    DoJump(platform, move_type);
    DoOutOfFrame();
}

#else

Character :: Character()
{
    d_JumpTimes = 0;
    d_FallTimes = 0;
    d_move = d_MoveType::RIGHT;
    for(int i = 0; i < int(d_MoveType::d_NumberOfMoveType); ++i)
        d_CurrentMoveType[i] = false;
    d_CurrentMoveType[short(d_MoveType::RIGHT)] = true;
    d_CurrentMoveType[int(d_MoveType::JUMP)] = true;
}

Character :: ~Character()
{
    delete[] d_Img;
    delete[] d_CurrentMoveType;
    Mix_FreeChunk(landing);
}

void Character :: Init(SDL_Renderer* renderer, const string& path)
{
    int i = 0;
    for(string s : d_MoveTypeImg)
        d_Img[i++].LoadImg(path + s, renderer);
    d_rect = d_Img[0].GetRect();
    LoadSound(landing, SOUND_FOLDER + "landing.wav");
}

SDL_Rect Character :: GetLegsRect()
{
    int SubR, SubL;
    if (d_CurrentMoveType[int(d_MoveType::RIGHT)])
        SubR = 24, SubL = 17; else
    if (d_CurrentMoveType[int(d_MoveType::LEFT)])
        SubR = 17, SubL = 24;
    /**if (d_CurrentMoveType[int(d_MoveType::LEFT)])
        cout << "left\n";
    if (d_CurrentMoveType[d_MoveType : : RIGHT])
        cout << "right\n";*/
    SDL_Rect res = {d_rect.x + SubL, d_rect.y+d_rect.h-8, d_rect.w - SubR - SubL, 1};
    return res;
}

bool Character :: OnPlatform(Platform& platform)
{
    /**int d_LeftToLegs = d_SidesToLegs[int(d_MoveType::LEFT)];
    int d_RightToLegs = d_SidesToLegs[d_MoveType : : RIGHT];
    if (d_CurrentMoveType[int(d_MoveType::LEFT)] == true)
        swap(d_LeftToLegs, d_RightToLegs);
    SDL_Rect g = {d_rect.x + d_LeftToLegs, d_rect.y+d_rect.h-8, d_rect.w - d_RightToLegs - d_LeftToLegs, 1};*/
    ///cout << g.x << ' ' << g.y << ' ' << g.w << ' ' << g.h << endl;
    return platform.CharacterStandOn(GetLegsRect());
}

void Character :: ChangePosition(d_MoveType MoveType, bool change_side)
{
    /**int t = (d_CurrentMoveType[int(d_MoveType::JUMP)] == true ? d_JumpTimes : d_FallTimes);
    int vy = (d_CurrentMoveType[int(d_MoveType::JUMP)] == true ? v0 - g*t : g*t);
    int deltaX = (vy + 10) * cosa;
    ///deltaX = 10;
    ///if (change_side) cout << deltaX << endl;
    if (MoveType == d_MoveType::RIGHT)
    {
        if (change_side)
            d_rect.x += d_MoveStep;
        d_rect.x += deltaX;
    } else
    if (MoveType == d_MoveType::LEFT)
    {
        if (change_side)
            d_rect.x -= d_MoveStep;
        d_rect.x -= deltaX;
    }*/
}

d_MoveType Character :: GetMoveType(const SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_RIGHT:
                return d_MoveType::RIGHT;

        case SDLK_LEFT:
                return d_MoveType::LEFT;
        default:
            return d_MoveType::INVALID;
        }
    }
    return d_MoveType::INVALID;
}

d_MoveType Character :: GetMoveType(const int& key)
{
    /**switch (int(key))
        {
        case SDLK_RIGHT:
                return d_MoveType::RIGHT;

        case SDLK_LEFT:
                return d_MoveType::LEFT;
        default:
            return d_MoveType::INVALID;
        }*/
    if (key == SDLK_RIGHT)
        return d_MoveType::RIGHT;
    if (key == SDLK_LEFT)
        return d_MoveType::LEFT;
    return d_MoveType::INVALID;
}

void Character :: Render(SDL_Renderer* renderer)
{
    d_Img[int(d_move)].SetRect(d_rect.x, d_rect.y);
    d_Img[int(d_move)].Render(renderer, nullptr);
}

bool Character :: DoJump(Platform& platform)
{
    bool move = false;
    float alpha = pi/2;
    d_MoveType move_type = d_MoveType::INVALID;
    if (event_queue.size())
    {
        move_type = GetMoveType(event_queue.front().key_event);
        if (!--event_queue.front().times)
            event_queue.pop();
    }
    if (move_type != d_MoveType::INVALID)
    {
        d_move = move_type;
        if (move_type == d_MoveType::RIGHT)
        {
            alpha -= delta_alpha, move = true;
            d_CurrentMoveType[short(move_type)] = true;
            if (d_CurrentMoveType[short(d_MoveType::LEFT)])
            {
                d_rect.x += d_MoveStep;
                d_CurrentMoveType[short(d_MoveType::LEFT)] = false; 
            }
        }
        if (move_type == d_MoveType::LEFT)
        {
            alpha += delta_alpha, move = true;
            d_CurrentMoveType[short(move_type)] = true;
            if (d_CurrentMoveType[short(d_MoveType::RIGHT)])
            {
                d_rect.x -= d_MoveStep;
                d_CurrentMoveType[short(d_MoveType::RIGHT)] = false; 
            }
            
        }
    }
    if (d_CurrentMoveType[int(d_MoveType::JUMP)])
    {
        ++d_JumpTimes;
        motion.JumpUp(d_rect.x, d_rect.y, v0, alpha, d_JumpTimes, move);
        if (d_JumpTimes > d_MaxJumpTimes)
        {
            d_CurrentMoveType[int(d_MoveType::JUMP)] = false;
            d_FallTimes = 0;
        }
    }
    else
    {
        motion.FallDown(d_rect.x, d_rect.y, alpha, ++d_FallTimes, move);
        if (OnPlatform(platform))
        {
            SDL_Delay(SHORT_DELAY);
            PlaySound(landing, 1);
            d_CurrentMoveType[int(d_MoveType::JUMP)] = true;
            d_JumpTimes = 0;
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

void Character :: PushAction(const SDL_Event& event)
{
    event_queue.emplace(event.key.keysym.sym, PRESS_FRAME);
}

#endif /// CHARACTER_DEBUG