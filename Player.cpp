#include "Player.h"
#include"Ground.h"
#include"Engine/Model.h"
#include"Engine/Input.h"
#include"Engine/Camera.h"
constexpr XMVECTOR NotHitV{ 9999,9999,9999,9999 };
constexpr float PLAYER_ROT_TH = 0.1f;//移動時に回転するかどうかの距離のしきい値
bool nearlyZero(float f) {//ほぼ0であるといえるならtrue。
    return XMScalarNearEqual(f, 0.0f, 0.0001f);
}

//コンストラクタ
Player::Player(GameObject* parent)
    :GameActor(parent, "Player"), hModel_(-1), moveTime_(0)
{
    status_.maxHp_ = 200;
    status_.hp_ = status_.maxHp_;
    status_.hitCircleRange_ = 1.1f;
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
    hModel_ = Model::Load("Assets/Charactors/psample.fbx");
    assert(hModel_ >= 0);

    AddCamp();


    skills.at(0) = dynamic_cast<SkillBase*>(new testSkill);
}

//更新
void Player::ActorUpdate()
{
#ifdef _DEBUG
    {//速度テスト用   
        if (Input::IsKeyDown(DIK_1))
            SetVelocity(1.0f);
        if (Input::IsKeyDown(DIK_2))
            SetVelocity(2.0f);
        if (Input::IsKeyDown(DIK_0))
            SetVelocity(0.0f);
        if (nearlyZero(GetMyVelocity()))//更新速度がほぼほぼ0ならあとの処理飛ばす
            return;
    }

    //当たり判定テスト用
    if (Input::IsKeyDown(DIK_Z))
    {
        FaceMouseDirection();

        testQuad.position_ = transform_.position_;
        testQuad.length_ = 2;
        testQuad.width_ = 5;
        testQuad.rotate_ =transform_.rotate_.y;
        CollisionManager::HitTestBy(PLAYER, testQuad);
    }
    if (Input::IsKeyDown(DIK_X))
    {
        FaceMouseDirection();
        testCircle.position_=transform_.position_;
        testCircle.radius_ = 2.2f;
        CollisionManager::HitTestBy(PLAYER, testCircle);
    }
    if (Input::IsKeyDown(DIK_C))
    {
        FaceMouseDirection();
        testSector.position_=transform_.position_;
        testSector.radius_ =3;
        testSector.rotate_ = transform_.rotate_.y;
        testSector.centerAngle_ = 30;
        CollisionManager::HitTestBy(PLAYER, testSector);
    }

    if (Input::IsKeyDown(DIK_A))
        transform_.rotate_.y = XMConvertToDegrees((float)atan2(-transform_.position_.x, -transform_.position_.z));
#endif

    if (Input::IsMouseButton(1))//移動
    {
        XMVECTOR target= getMouseTargetPos();
        if (isHit(target))
            calculateForMove(target);
    }
    //各入力
    if(Input::IsMouseButton(0))//通常攻撃
    {

    }
    else if (Input::IsKeyDown(DIK_Q))
    {
        ActivateSkill(0);
    }
    if (moveTime_ > 0)
    {
        move();
    }

    

    for (auto itr : skills)//skillアップデート
    {
        if(itr != nullptr)
            itr->Update();
    }
}

void Player::FaceMouseDirection()
{
    XMVECTOR target = getMouseTargetPos();
    if (isHit(target))
        FaceTargetDirection(target);
}

bool Player::isHit(const DirectX::XMVECTOR& target)
{
    return XMComparisonAnyFalse(XMVector3EqualR(target, NotHitV));
}

void Player::move()
{
    vMove_ = moveDirection_ * MOVE_VELOCITY * GetVelocity();
    if (moveTime_ >1)
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

void Player::RemoveCamp()
{
    RemoveColliderCamp((GameActor*)this, PLAYER);
}

//描画
void Player::ActorDraw()
{
    DrawCollision();
#ifdef _DEBUG
    if (Input::IsKey(DIK_Z))
    {
       
        Transform q;
        q.position_ = testQuad.position_;
        q.scale_.x = testQuad.width_;
        q.scale_.z = testQuad.length_;
        q.rotate_.y = testQuad.rotate_;
        Model::SetTransform(hQuad_,q );
        Model::Draw(hQuad_);
    }
    if (Input::IsKey(DIK_X))
    {
        Transform c;
        c.position_ = testCircle.position_;
        c.scale_.x = testCircle.radius_;
        c.scale_.z = testCircle.radius_;
        Model::SetTransform(hCircle_, c);
        Model::Draw(hCircle_);
    }
    if (Input::IsKey(DIK_C))
    {
        Transform s;
        s.position_ = testSector.position_;
        s.scale_.x = testSector.radius_;
        s.scale_.z = testSector.radius_;
        s.rotate_.y =180+ testSector.rotate_;
        Model::SetTransform(hSector_, s);
        Model::Draw(hSector_);
    }
#endif
    Model::SetTransform(hModel_,transform_);
    Model::Draw(hModel_);
    for (auto itr : skills)
    {
        if (itr != nullptr)
            itr->Draw();
    }
}

//開放
void Player::Release()
{
    for (auto itr : skills)
    {
        SAFE_DELETE(itr);
    }
}

void Player::ActivateSkill(const int number)
{

    if (!this->canMove())//自身が動けるか？
        return;
    if (number < 0 || number >= skills.size())//存在するスキル番号か？
        return;
    auto& skill = skills.at(number);
    if (!skill->CanUse())//対象のスキルは使用可能か？
        return;
    FaceMouseDirection();//マウス方向を向く
    moveTime_ = 0;//移動してたら止める
 
    skill->Activate(transform_);
}

XMVECTOR Player::getMouseTargetPos()
{
    XMFLOAT3 mouse = Input::GetMousePosition();
    XMMATRIX matInv = Camera::GetInverseMatrix();
    XMFLOAT3 front = mouse, back = mouse;
    back.z = 1.0f;
    XMVECTOR vFront = XMVector3TransformCoord(XMLoadFloat3(&front), matInv);
    XMVECTOR vBack = XMVector3TransformCoord(XMLoadFloat3(&back), matInv);
    XMVECTOR dir = XMVector3Normalize(vBack - vFront);
    XMVECTOR a = dir / XMVectorGetY(dir);//yが1になるように
    return Camera::GetPosition()- (a * XMVectorGetY(Camera::GetPosition()));//カメラ座標からdir方向に進んでyが0の時の座標を返す

}

void Player::calculateForMove(const XMVECTOR target_)
{
    //移動情報の計算
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);//Face〜にも同じ記述あるがこっちでも書くほうが楽

    float length =XMVectorGetX(XMVector3Length(target_ - vPos));
    moveTime_ = length / MOVE_VELOCITY -1;//-1と次の行がないと動きが微妙になる
     if (length < PLAYER_ROT_TH)return;
 
    FaceTargetDirection(target_);
    
}
void Player::FaceTargetDirection(const XMVECTOR& target_)
{
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    //移動方向を向く 
    moveDirection_ = XMVector3Normalize(target_ - vPos);
    XMFLOAT3 fdir;
    XMStoreFloat3(&fdir, moveDirection_);
    transform_.rotate_.y = XMConvertToDegrees((float)atan2(fdir.x, fdir.z));
    
}
bool Player::canMove()
{
    for (auto itr : skills)
    {
        if (itr != nullptr)
        {
            if (itr->CanMove() == false)
            return false;
        }
    }
    return true;
}