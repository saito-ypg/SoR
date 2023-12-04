#pragma once
#include "Engine/GameObject.h"
#include "ActorInfo.h"
class ActorCollider;
class GameActor :public GameObject{
protected:
    ActorInfo status_;
    bool isInvincible_;//���G��Ԃ��H

public:
    float GetRadius(){return status_.hitCircleRange_;}
    GameActor(GameObject* parent, const std::string& name); 
    virtual ~GameActor();
    void Update() override final;//info�֘A�̍X�V�͂��ׂẴL�����ł��̂ŁA�ʂ̍X�V��ActorUpdate�ɕ������邱��
    virtual void ActorUpdate()=0;//�p����Ŏ���
    void TakeAttacked() const;//�I�[�o�[���C�h���邩����
    Transform* GetTransformRef();
};

