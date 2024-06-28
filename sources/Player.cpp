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
    constexpr float PLAYER_ROT_TH = 0.1f;//�ړ����ɉ�]���邩�ǂ����̋����̂������l

    const std::map<int, int> skillkeysmap{//�X�L���ԍ�������̓L�[�ɕϊ�
        {0,DIK_Q },
        {1,DIK_W},
        {2,DIK_E},
        {3,DIK_R},
    };
    bool nearlyZero(float f) {//�ق�0�ł���Ƃ�����Ȃ�true�B
    return XMScalarNearEqual(f, 0.0f, 0.0001f);
}
}


//�R���X�g���N�^
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

//�f�X�g���N�^
Player::~Player()
{
}       

//������
void Player::Initialize()
{
    hBody_ = Model::Load("Charactors/psample.fbx");
    assert(hBody_ >= 0);

    AddCamp();

    AttachSkill<testSkill>(0);
    AttachSkill<ChargeSkill>(1);
}

//�X�V
void Player::ActorUpdate(const float& dt)
{
#ifdef _DEBUG
    {//���x�e�X�g�p   
        if (Input::IsKeyDown(DIK_1))
            GetParent()->SetTimeScale(1.0f);
        if (Input::IsKeyDown(DIK_2))
            GetParent()->SetTimeScale(2.0f);
        if (Input::IsKeyDown(DIK_0))
            GetParent()->SetTimeScale(0.0f);
        if (nearlyZero(GetMyTimeScale()))//�X�V���x���قڂق�0�Ȃ炠�Ƃ̏�����΂�
            return;
    }
#endif
    if (Input::IsKey(DIK_A))
        status_.hp_--;
    
    MoveInput();
    //�e����
    if(Input::IsMouseButton(0))//�ʏ�U��
    {

    }
    else {//�e��X�L��
        for (int i = 0; i < skillsNum; i++) {
            if(!skills.at(i))//�X�L���A�^�b�`�ł��ĂȂ�������
            {
                continue;
            }
            else if (usingSkillIndex==UNUSED && Input::IsKeyDown(skillkeysmap.at(i)))
            {//�X�L���͈͕\���̂��߂�index�w��
                if (canUseSkill(i)) {
                    usingSkillIndex = i;
                }
            }
            else if (usingSkillIndex==i && Input::IsKeyUp(skillkeysmap.at(i)))
            {//�����O�L�����Z������ĂȂ���΂����Ŕ���
                ActivateSkill(i);
                usingSkillIndex = UNUSED;
            }
        }
    }
    if (moveTime_ > 0)
    {
        move();
    }

    

    for (auto itr : skills)//skill�A�b�v�f�[�g
    {
        if(itr != nullptr)
            itr->Update();
    }
}

void Player::MoveInput()
{
    if (Input::IsMouseButton(1))//�ړ���w��
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

//�`��
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

//�J��
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
    if (this->isDuringSkill())//���łɃX�L�����쒆�Ȃ炘
        return false;
    if (number < 0 || number >= skills.size())//���݂��Ȃ��X�L���ԍ���
        return false;
    return skills.at(number)->CanUse();//�Ώۂ̃X�L���͎g�p�\����Ԃ�
    
}

void Player::ActivateSkill(const int number)
{
    if (!canUseSkill(number))
        return;
    FaceMouseDirection();//�}�E�X����������
    moveTime_ = 0;//�ړ����Ă���~�߂�
 
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
    XMVECTOR a = dir / XMVectorGetY(dir);//y��1�ɂȂ�悤��
    auto temp = Camera::GetPosition();
    XMVECTOR campos = XMLoadFloat3(&temp);
    return campos- (a * XMVectorGetY(campos));//�J�������W����dir�����ɐi���y��0�̎��̍��W��Ԃ�

}

void Player::calculateForMove(const XMVECTOR target_)
{
    //�ړ����̌v�Z
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);//Face�`�ɂ������L�q���邪�������ł������ق����y

    float length =XMVectorGetX(XMVector3Length(target_ - vPos));
    moveTime_ = length / MOVE_VELOCITY -1;//-1�Ǝ��̍s�ŏ����݂ɍr�Ԃ�̑΍�
     if (length < PLAYER_ROT_TH)return;
 
    float deg= GetTargetDirection(target_);
    transform_.rotate_.y = deg;
    XMVECTOR forward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
    moveDirection_= XMVector3TransformCoord(forward, XMMatrixRotationY(XMConvertToRadians(deg)));

    
}
float Player::GetTargetDirection(const XMVECTOR& target_) const
{
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    //�ړ����������� 
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
                return true;//�����遨�X�L�����[�V�������łȂ�
        }
    }
    return false;
}

void Player::dyingProcess()
{
    ModeratorSequence* ms = (ModeratorSequence*)FindObject("ModeratorSequence");
    ms->SetGameOver();
}
