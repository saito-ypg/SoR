#pragma once
//#include "Engine/GameObject.h"
#include"GameActor.h"
constexpr float MOVE_VELOCITY = 10.0f /60;
class Player : public GameActor
{
    int hModel_;
    //�ړ������̒P�ʃx�N�g�����i�[
    XMVECTOR moveDirection_;
    //�ړ��x�N�g��
    XMVECTOR vMove_;
    //�ړ��ɂ�����t���[����������B�ړ����f������0��
    float moveTime_;
    //���ꂽ�x�N�g�����X�N���[�����W���烏�[���h���W�ɕϊ����ĕԂ�
    XMVECTOR getMouseTargetPos(XMFLOAT3 mouse);
    
    void move(XMVECTOR target_);
public:
    //�R���X�g���N�^
    Player(GameObject* parent);

    //�f�X�g���N�^
    ~Player();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

};