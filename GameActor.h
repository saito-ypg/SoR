#pragma once
#include<vector>
#include "Engine/GameObject.h"
#include "ActorInfo.h"
#include"CollisionManager.h"
#include"DamageData.h"
class ActorCollider; 
const float defTime = 25.0f;
class GameActor :public GameObject{
private:
    struct {
        float Time;//�����c�莞��
        float Velocity;//����
        XMVECTOR Dir;//�������K��
    } knockBack;
   
    protected:
    
    ActorInfo status_;
    bool isInvincible_;//���G��Ԃ��H
    bool isDead_;//HP0�ȉ��ɂȂ����炱��ς���Agameobject�Ƃ͕ʁH
    std::vector<int> hModels_;//���f���ԍ������X�g��

    void AddColliderCamp(GameActor *act, CAMPS camp);//�����蔻���o�^�A�p����Őw�c�Œ肷��
    virtual void AddCamp()=0;//�p���p
    void RemoveColliderCamp(GameActor* act, CAMPS camp);;//�����蔻�����
    virtual void RemoveCamp()= 0;//�p���p
    
    bool CanMove();//�W�Q�v�f�ɂ���ē����Ȃ���Ԃɂ��邩
    //void LoadModel(string filename);//���f����ǂݍ��݁AhModels_�ɒǉ��B�ǂݍ��߂���true
    
    void SimpleDraw();//�ȈՓI�Ƀ��f����`�悷��Bdraw���ŌĂ�
    void DrawCollision();//�e�X�g�p�A�����蔻���`��Bdraw���ŌĂ�
    int hCircle_;
    int hQuad_;
    int hSector_;
    void DrawHP();//HP��`�悷��B
public:
    float GetRadius()const{return status_.hitCircleRange_;}
    GameActor(GameObject* parent, const std::string& name); 
    virtual ~GameActor();
    void Update(const float& dt) override final;//info�֘A�̍X�V�͂��ׂẴL�����ł��̂ŁA�ʂ̍X�V��ActorUpdate�ɕ������邱��
    virtual void ActorUpdate(const float& dt)=0;//�p����Ŏ���
    void Draw() override final;//�ʂ̕`���ActorDraw�ɕ������邱��
    virtual void ActorDraw() = 0;
    void TakeAttacked(DamageData &dmg,XMVECTOR &dir);//�I�[�o�[���C�h���邩����
    Transform* GetTransformRef();
    void ForceMove(XMVECTOR move);
};

