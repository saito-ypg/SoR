#pragma once
#include "Engine/GameObject.h"
#include "ActorInfo.h"
class ActorCollider;
class GameActor :
    public GameObject{
protected:
    ActorInfo status_;
    bool isInvincible_;//���G��Ԃ��H
    
public:
    
    GameActor(GameObject* parent, const std::string& name); 
    void Update() override final;//info�֘A�̍X�V�͂��ׂẴL�����ł��̂ŁA�ʂ̍X�V��ActorUpdate�ɕ������邱��
    virtual void ActorUpdate()=0;//
};

