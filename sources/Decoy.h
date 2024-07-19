#pragma once
#include "EnemyBase.h"
class Decoy:
    public EnemyBase
{
private:

public:
    Decoy(GameObject* parent, bool isBoss=false);
    ~Decoy();
    void dyingDraw() override;
    void Initialize() override;
    void ActorUpdate(const float& dt) override;
    void ActorDraw() override;
    void ActorRelease() override;
};

