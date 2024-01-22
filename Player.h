#pragma once
//#include "Engine/GameObject.h"
#include"GameActor.h"
#include"PlayerSkillsInclude.h"
constexpr float MOVE_VELOCITY = 10.0f /60;
class Player : public GameActor
{//Pimpl�Ƃ������T�O�A�悳����
    int hModel_;
    //�ړ������̒P�ʃx�N�g�����i�[
    XMVECTOR moveDirection_;
    //�ړ��x�N�g��
    XMVECTOR vMove_;
    //�ړ��ɂ�����t���[����������B�ړ����f������0��
    float moveTime_;

 //�X�L���o�^
    std::vector<SkillBase*>skills{ 4 };
    void ActivateSkill(int number);

    //���݂̃}�E�X���W�����[���h���W�ɕϊ����ĕԂ�
    XMVECTOR getMouseTargetPos();
    //target�̕����ɉ�]
    void FaceTargetDirection(const XMVECTOR& target_);
    //�ړ�+��]
    void calculateForMove(const XMVECTOR target_);
    
    void FaceMouseDirection();

    void move();
    
    void AddCamp()override;
    void RemoveCamp()override;
#ifdef _DEBUG
    //test
    AttackRangeQuad testQuad;
    AttackRangeCircle testCircle;
    AttackRangeCirculerSector testSector;
#endif // _DEBUG

    bool canMove();
protected:

public:
    //�R���X�g���N�^
    Player(GameObject* parent);

    //�f�X�g���N�^
    virtual ~Player();

    //������
    void Initialize() override;

    //�ʍX�V
    void ActorUpdate() override;

   

    bool isHit(const DirectX::XMVECTOR& target);

    //�`��
    void ActorDraw() override;

    //�J��
    void Release() override;

};