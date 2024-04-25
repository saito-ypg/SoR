#pragma once
//#include "Engine/GameObject.h"
#include"GameActor.h"
#include"PlayerSkillsInclude.h"
constexpr float MOVE_VELOCITY = 10.0f /60;
class Player : public GameActor
{
private:
    //Pimpl�Ƃ������T�O�A�悳����
    int hModel_;
    //�ړ������̒P�ʃx�N�g�����i�[
    XMVECTOR moveDirection_;
    //�ړ��x�N�g��
    XMVECTOR vMove_;
    //�ړ��ɂ�����t���[����������B�ړ����f������0��
    float moveTime_;

 //�X�L���o�^
    static constexpr int skillsNum = 4;
    std::vector<SkillBase*>skills{ static_cast<size_t>(skillsNum)};   
    bool canUseSkill(int number);
    void ActivateSkill(int number);
    
    template<class skill>
    void AttachSkill(int index) {//�X�L�����v���C���[�ɕR�Â���
        assert(!skills.at(index));//at�Ŕ͈͊O�͎̂Ăo�^�̔ԍ��ɂ��Ԃ肪�Ȃ��悤�ɂ���(����Ă���=�C���X�^���X������Ă���)
        skills.at(index) = dynamic_cast<SkillBase*>(new skill(this));
    }

    //���݂̃}�E�X���W�����[���h���W�ɕϊ����ĕԂ�
    XMVECTOR getMouseTargetPos();
    //target�̕����ɉ�]
    float GetTargetDirection(const XMVECTOR& target_);
    //�ړ�+��]
    void calculateForMove(const XMVECTOR target_);
    
    void FaceMouseDirection();

    void move();
    
    void AddCamp()override;
    void RemoveCamp()override;
#ifdef _DEBUG
    //test
    AttackRangeQuad testQuad;
    AttackRangeCircle testCircle;
    AttackRangeCirculerSector testSector;
#endif // _DEBUG

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



   

    bool isIntersectGround(const DirectX::XMVECTOR& target);

    //�`��
    void ActorDraw() override;

    //�J��
    void Release() override;

};