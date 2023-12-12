#include "Player.h"
#include"Ground.h"
#include"Engine/Model.h"
#include"Engine/Input.h"
#include"Engine/Camera.h"
constexpr XMVECTOR NotHitV{ 9999,9999,9999,9999 };
bool nearlyZero(float f) {//ほぼ0であるといえるならtrue
    return (int)(f * 10000) == 0;
}
//コンストラクタ
Player::Player(GameObject* parent)
    :GameActor(parent, "Player"), hModel_(-1), moveTime_(0)
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
    status_ = { 200,1.1 };
    AddCamp();
}

//更新
void Player::ActorUpdate()
{
    {//速度テスト用   
        if (Input::IsKeyDown(DIK_1))
            SetVelocity(1.0f);
        if (Input::IsKeyDown(DIK_2))
            SetVelocity(2.0f);
        if (Input::IsKeyDown(DIK_0))
            SetVelocity(0.0f);
    }

    if (nearlyZero(GetMyVelocity()))//更新速度がほぼほぼ0ならあとの処理飛ばす
        return;

    if (Input::IsKeyDown(DIK_Z))
    {
        AttackRangeQuad testQuad(transform_.position_);
        testQuad.length_ = 2;
        testQuad.width_ = 2;
        testQuad.rotate_ =0;
        CollisionManager::HitTestBy(PLAYER, testQuad);
    }
    if (Input::IsKeyDown(DIK_X))
    {
        AttackRangeCircle testCircle(transform_.position_);
        testCircle.radius_ = 1;
        CollisionManager::HitTestBy(PLAYER, testCircle);
    }
    if (Input::IsKeyDown(DIK_C))
    {
        AttackRangeCirculerSector testSector(transform_.position_);
        testSector.radius_ = 1;
        testSector.rotate_ = transform_.rotate_.y;
        testSector.centerAngle_ = 45;
        CollisionManager::HitTestBy(PLAYER, testSector);
    }

    if (Input::IsMouseButton(1))
    {
        XMVECTOR target= getMouseTargetPos(Input::GetMousePosition());
        if(XMComparisonAnyFalse(XMVector3EqualR(target, NotHitV)))
            calculateForMove(target);
    }
    //各入力
    if(Input::IsMouseButton(0))
    { }
    if (moveTime_ > 0)
    {
        move();
    }

}

void Player::move()
{
    vMove_ = moveDirection_ * MOVE_VELOCITY * GetVelocity();
    if (moveTime_ < 1)
    {
        XMVECTOR vpos = XMLoadFloat3(&transform_.position_);
        vpos += vMove_ * moveTime_;
        XMStoreFloat3(&transform_.position_, vpos);
        moveTime_ = 0;
    }
    else
    {
        XMVECTOR vpos = XMLoadFloat3(&transform_.position_);
        vpos += vMove_;
        XMStoreFloat3(&transform_.position_, vpos);
        moveTime_ -= GetVelocity();
    }
}

void Player::AddCamp()
{
    AddColliderCamp((GameActor*)this, PLAYER);
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

XMVECTOR Player::getMouseTargetPos(XMFLOAT3 mouse)
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
    return NotHitV;
}

void Player::calculateForMove(XMVECTOR target_)
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
