#pragma once
#include<vector>
#include"AttackRange.h"
#include"DamageData.h"
//�v���C���[�p�X�L���̌�
enum sequenceStep
{
	

};
struct flags//�K�v�ɉ����ăr�b�g�t���O
{

};
class SkillBase
{
public:
	struct DamageData damageData_;

	const float defaultCastTime_;//�X�L���g�p�ɂ����鑍����
	float castTime_;//�X�L���g�p����
	const float defaultCoolDown_;//�X�L���̍Ďg�p�܂ł̎���
	float coolDown_;//�N�[���^�C���c�莞��

	//�r�����[�h�̎���start�݂����ɃV�[�P���X���ꂽ���B����ɉ����čU���o�����蓮��������
	std::vector<float>sequence;

	SkillBase(float CT,float CD):defaultCastTime_(CT),defaultCoolDown_(CD){}
	virtual void update();//�X�L�����ԁACD���ԓ��̍X�V�Ǝ����I�Ȕ���
	virtual void action() = 0;//�X�L�������������̓����Ƃ�������

};

