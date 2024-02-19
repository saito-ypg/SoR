#include "Ground.h"
#include"Engine/Model.h"

//�R���X�g���N�^
Ground::Ground(GameObject* parent)
    :GameObject(parent, "Ground"), hModel_(-1)
{
}

//�f�X�g���N�^
Ground::~Ground()
{
}

//������
void Ground::Initialize()
{
    hModel_ = Model::Load("Assets/Ground.fbx");
    assert(hModel_ >= 0);
}

//�X�V
void Ground::Update(const float& dt)
{
}

//�`��
void Ground::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Ground::Release()
{
}

int Ground::GetGloundHandle()
{
    return hModel_;
}
