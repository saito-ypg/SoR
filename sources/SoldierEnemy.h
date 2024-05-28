#pragma once
#include "EnemyBase.h"
class SoldierEnemy : public EnemyBase
{
private:

public:
    SoldierEnemy(GameObject* parent);
    ~SoldierEnemy();
    void dyingDraw() override;
    void Initialize() override;
    void ActorUpdate(const float& dt) override;
    void ActorDraw() override;
    void Release() override;
};

