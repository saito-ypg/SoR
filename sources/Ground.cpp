
#include"../Engine/Model.h"
#include "Ground.h"
//コンストラクタ
Ground::Ground(GameObject* parent)
    :GameObject(parent, "Ground"), hModel_(-1)
{
}

//デストラクタ
Ground::~Ground()
{
}

//初期化
void Ground::Initialize()
{
    hModel_ = Model::Load("ground.fbx");
    assert(hModel_ >= 0);
}

//更新
void Ground::Update(const float& dt)
{
}

//描画
void Ground::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Ground::Release()
{
}

int Ground::GetGloundHandle()
{
    return hModel_;
}
