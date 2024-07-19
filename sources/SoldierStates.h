#pragma once
#include "MovementStateBase.h"
constexpr float END_MOVE_THRESHOULD = 4.0f;

class SoldierStateMove :
    public MovementStateBase
{
public:

    SoldierStateMove(EnemyBase& base);
    ~SoldierStateMove();
    void Update(const float& dt)override;
    void Release();
};

