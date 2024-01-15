#pragma once
#include<vector>
#include"AttackRange.h"
#include"DamageData.h"
#include"Engine/Transform.h"


//�v���C���[�p�X�L���̊�b�N���X�B�e��p�����[�^�[�͈�U�t���[���P�ʂŎw��B
class SkillBase
{
private:

protected:
	Transform transform_;//�X�L�������ʒu

	std::vector<float>sequence{0};//�U���ɂ�����e�X�e�b�v�̎���
	float steptime;//�e�X�e�b�v�Ō��݂ǂꂾ���̎��Ԃ�������
	int stepindex;//���݉��X�e�b�v�ڂ��Bsequence


	virtual void action() = 0;//�X�L�������������̓���Ə����̎���
	float defaultCastTime_;//�X�L���g�p�ɂ����鑍����
	float castTime_;//�X�L���g�p�ɂ����蓮���Ȃ�����
	float defaultCoolDown_;//�X�L���̍Ďg�p�܂ł̎���
	float coolDown_;//�N�[���^�C���c�莞��

public:
	struct DamageData damageData_;
	bool isInOperation;
	SkillBase();
	SkillBase(float CT, float CD);//�b�P�ʎw��

	virtual void Update();//�X�L�����ԁACD���ԓ��̍X�V�Ǝ����I�Ȕ���
	void Activate(Transform tr);//�X�L�������i�{�^���������Ƃ��j
	virtual void Draw()=0;//�X�L���G�t�F�N�g�ȂǕ`��
	bool CamMove() { return castTime_ < 0;  }

	static float Sec(float flames) {return flames / 60;}//�t���[������b���o��
	static float flame(float seconds) { return seconds * 60; }//�b����t���[�����o��
};

