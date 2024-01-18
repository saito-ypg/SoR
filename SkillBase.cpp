#include "SkillBase.h"


SkillBase::SkillBase() :defaultCastTime_(-1), defaultCoolDown_(-1), castTime_(0.0f), coolDown_(0.0f),stepindex(0),steptime(0.0f),isInOperation(false)
{
}
SkillBase::SkillBase(float CT, float CD) :SkillBase()
{
	defaultCastTime_ = frame(CT);
	defaultCoolDown_ = frame(CD);
}

void SkillBase::Update()
{//��
	if (castTime_ >= 0)
		castTime_--;
	else
		coolDown_--;

	if (isInOperation)
	{
		action();//�����ōX�V�ŗǂ��H
		steptime--;//���Ԑi�߂�
		if (steptime <= 0)
		{
			stepindex++;//�X�e�b�v�i�߂�
			if (stepindex >= sequence.size())//�X�e�b�v�S���I�������
				isInOperation = false;//����I��点��
		}
	}
}

void SkillBase::Activate(Transform tr)
{
	if (coolDown_ > 0)
		return;
	//�����ł����ԂȂ�
	transform_ = tr;
	isInOperation = true;
	this->action();
}

