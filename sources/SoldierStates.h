#pragma once
#include "MovementStateBase.h"
class SoldierStateMove :
    public MovementStateBase
{
public:
    SoldierStateMove(EnemyBase& base);
    ~SoldierStateMove();
    void Update(const float& dt)override;
    void Release();
};

