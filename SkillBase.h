#pragma once
#include<vector>
#include"AttackRange.h"
#include"DamageData.h"



//�v���C���[�p�X�L���̌�
class SkillBase
{
private:

protected:
	
	//float steptime;//�e�X�e�b�v
	//std::vector<float>sequence;//�e�X�e�b�v�ɂ����鎞�ԓ���Ƃ�

	//�r�����[�h�̎���start�݂����ɃV�[�P���X���ꂽ���B����ɉ����čU���o�����蓮��������
	virtual void action() = 0;//�X�L�������������̓���Ə����̎���
public:
	struct DamageData damageData_;

	float defaultCastTime_;//�X�L���g�p�ɂ����鑍����
	float castTime_;//�X�L���g�p�ɂ����鎞��
	float defaultCoolDown_;//�X�L���̍Ďg�p�܂ł̎���
	float coolDown_;//�N�[���^�C���c�莞��

	SkillBase();
	SkillBase(float CT, float CD);

	virtual void Update();//�X�L�����ԁACD���ԓ��̍X�V�Ǝ����I�Ȕ���
	void Activate();//�X�L�������i�{�^���������Ƃ��j


};

