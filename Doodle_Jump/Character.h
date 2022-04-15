#ifndef CHARACTER_H
#define CHARACTER_H

/** Character's feature

    - Turn left, turn right when keydown
    - Stand on the platform
**/

#include "CommonFunc.h"
#include "ImgProcess.h"
#include "Platform.h"
#include "Motion.h"

#define key_event first
#define times second

enum class d_MoveType
{
    LEFT = 0, RIGHT, FLY, JUMP, d_NumberOfMoveType, INVALID
};

const string d_MoveTypeImg[] = {"left.png", "right.png", "fly.png"};

/// Speed
const int d_MoveStep = 20;
const int d_MoveSpeed = 15;
const int d_JumpSpeed = 5;
const int d_FallSpeed = 3;
const int d_FlySpeed = 30;

/// Jump
/// T = v0sina/g
const int d_MaxJumpTimes = v0 / g;
const float d_VisibleRatio = 0.55;

/// other constants
const int d_SidesToLegs[] = {17, 24};

///#define CHARACTER_H_DEBUG
#ifndef CHARACTER_H_DEBUG

class Character: public ImgProcess
{
public:

    Character();
    ~Character();

    void Init(SDL_Renderer* renderer, const string& path);
    d_MoveType GetMoveType(const SDL_Event& event);
    void Render(SDL_Renderer* renderer);
    bool Jump();
    void Fall();
    void Cross(d_MoveType side);
    bool DoOutOfFrame();
    SDL_Rect GetLegsRect();

    friend class Game;

private:

    d_MoveType d_move;
    int d_JumpTimes;
    int d_FallTimes;
    bool* d_CurrentMoveType = new bool[uint16_t(d_MoveType::d_NumberOfMoveType)];
    ImgProcess* d_Img = new ImgProcess[uint16_t(d_MoveType::d_NumberOfMoveType)];
    Mix_Chunk *landing;
    pair <d_MoveType, int> move_event;/// = {0,0};
};

#else

class Character: public ImgProcess
{
public:

    Character();
    ~Character();

    void Init(SDL_Renderer* renderer, const string& path);
    d_MoveType GetMoveType(const SDL_Event& event);
    d_MoveType GetMoveType(const int& key);
    void Render(SDL_Renderer* renderer);
    void ChangePosition(d_MoveType MoveType, bool change_side);
    bool OnPlatform(Platform& platform);
    bool DoJump(Platform& platform);
    void DoActions(Platform& platform);
    bool DoOutOfFrame();
    void PushAction(const SDL_Event& event);
    SDL_Rect GetLegsRect();

    friend class Motion;

private:

    d_MoveType d_move;
    int d_JumpTimes;
    int d_FallTimes;
    bool* d_CurrentMoveType = new bool[uint16_t(d_MoveType::d_NumberOfMoveType)];
    ImgProcess* d_Img = new ImgProcess[uint16_t(d_MoveType::d_NumberOfMoveType)];
    Mix_Chunk *landing;
    Motion motion;
    queue <pair<int,int>> event_queue;
};

#endif /// CHARACTER_H_DEBUG

#endif // CHARACTER_H

