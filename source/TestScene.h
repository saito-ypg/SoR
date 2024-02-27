#pragma once
#include "../Engine/GameObject.h"
class TestScene :
    public GameObject
{
public:
    TestScene(GameObject* parent);
    void Initialize() override;
    void Update(const float& dt) override;
    void Draw() override;
    void Release() override;
};

