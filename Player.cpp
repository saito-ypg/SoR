#include "Player.h"
#include"Ground.h"
#include"Engine/Model.h"
#include"Engine/Input.h"
#include"Engine/Camera.h"
//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1), moveTime_(0)
{
    moveDirection_ = XMVectorZero();
    vMove_ = XMVectorZero();
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
        XMFLOAT3 mousepos= Input::GetMousePosition();
        std::string resStr = std::to_string(mousepos.x) + "," + std::to_string(mousepos.y) + "\n";
        OutputDebugString(resStr.c_str());
        XMVECTOR target= GetMouseTargetPos(XMFLOAT3{mousepos.x,mousepos.y,0});
        Move(target);
   
    }
    //各入力

    if (moveTime_ > 0)
    {
        vMove_ = moveDirection_ * MOVE_VELOCITY;
        if (moveTime_ < 1)
        {
            XMVECTOR vpos = XMLoadFloat3(&transform_.position_);
            vpos += moveDirection_ * MOVE_VELOCITY *moveTime_;
            XMStoreFloat3(&transform_.position_, vpos);
            moveTime_ = 0;
        }
        else
        {
            XMVECTOR vpos = XMLoadFloat3(&transform_.position_);
            vpos += moveDirection_ * MOVE_VELOCITY;
            XMStoreFloat3(&transform_.position_, vpos);
            moveTime_--;
        }
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
    XMMATRIX matInv = Camera::GetInverseMatrix();
    XMFLOAT3 front = mouse, back = mouse;
    back.z = 1.0f;
    XMVECTOR vFront = XMVector3TransformCoord(XMLoadFloat3(&front), matInv);
    XMVECTOR vBack = XMVector3TransformCoord(XMLoadFloat3(&back), matInv);
    Ground* pGround = (Ground*)FindObject("Ground");
    int hG = pGround->GetGloundHandle();
    RayCastData data;
    XMStoreFloat4(&data.start, vFront);
    XMStoreFloat4(&data.dir,vBack - vFront);
    //Model::SetTransform(hG, transform_);
    Model::RayCast(hG, data);
    if (data.hit)
    {
        XMVECTOR vpos = XMLoadFloat4(&data.dir);
        vpos *= data.dist;
        XMVECTOR vstart = XMLoadFloat4(&data.start);
        return (vstart + vpos);
    }
  return XMVectorSplatQNaN();
}

void Player::Move(XMVECTOR target_)
{
    //移動情報の計算
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    moveDirection_ = XMVector3Normalize(target_-vPos);
    float length =XMVectorGetX(XMVector3Length(target_ - vPos));
    moveTime_ = length / MOVE_VELOCITY;
    
    //移動方向を向く
    XMVECTOR vfront = XMVector3Normalize(XMVectorSet(0, 0, 1, 0));
    float dot=XMVectorGetX(XMVector3Dot(moveDirection_, vfront));
    float angle = acos(dot);
    XMVECTOR vCross = XMVector3Cross(vfront, moveDirection_);
    if (XMVectorGetY(vCross) < 0) { angle *= -1; }
    transform_.rotate_.y = XMConvertToDegrees(angle);
}
