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
{//仮
	if (castTime_ >= 0)
		castTime_--;
	else
		coolDown_--;

	if (isInOperation)
	{
		action();//ここで更新で良い？
		steptime--;//時間進める
		if (steptime <= 0)
		{
			stepindex++;//ステップ進める
			if (stepindex >= sequence.size())//ステップ全部終わったら
				isInOperation = false;//動作終わらせる
		}
	}
}

void SkillBase::Activate(Transform tr)
{
	if (coolDown_ > 0)
		return;
	//発動できる状態なら
	transform_ = tr;
	isInOperation = true;
	this->action();
}

