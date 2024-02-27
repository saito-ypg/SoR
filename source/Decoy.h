#pragma once
#include "EnemyBase.h"
class Decoy:
    public EnemyBase
{
private:

public:
    Decoy(GameObject* parent);
    ~Decoy();
    void dyingDraw() override;
    void Initialize() override;
    void ActorUpdate(const float& dt) override;
    void ActorDraw() override;
    void Release() override;
};

