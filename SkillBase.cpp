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
{//仮
	if (!isInOperation) {
		if (castTime_ > 0)
			castTime_--;
		else
			coolDown_--;
		return;
	}

	action();//ここで更新で良い？
	steptime--;//時間進める
	if (steptime > 0)
		return;

	stepindex++;//ステップ進める
	if (stepindex >= sequence.size())//ステップ全部終わったら
		isInOperation = false;//動作終わらせる
	else
		steptime = sequence.at(stepindex);

}

void SkillBase::Activate(Transform tr)
{

	//発動できる状態なら
	transform_ = tr;
	castTime_ = defaultCastTime_;
	coolDown_ = defaultCoolDown_;
	stepindex = 0;
	steptime = sequence.front();
	isInOperation = true;
}

