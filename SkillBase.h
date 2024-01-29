#pragma once
#include<vector>
#include"AttackRange.h"
#include"DamageData.h"
#include"Engine/Transform.h"


//�v���C���[�p�X�L���̊�b�N���X�B�e��p�����[�^�[�͈�U�t���[���P�ʂŎw��B
//�e�h�����action�̒���step���ɏ����ς���(switch-case)�B�K�v�Ȃ��p��enum���B
class SkillBase
{
private:

protected:
	Transform transform_;//�X�L�������ʒu
	std::vector<float>sequence{0};//�U���ɂ�����e�X�e�b�v�̎���
	float steptime;//�e�X�e�b�v�Ō��݂ǂꂾ���̎��Ԃ�������
	int stepindex;//���݉��X�e�b�v�ڂ��Bsequence

	enum base_steps {//��{�I�ȃX�e�b�v
		INVOKED = 0,//��������A�\������Ƃ�
		START_ATTACK,//�U������J�n
		END_ATTACK,//�U������I��
	};
	
	virtual void action() = 0;//�X�L���������̓���Ə����̎���
	float defaultCastTime_;//�X�L���g�p�㓮���Ȃ�������
	float castTime_;//������悤�ɂȂ�܂ł̎c�莞��
	float defaultCoolDown_;//�X�L���̍Ďg�p�܂ł̎���
	float coolDown_;//�N�[���^�C���c�莞��
	bool isInOperation;
	
	struct attack {
		AttackRangeBase range;
		float Duration;
		DamageData damageData_;
	};
public:
	

	SkillBase();
	SkillBase(float CT, float CD);//�b�P�ʎw��

	virtual void Update();//�X�L�����ԁACD���ԓ��̍X�V�B�����I�Ȕ���?
	void Activate(Transform tr);//�X�L�������i�{�^���������Ƃ��j
	virtual void Draw()=0;//�X�L���G�t�F�N�g�ȂǕ`��
	bool CanUse() { return coolDown_ <= 0; }
	bool CanMove() { return castTime_ <= 0;  }

	static float Sec(float flames) {return flames / 60;}//�t���[������b�ɕϊ�
	static float frame(float seconds) { return seconds * 60; }//�b����t���[���ɕϊ�
};

