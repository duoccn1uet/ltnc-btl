#ifndef THREAT_H
#define THREAT_H

#include "CommonFunc.h"
#include "ImgProcess.h"
#include "Motion.h"

enum class ThreatType: short
{
    FLY, MOVE_ON_PLATFORM, JUMP, TRAP, nThreatType, INVALID
};

const string ThreatTypeText[] = {"fly", "move_on_platform", "jump", "trap"};

enum class ThreatMotionType: short
{
    FLY, MOVE_ON_PLATFORM, NOT_MOVE, JUMP, nThreatMotionType
};

enum class ThreatMoveType: short
{
    LEFT, RIGHT, JUMP, FALL, NOT_MOVE, nThreatMoveType
};

const float Threat_g = 0.09;
const float Threat_v0 = 3;
const float MAX_JUMP_HEIGHT = Threat_v0*Threat_v0/(2*Threat_g);
const int MAX_JUMP_TIMES = Threat_v0/Threat_g;
const int MAX_FALL_TIMES = Threat_v0/Threat_g;

class Threat: public ImgProcess
{
public:

    Threat();
    ~Threat();

    void SetThreatType(const ThreatType& _type);
    ThreatType GetType() {return type;}
    ThreatMotionType GetMotionType() {return motion_type;}
    void SetMotionType(const ThreatMotionType& mt);
    ThreatMotionType GetDefaultMotionType();
    void CreateThreat(const ThreatType& _type, const ThreatMotionType& mt);
    void SetRect(const int& x, const int& y);
    SDL_Rect GetRect();

    /// Moving
    void SetMoveType(const ThreatMoveType mt);
    void Move(int sign = 1);
    /// Fly
    void MoveLeft();
    void MoveRight();

    /// Jump
    void Jump();
    void Fall();

    void ChangeDirection() {change_direction = true;}
    ThreatMoveType CurrentMoveType();
    void Render();
    void FreeThreat();

private:

    ThreatType type = ThreatType::nThreatType;
    ThreatMotionType motion_type = ThreatMotionType::nThreatMotionType;
    bool current_move_type[uint16_t(ThreatMoveType::nThreatMoveType)];
    bool change_direction = false;
    float t_x = 0, t_y = 0;

    /// Moving
    /// Jump
    int jump_times = 0, fall_times = 0;
    float s_fall = 0;
};

#endif THREAT_H