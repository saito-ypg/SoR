#pragma once
#include<vector>
#include "Engine/GameObject.h"
#include "ActorInfo.h"
#include"CollisionManager.h"

class ActorCollider;
class GameActor :public GameObject{
protected:
    ActorInfo status_;
    bool isInvincible_;//���G��Ԃ��H
    std::vector<int> hModels_;//���f���ԍ������X�g��

    void AddColliderCamp(GameActor *act, CAMPS camp);//�����蔻���o�^�A�p����Őw�c�Œ肷��
    virtual void AddCamp()=0;//�p���p

    //void LoadModel(string filename);//���f����ǂݍ��݁AhModels_�ɒǉ��B�ǂݍ��߂���true
    void SimpleDraw();//�ȈՓI�Ƀ��f����`�悷��B


public:
    float GetRadius()const{return status_.hitCircleRange_;}
    GameActor(GameObject* parent, const std::string& name); 
    virtual ~GameActor();
    void Update() override final;//info�֘A�̍X�V�͂��ׂẴL�����ł��̂ŁA�ʂ̍X�V��ActorUpdate�ɕ������邱��
    virtual void ActorUpdate()=0;//�p����Ŏ���

    void TakeAttacked();//�I�[�o�[���C�h���邩����
    Transform* GetTransformRef();
};

