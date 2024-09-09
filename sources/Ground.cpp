
#include"Engine/Model.h"
#include "Ground.h"
//コンストラクタ
Ground::Ground(GameObject* parent)
    :GameObject(parent, "Ground")
{
}

//デストラクタ
Ground::~Ground()
{
}

//初期化
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

//更新
void Ground::Update(const float& dt)
{
}

//描画
void Ground::Draw()
{
    for (auto &[h,t] : staticObjects) {
        Model::SetTransform(h, t);
        Model::Draw(h);
    }
}

//開放
void Ground::Release()
{
}
