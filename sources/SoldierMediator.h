#pragma once
#include "MediatorBase.h"
#include"MediatorFactory.h"
class SoldierMediator :
    public MediatorBase
{
private:
    void DetermineNextState() override;

public:
    SoldierMediator(EnemyBase&e);
    ~SoldierMediator();
};

class SoldierMediatorFactory :public MediatorFactory
{
    std::unique_ptr<MediatorBase> createMediator(EnemyBase& enemy) override
    {
        return std::make_unique<SoldierMediator>(enemy);
    }
};