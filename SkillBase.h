#pragma once
#include<vector>
#include"AttackRange.h"
#include"DamageData.h"
#include"Engine/Transform.h"


//�v���C���[�p�X�L���̊�b�N���X�B�e��p�����[�^�[�͈�U�b�P�ʂŎw��
class SkillBase
{
private:

protected:
	Transform transform_;//�X�L�������ʒu
	//float steptime;//�e�X�e�b�v
	std::vector<float>sequence;//�e�X�e�b�v�ɂ����鎞�ԓ���Ƃ�
	//�r�����[�h�̎���start�݂����ɃV�[�P���X���ꂽ���B����ɉ����čU���o�����蓮��������

	virtual void action() = 0;//�X�L�������������̓���Ə����̎���
	float defaultCastTime_;//�X�L���g�p�ɂ����鑍����
	float castTime_;//�X�L���g�p�ɂ����蓮���Ȃ�����
	float defaultCoolDown_;//�X�L���̍Ďg�p�܂ł̎���
	float coolDown_;//�N�[���^�C���c�莞��

public:
	struct DamageData damageData_;

	SkillBase();
	SkillBase(float CT, float CD);

	virtual void Update();//�X�L�����ԁACD���ԓ��̍X�V�Ǝ����I�Ȕ���
	void Activate(Transform tr);//�X�L�������i�{�^���������Ƃ��j
	virtual void Draw()=0;//�X�L���G�t�F�N�g�ȂǕ`��

};

