#pragma once
#include<vector>
#include "../Engine/GameObject.h"
#include "ActorInfo.h"
#include"CollisionManager.h"
#include"DamageData.h"
using namespace AreaModels;
class ActorCollider; 
const float defTime = 35.0f;
class GameActor :public GameObject{
private:
    struct {
        float Time;//�����c�莞��
        float Velocity;//����
        XMVECTOR Dir;//����
    } knockBack;
   
protected:
    
    ActorInfo status_;
    bool isInvincible_;//���G��Ԃ��H
    bool isdying;//HP0�ȉ��ɂȂ����炱��ς���A�񕜂��Ă����񂾂܂�
    bool  IsDying_()const { return isdying; }
    int hBody_;//��{�ƂȂ郂�f���̕`��
    std::vector<int> hModels_;//Body�ȊO�̕⏕�I�ȃ��f���ԍ���z���

    //�����蔻���o�^�A�p����Őw�c�Œ肷��
    void AddColliderCamp(GameActor *act, CAMPS camp);
    //�p���p
    virtual void AddCamp()=0;
    //�����蔻�����
    void RemoveColliderCamp(GameActor* act, CAMPS camp);
    //�p���p
    virtual void RemoveCamp()= 0;

    //�W�Q�v�f�ɂ���ē����Ȃ���Ԃɂ��邩?(������)
    bool CanMoveWithEffects();

    //���f���{�̂�`�悷��BActorDraw���ŌĂ�
    void DrawBody();
    //�e�X�g�p�A�����蔻���`��Bdraw���ŌĂ�
    void DrawCollision();
    //HP��`�悷��
    void DrawHP() const;

    //���S�������B�Ȃ��Ȃ�Ȃ��ł悵
    virtual void dyingProcess();
    //���S���`��B�|���A�j���[�V�����Ƃ�
    virtual void dyingDraw();
public:
    float GetRadius()const{return status_.hitCircleRange_;}
    GameActor(GameObject* parent, const std::string& name); 
    virtual ~GameActor();

    //actor�ŋ��ʂ̕`����s�����߁A�ʂ̍X�V��ActorUpdate�ɕ������邱��
    void Update(const float& dt) override final;
    //�p����Ŏ����B�ʂ̍X�V
    virtual void ActorUpdate(const float& dt)=0;
    //actor�ŋ��ʂ̕`����s�����߁A�ʂ̕`���ActorDraw�ɕ������邱��
    void Draw() override final;
    //�p����Ŏ����B�ʂ̋��L
    virtual void ActorDraw() = 0;
    //�I�[�o�[���C�h���邩����
    void TakeAttacked(DamageData &dmg,XMVECTOR &dir);
    Transform* GetTransformRef();
    //move�̕������ړ�������
    void ForceMove(XMVECTOR translateBy);
};

