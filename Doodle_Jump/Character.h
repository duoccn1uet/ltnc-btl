#ifndef CHARACTER_H
#define CHARACTER_H

/** Character's feature

    - Turn left, turn right when keydown
    - Stand on the platform
**/

#include "CommonFunc.h"
#include "ImgProcess.h"
#include "Platform.h"
#include "Item.h"
#include "Motion.h"

#define key_event first
#define times second

enum class CharacterMoveType
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
const float d_VisibleRatio = 0.55;

/// speed
const float NormalSpeed = v0;
const float HighSpeed = NormalSpeed * 1.7;
/// other constants
const int d_SidesToLegs[] = {17, 24};
const int leg_height = 20;

///#define CHARACTER_H_DEBUG
#ifndef CHARACTER_H_DEBUG

class Character: public ImgProcess
{
public:

    Character();
    ~Character();

    void Init(const string& path);
    CharacterMoveType GetMoveType(const SDL_Event& event);
    void Render();
    void Move();
    void Jump(int v0);
    void Fall();
    void Cross(CharacterMoveType side);
    bool CollectItem(Item& item);
    bool DoOutOfFrame();
    SDL_Rect GetLegsRect();

    friend class Game;

private:

    CharacterMoveType d_move;
    int jump_times;
    int fall_times;
    bool* current_move_type = new bool[uint16_t(CharacterMoveType::d_NumberOfMoveType)];
    ImgProcess* d_Img = new ImgProcess[uint16_t(CharacterMoveType::d_NumberOfMoveType)];
    Mix_Chunk *landing;
    pair <CharacterMoveType, int> move_event;/// = {0,0};
};

#else

class Character: public ImgProcess
{
public:

    Character();
    ~Character();

    void Init(const string& path);
    CharacterMoveType GetMoveType(const SDL_Event& event);
    CharacterMoveType GetMoveType(const int& key);
    void Render();
    void ChangePosition(CharacterMoveType MoveType, bool change_side);
    bool OnPlatform(Platform& platform);
    bool DoJump(Platform& platform);
    void DoActions(Platform& platform);
    bool DoOutOfFrame();
    void PushAction(const SDL_Event& event);
    SDL_Rect GetLegsRect();

    friend class Motion;

private:

    CharacterMoveType d_move;
    int jump_times;
    int fall_times;
    bool* current_move_type = new bool[uint16_t(CharacterMoveType::d_NumberOfMoveType)];
    ImgProcess* d_Img = new ImgProcess[uint16_t(CharacterMoveType::d_NumberOfMoveType)];
    Mix_Chunk *landing;
    Motion motion;
    queue <pair<int,int>> event_queue;
};

#endif /// CHARACTER_H_DEBUG

#endif // CHARACTER_H

