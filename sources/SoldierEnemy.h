#pragma once
#include "EnemyBase.h"

//åªèÛñ¢é¿ëï
class SoldierEnemy : public EnemyBase
{
private:

public:
    SoldierEnemy(GameObject* parent, bool isBoss = false);
    ~SoldierEnemy();
    void dyingDraw() override;
    void Initialize() override;
    void ActorUpdate(const float& dt) override;
    void ActorDraw() override;
    void ActorRelease() override;

};

