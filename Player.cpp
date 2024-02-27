#include "Player.h"
#include"Ground.h"
#include"Engine/Model.h"
#include"Engine/Input.h"
#include"Engine/Camera.h"
constexpr XMVECTOR NotHitV{ 9999,9999,9999,9999 };
constexpr float PLAYER_ROT_TH = 0.1f;//�ړ����ɉ�]���邩�ǂ����̋����̂������l
bool nearlyZero(float f) {//�ق�0�ł���Ƃ�����Ȃ�true�B
    return XMScalarNearEqual(f, 0.0f, 0.0001f);
}

//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameActor(parent, "Player"), hModel_(-1), moveTime_(0),isSkillBeingUsed(false)
{
    status_.maxHp_ = 200;
    status_.hp_ = status_.maxHp_;
    status_.hitCircleRange_ = 1.1f;
    moveDirection_ = XMVectorZero();
    vMove_ = XMVectorZero();
}

//�f�X�g���N�^
Player::~Player()
{
}       

//������
void Player::Initialize()
{
    hModel_ = Model::Load("Assets/Charactors/psample.fbx");
    assert(hModel_ >= 0);

    AddCamp();


    skills.at(0) = dynamic_cast<SkillBase*>(new testSkill);
}

//�X�V
void Player::ActorUpdate(const float& dt)
{
#ifdef _DEBUG
    {//���x�e�X�g�p   
        if (Input::IsKeyDown(DIK_1))
            pParent_->SetTimeScale(1.0f);
        if (Input::IsKeyDown(DIK_2))
            pParent_->SetTimeScale(2.0f);
        if (Input::IsKeyDown(DIK_0))
            pParent_->SetTimeScale(0.0f);
        if (nearlyZero(GetMyTimeScale()))//�X�V���x���قڂق�0�Ȃ炠�Ƃ̏�����΂�
            return;
    }
    int a=0;

    //�����蔻��e�X�g�p
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

    if (Input::IsMouseButton(1))//�ړ�
    {
        XMVECTOR target= getMouseTargetPos();
        if (isHit(target))
            calculateForMove(target);

    }
    //�e����
    if(Input::IsMouseButton(0))//�ʏ�U��
    {

    }
    else {
        if (!isSkillBeingUsed && Input::IsKeyDown(DIK_Q))
        {
            isSkillBeingUsed = canUseSkill(0);
        }
        if (isSkillBeingUsed&&Input::IsKeyUp(DIK_Q))
        {
            isSkillBeingUsed = false;
            ActivateSkill(0);
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
    vMove_ = moveDirection_ * MOVE_VELOCITY * GetTotalTimeScale();
    if (moveTime_ >1)
    {
        XMVECTOR vpos = XMLoadFloat3(&transform_.position_);
        vpos += vMove_;
        XMStoreFloat3(&transform_.position_, vpos);
        moveTime_ -= GetTotalTimeScale();
        isSkillBeingUsed = false;
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
#ifdef _DEBUG
    if (Input::IsKey(DIK_Z))
    {
       
        Transform q;
        q.position_ = testQuad.position_;
        q.scale_.x = testQuad.width_;
        q.scale_.z = testQuad.length_;
        q.rotate_.y = testQuad.rotate_;
        Model::SetTransform(area(QUAD), q);
        Model::Draw(area(QUAD));
    }
    if (Input::IsKey(DIK_X))
    {
        Transform c;
        c.position_ = testCircle.position_;
        c.scale_.x = testCircle.radius_;
        c.scale_.z = testCircle.radius_;
        Model::SetTransform(area(CIRCLE), c);
        Model::Draw(area(CIRCLE));
    }
    if (Input::IsKey(DIK_C))
    {
        Transform s;
        s.position_ = testSector.position_;
        s.scale_.x = testSector.radius_;
        s.scale_.z = testSector.radius_;
        s.rotate_.y =180+ testSector.rotate_;
        Model::SetTransform(area(SECTOR), s);
        Model::Draw(area(SECTOR));
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

//�J��
void Player::Release()
{
    for (auto itr : skills)
    {
        SAFE_DELETE(itr);
    }
}

bool Player::canUseSkill(int number)
{
    if (!this->canMove())//���g�������邩�H
        return false;
    if (number < 0 || number >= skills.size())//���݂���X�L���ԍ����H
        return false;
    return skills.at(number)->CanUse();//�Ώۂ̃X�L���͎g�p�\���H
    
}

void Player::ActivateSkill(const int number)
{
    if (!canUseSkill(number))
        return;
    FaceMouseDirection();//�}�E�X����������
    moveTime_ = 0;//�ړ����Ă���~�߂�
 
    skills.at(number)->Activate(transform_);
}

void Player::previewSkill(int number)
{
    if(!canUseSkill(number))
        return;//�����܂ł͔����ƈꏏ



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
    return Camera::GetPosition()- (a * XMVectorGetY(Camera::GetPosition()));//�J�������W����dir�����ɐi���y��0�̎��̍��W��Ԃ�

}

void Player::calculateForMove(const XMVECTOR target_)
{
    //�ړ����̌v�Z
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);//Face�`�ɂ������L�q���邪�������ł������ق����y

    float length =XMVectorGetX(XMVector3Length(target_ - vPos));
    moveTime_ = length / MOVE_VELOCITY -1;//-1�Ǝ��̍s���Ȃ��Ɠ����������ɂȂ�
     if (length < PLAYER_ROT_TH)return;
 
    FaceTargetDirection(target_);
    
}
void Player::FaceTargetDirection(const XMVECTOR& target_)
{
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    //�ړ����������� 
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