#pragma once
#include "Engine/GameObject.h"
class GameActor :
    public GameObject{
protected:
    float hitCircleRange;
    float hp_;
public:
    GameActor(GameObject* parent, const std::string& name); 
    void SetHitRange(float range);
};

