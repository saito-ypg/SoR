
#include"Engine/Model.h"
#include "Ground.h"
//�R���X�g���N�^
Ground::Ground(GameObject* parent)
    :GameObject(parent, "Ground")
{
}

//�f�X�g���N�^
Ground::~Ground()
{
}

//������
void Ground::Initialize()
{
    using Model::FAIL_READ;
    const int hModel= Model::Load("ground.fbx");
    assert(hModel !=FAIL_READ);
    staticObjects.push_back(StaticObject(hModel,transform_));

    const int hModel1 = Model::Load("Props/House1.fbx");
    assert(hModel1 != FAIL_READ);
    Transform t1 = Transform();
    t1.position_ = { 23,0,18 };
    staticObjects.push_back(StaticObject(hModel1, t1));
}

//�X�V
void Ground::Update(const float& dt)
{
}

//�`��
void Ground::Draw()
{
    for (auto &[h,t] : staticObjects) {
        Model::SetTransform(h, t);
        Model::Draw(h);
    }
}

//�J��
void Ground::Release()
{
}
