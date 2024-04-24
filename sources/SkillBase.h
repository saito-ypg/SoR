#pragma once
#include<vector>
#include"../Engine/Transform.h"
#include"areamodels.h"
#include"AttackRange.h"
#include"DamageData.h"

using namespace AreaModels;
class Player;
///�v���C���[�p�X�L���̊�b�N���X�B�e��p�����[�^�[�͈�U�t���[���P�ʂŎw��B
///�e�h�����action�̒���step���ɏ����ς���(switch-case)�B�K�v�Ȃ��p��enum���B
/// �R���X�g���N�^��CastTime�ECoolDown�̎w��
/// sequence�̃t���[�����w����s������
class SkillBase
{
private:
	SkillBase();//�h���悩��͈����t���̂��̂��ĂԁB����͊�b�I�ȏ������݂̂��s��
protected:
	Transform transform_;//�X�L���������̃g�����X�t�H�[�����i�[���Ă����B�������ȊO�͊�{������Ȃ��B�v���C���[�̂��̂Ƃ͋�ʂ���
	std::vector<float>sequence{0};//�U���ɂ�����e�X�e�b�v�t���[����
	float steptime;//�e�X�e�b�v�Ō��݂ǂꂾ���̎��Ԃ�������
	int stepindex;//���݉��X�e�b�v�ڂ��Bsequence

	enum base_steps {//��{�I�ȃX�e�b�v
		INVOKED = 0,//��������A�\������Ƃ�
		START_ATTACK,//�U������J�n
		END_ATTACK,//�U������I��
	};
	
	virtual void action() = 0;//�X�L���������̓���Ə����̎���
	void SwitchActionByStep();//�e�X�e�b�v�̏������Ăѕ�����
	virtual void invokedStep()=0;//�U���O�X�e�b�v�̎���
	virtual void startStep()=0;//�U���J�n�X�e�b�v�̎���
	virtual void endStep()=0;//�U���I����X�e�b�v�̎���

	float defaultCastTime_;//�X�L���g�p�㓮���Ȃ�������
	float castTime_;//������悤�ɂȂ�܂ł̎c�莞��
	float defaultCoolDown_;//�X�L���̍Ďg�p�܂ł̎���
	float coolDown_;//�N�[���^�C���c�莞��
	bool isInOperation;//�X�L���g�p����
	Player* pPlayer_;//�v���C���[�̃X�e�[�^�X�ς����肵�������Ɏg���|�C���^
	void RegisterHitRange(AttackRangeCircle c,DamageData &dmg);
	void RegisterHitRange(AttackRangeQuad q, DamageData &dmg);
	void RegisterHitRange(AttackRangeCirculerSector s, DamageData &dmg);
	Transform GetPlayerTransform();
public:
	


	SkillBase(float CT, float CD, Player* pPlayer);//�b���w�聨�t���[���ɕϊ����Ă�B�h���悩�炱����Ă�

	virtual ~SkillBase();
	virtual void Update();//�X�L�����ԁACD���ԓ��̍X�V�B�����I�Ȕ���?
	void Activate();//�X�L�������i�{�^���������Ƃ��j
	virtual void Draw()=0;//�X�L���G�t�F�N�g�ȂǕ`��
	virtual void DrawRangeDisplay(float deg)=0;//�U���O�ɔ͈͂�\������ ����->�p�x
	virtual void Release() = 0;
	bool CanUse() const{ return coolDown_ <= 0; }
	bool CanMove() const{ 
		return castTime_ <= 0; 
	}

	static float Sec(float flames) {return flames / 60;}//�t���[������b�ɕϊ�
	static float frame(float seconds) { return seconds * 60; }//�b����t���[���ɕϊ�
};

