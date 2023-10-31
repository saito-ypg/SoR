#include "Player.h"
#include"Engine/Model.h"
#include"Engine/Input.h"

//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"),hModel_(-1)
{
}

//�f�X�g���N�^
Player::~Player()
{
}       

//������
void Player::Initialize()
{
    hModel_ = Model::Load("Assets/psample.fbx");
    assert(hModel_ >= 0);
}

//�X�V
void Player::Update()
{
    if (Input::IsMouseButton(1))
    {
        GetMouseTargetPos(Input::GetMousePosition());
    }
}

//�`��
void Player::Draw()
{
    Model::SetTransform(hModel_,transform_);
    Model::Draw(hModel_);
}

//�J��
void Player::Release()
{
}
XMVECTOR Player::GetMouseTargetPos(XMFLOAT3 mouse)
{
    return;
}