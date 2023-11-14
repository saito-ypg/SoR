#pragma once
#include "Engine/GameObject.h"
#include "ActorInfo.h"

class GameActor :
    public GameObject{
protected:
    ActorInfo status_;
public:
    GameActor(GameObject* parent, const std::string& name); 
};

