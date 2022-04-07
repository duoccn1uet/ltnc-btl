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

class Character: public ImgProcess
{
public:

    Character();
    ~Character();

    void Init(SDL_Renderer* renderer, const string& path);
    d_MoveType GetMoveType(const SDL_Event& event);
    void Render(SDL_Renderer* renderer);
    void ChangePosition(d_MoveType MoveType, bool change_side);
    bool OnPlatform(Platform& platform);
    bool DoJump(Platform& platform, const d_MoveType& move_type);
    void DoActions(Platform& platform, const d_MoveType& move_type);
    bool DoOutOfFrame();
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
};

#endif // CHARACTER_H

