#include "SkillBase.h"


SkillBase::SkillBase() :defaultCastTime_(-1), defaultCoolDown_(-1), castTime_(0.0f), coolDown_(0.0f), stepindex(0), steptime(0.0f), isInOperation(false)
{
}
SkillBase::SkillBase(float CT, float CD) :SkillBase()
{
	defaultCastTime_ = frame(CT);
	defaultCoolDown_ = frame(CD);
}

void SkillBase::Update()
{//��
	if (!isInOperation) {
		if (castTime_ > 0)
			castTime_--;
		else
			coolDown_--;
		return;
	}

	action();//�����ōX�V�ŗǂ��H
	steptime--;//���Ԑi�߂�
	if (steptime > 0)
		return;

	stepindex++;//�X�e�b�v�i�߂�
	if (stepindex >= sequence.size())//�X�e�b�v�S���I�������
		isInOperation = false;//����I��点��
	else
		steptime = sequence.at(stepindex);

}

void SkillBase::Activate(Transform tr)
{

	//�����ł����ԂȂ�
	transform_ = tr;
	castTime_ = defaultCastTime_;
	coolDown_ = defaultCoolDown_;
	stepindex = 0;
	steptime = sequence.front();
	isInOperation = true;
}

