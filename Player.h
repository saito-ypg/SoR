#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Player : public GameObject
{
    int hModel_;
    //���ꂽ�x�N�g�����X�N���[�����W���烏�[���h���W�ɕϊ����ĕԂ�
    XMVECTOR GetMouseTargetPos(XMFLOAT3 mouse);
    
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