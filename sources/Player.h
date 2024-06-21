#pragma once
//#include "Engine/GameObject.h"
#include"GameActor.h"
#include"PlayerSkillsInclude.h"

class Player : public GameActor
{   
public:
    static constexpr int skillsNum = 4;
    static constexpr int UNUSED = -1;//�X�L�����������ĂȂ��Ƃ�
private:
    static constexpr float MOVE_VELOCITY = 10.0f /60;
    

    int usingSkillIndex = UNUSED;//�g�p���X�L���ԍ��A�Ȃ�������UNUSED(=-1);
    //�ړ������̒P�ʃx�N�g�����i�[
    XMVECTOR moveDirection_;
    //�ړ��x�N�g��
    XMVECTOR vMove_;
    //�ړ��ɂ�����t���[����������B�ړ����f������0��
    float moveTime_;

 //�X�L���o�^
 
    std::vector<SkillBase*>skills{ static_cast<size_t>(skillsNum)};   
    bool canUseSkill(int number);
    void ActivateSkill(int number);
    
    template<class skill, typename = std::enable_if_t < std::is_base_of_v <SkillBase, skill>>>
    void AttachSkill(int index) {//�X�L�����v���C���[�ɕR�Â���
        assert(!skills.at(index));//at�Ŕ͈͊O�͎̂Ăo�^�̔ԍ��ɂ��Ԃ肪�Ȃ��悤�ɂ���(����Ă���=�C���X�^���X������Ă���)
        skills.at(index) = dynamic_cast<SkillBase*>(new skill(this));
    }

    //���݂̃}�E�X���W�����[���h���W�ɕϊ����ĕԂ�
    XMVECTOR getMouseTargetPos();
    //target�̕����ɉ�]
    float GetTargetDirection(const XMVECTOR& target_) const;
    //�ړ�+��]
    void calculateForMove(const XMVECTOR target_);
    
    void FaceMouseDirection();

    void move();
    
    void AddCamp()override;
    void RemoveCamp()override;

    bool isDuringSkill();
    void MoveInput();
protected:
    void dyingProcess()override;
public:
    //�R���X�g���N�^
    Player(GameObject* parent);

    //�f�X�g���N�^
    virtual ~Player();

    //������
    void Initialize() override;

    //�ʍX�V
    void ActorUpdate(const float& dt) override;

    //�v����
    bool isIntersectGround(const DirectX::XMVECTOR& target);
    
    //�`��
    void ActorDraw() override;

    //�J��
    void Release() override;

   
    //UI�p�B�N�[���_�E�������Ƃ��ʂł�����肱�����̂ق��������H
    std::vector<SkillBase*>getSkills() const;
    int getUsingSkill() const { return usingSkillIndex; }


};