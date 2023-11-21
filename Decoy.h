#pragma once
#include "EnemyBase.h"
class Decoy:
    public EnemyBase
{
private:

public:
    Decoy(GameObject* parent);
    ~Decoy();

    void Initialize() override;
    void ActorUpdate() override;
    void Draw() override;
    void Release() override;
};

