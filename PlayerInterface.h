#pragma once
#include "Engine/GameObject.h"
class PlayerInterface :
    public GameObject
{
public:
    PlayerInterface(GameObject*parent);
    ~PlayerInterface();

    void Initialize()override;
    void Update(const float& dt)override;
    void Draw()override;
    void Release()override;
};

