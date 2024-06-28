#include<algorithm>
#include "Player.h"
#include"Ground.h"
#include"../Engine/Model.h"
#include"../Engine/Input.h"
#include"../Engine/Camera.h"
#include"../Engine/Global.h"
#include"ModeratorSequence.h"
namespace {
    constexpr XMVECTOR NotHitV{ 9999,9999,9999,9999 };
    constexpr float PLAYER_ROT_TH = 0.1f;//移動時に回転するかどうかの距離のしきい値

    const std::map<int, int> skillkeysmap{//スキル番号から入力キーに変換
        {0,DIK_Q },
        {1,DIK_W},
        {2,DIK_E},
        {3,DIK_R},
    };
    bool nearlyZero(float f) {//ほぼ0であるといえるならtrue。
    return XMScalarNearEqual(f, 0.0f, 0.0001f);
}
}


//コンストラクタ
Player::Player(GameObject* parent)
    :GameActor(parent, "Player"), moveTime_(0)
{
    status_ = ActorInfo(200, 1.1f);

    moveDirection_ = XMVectorZero();
    vMove_ = XMVectorZero();
    for (auto i : skills)
    {
        i = nullptr;
    }

}

//デストラクタ
Player::~Player()
{
}       

//初期化
void Player::Initialize()
{
    hBody_ = Model::Load("Charactors/psample.fbx");
    assert(hBody_ >= 0);

    AddCamp();

    AttachSkill<testSkill>(0);
    AttachSkill<ChargeSkill>(1);
}

//更新
void Player::ActorUpdate(const float& dt)
{
#ifdef _DEBUG
    {//速度テスト用   
        if (Input::IsKeyDown(DIK_1))
            GetParent()->SetTimeScale(1.0f);
        if (Input::IsKeyDown(DIK_2))
            GetParent()->SetTimeScale(2.0f);
        if (Input::IsKeyDown(DIK_0))
            GetParent()->SetTimeScale(0.0f);
        if (nearlyZero(GetMyTimeScale()))//更新速度がほぼほぼ0ならあとの処理飛ばす
            return;
    }
#endif
    if (Input::IsKey(DIK_A))
        status_.hp_--;
    
    MoveInput();
    //各入力
    if(Input::IsMouseButton(0))//通常攻撃
    {

    }
    else {//各種スキル
        for (int i = 0; i < skillsNum; i++) {
            if(!skills.at(i))//スキルアタッチできてなかったら
            {
                continue;
            }
            else if (usingSkillIndex==UNUSED && Input::IsKeyDown(skillkeysmap.at(i)))
            {//スキル範囲表示のためのindex指定
                if (canUseSkill(i)) {
                    usingSkillIndex = i;
                }
            }
            else if (usingSkillIndex==i && Input::IsKeyUp(skillkeysmap.at(i)))
            {//発動前キャンセルされてなければここで発動
                ActivateSkill(i);
                usingSkillIndex = UNUSED;
            }
        }
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

void Player::MoveInput()
{
    if (Input::IsMouseButton(1))//移動先指定
    {
        if (isDuringSkill())
            return;
        XMVECTOR target = getMouseTargetPos();
        if (isIntersectGround(target)) {
            calculateForMove(target);
            if (Input::IsMouseButtonDown(1))usingSkillIndex = UNUSED;
        }
    }
}

void Player::FaceMouseDirection()
{
    XMVECTOR target = getMouseTargetPos();
    if (isIntersectGround(target)) {
        float deg = GetTargetDirection(target);
        transform_.rotate_.y = deg;
    }
}

bool Player::isIntersectGround(const DirectX::XMVECTOR& target)
{
    return XMComparisonAnyFalse(XMVector3EqualR(target, NotHitV));
}

void Player::move()
{
    vMove_ = moveDirection_ * MOVE_VELOCITY * GetTotalTimeScale();
    if (moveTime_ >1)
    {
        XMVECTOR vpos = XMLoadFloat3(&transform_.position_);
        vpos += vMove_;
        XMStoreFloat3(&transform_.position_, vpos);
        moveTime_ -= GetTotalTimeScale();

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
    DrawBody();
    if (usingSkillIndex != UNUSED) {
        skills.at(usingSkillIndex)->DrawRangeDisplay(GetTargetDirection(getMouseTargetPos()));
    }
    for (auto itr : skills)
    {
        if (itr != nullptr)
        {
            itr->Draw();
            
        }
    }
}

//開放
void Player::ActorRelease()
{
    for (auto itr : skills)
    {
        SAFE_DELETE(itr);
    }
}

std::vector<SkillBase*> Player::getSkills() const
{
    std::vector<SkillBase*>retVec(skills.begin(), skills.end());
    return retVec;
}


bool Player::canUseSkill(int number)
{
    if (this->isDuringSkill())//すでにスキル動作中ならｘ
        return false;
    if (number < 0 || number >= skills.size())//存在しないスキル番号ｘ
        return false;
    return skills.at(number)->CanUse();//対象のスキルは使用可能かを返す
    
}

void Player::ActivateSkill(const int number)
{
    if (!canUseSkill(number))
        return;
    FaceMouseDirection();//マウス方向を向く
    moveTime_ = 0;//移動してたら止める
 
    skills.at(number)->Activate();
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
    auto temp = Camera::GetPosition();
    XMVECTOR campos = XMLoadFloat3(&temp);
    return campos- (a * XMVectorGetY(campos));//カメラ座標からdir方向に進んでyが0の時の座標を返す

}

void Player::calculateForMove(const XMVECTOR target_)
{
    //移動情報の計算
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);//Face～にも同じ記述あるがこっちでも書くほうが楽

    float length =XMVectorGetX(XMVector3Length(target_ - vPos));
    moveTime_ = length / MOVE_VELOCITY -1;//-1と次の行で小刻みに荒ぶるの対策
     if (length < PLAYER_ROT_TH)return;
 
    float deg= GetTargetDirection(target_);
    transform_.rotate_.y = deg;
    XMVECTOR forward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
    moveDirection_= XMVector3TransformCoord(forward, XMMatrixRotationY(XMConvertToRadians(deg)));

    
}
float Player::GetTargetDirection(const XMVECTOR& target_) const
{
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    //移動方向を向く 
    XMVECTOR direction = XMVector3Normalize(target_ - vPos);
    XMFLOAT3 fdir;
    XMStoreFloat3(&fdir, direction);
    return XMConvertToDegrees((float)atan2(fdir.x, fdir.z));
    
}
bool Player::isDuringSkill()
{
    for (auto itr : skills)
    {
        if (itr != nullptr)
        {
            if (!itr->CanMove())
                return true;//動ける→スキルモーション中でない
        }
    }
    return false;
}

void Player::dyingProcess()
{
    ModeratorSequence* ms = (ModeratorSequence*)FindObject("ModeratorSequence");
    ms->SetGameOver();
}
