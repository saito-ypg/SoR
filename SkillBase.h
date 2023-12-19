#pragma once
#include "AttackRange.h"
#include"DamageData.h"
//�v���C���[�p�X�L���̌�
class SkillBase
{
public:
	struct DamageData damageData_;

	const float defaultCastTime_;//�X�L���g�p�ɂ����鑍����
	float castTime_;//�X�L���g�p����
	const float defaultCoolDown_;//�X�L���̍Ďg�p�܂ł̎���
	float coolDown_;//�N�[���^�C���c�莞��

	SkillBase(float CT,float CD):defaultCastTime_(CT),defaultCoolDown_(CD){}
	virtual void action() = 0;//�X�L�������������̓����Ƃ�������
	void update();

};

