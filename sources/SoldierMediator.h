#pragma once
#include "MediatorBase.h"
class SoldierMediator :
    public MediatorBase
{
private:
    void DetermineNextState() override;

public:
    SoldierMediator(EnemyBase&y);
    ~SoldierMediator();
    


    
};

