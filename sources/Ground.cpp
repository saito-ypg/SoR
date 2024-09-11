
#include"Engine/Model.h"
#include "Ground.h"
#include"Engine/Input.h"
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

    /*const int hModel1 = Model::Load("Props/House1.fbx");
    assert(hModel1 != FAIL_READ);
    Transform t1 = Transform();
    t1.scale_ = { 0.01f,0.01f,0.01f };
    staticObjects.push_back(StaticObject(hModel1, t1));*/
    const int hModel2 = Model::Load("Props/old_cottage.fbx");
    assert(hModel2 != FAIL_READ);
    Transform t2 = Transform();
    t2.position_ = { 26,0,10 };
    t2.rotate_.y = 90;
    staticObjects.push_back(StaticObject(hModel2, t2));
}

//�X�V
void Ground::Update(const float& dt)
{

    //{//debug�p
    //    auto& t=staticObjects.at(1).transform;
    //    if (Input::IsKey(DIK_RIGHT))
    //        t.rotate_.y++;
    //    if (Input::IsKey(DIK_LEFT))
    //        t.rotate_.y--;
    //}
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
