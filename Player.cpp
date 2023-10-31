#include "Player.h"
#include"Engine/Model.h"
#include"Engine/Input.h"

//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"),hModel_(-1)
{
}

//デストラクタ
Player::~Player()
{
}       

//初期化
void Player::Initialize()
{
    hModel_ = Model::Load("Assets/psample.fbx");
    assert(hModel_ >= 0);
}

//更新
void Player::Update()
{
    if (Input::IsMouseButton(1))
    {
        GetMouseTargetPos(Input::GetMousePosition());
    }
}

//描画
void Player::Draw()
{
    Model::SetTransform(hModel_,transform_);
    Model::Draw(hModel_);
}

//開放
void Player::Release()
{
}
XMVECTOR Player::GetMouseTargetPos(XMFLOAT3 mouse)
{
    return;
}