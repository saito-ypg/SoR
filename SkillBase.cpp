#include "SkillBase.h"


SkillBase::SkillBase() :defaultCastTime_(-1), defaultCoolDown_(-1), castTime_(0.0f), coolDown_(0.0f)
{
}
SkillBase::SkillBase(float CT, float CD) :SkillBase()
{
	defaultCastTime_ = CT;
	defaultCoolDown_ = CD;
}

void SkillBase::Update()
{//仮
	if (castTime_ > 0)
		castTime_--;
	else
		coolDown_--;
}

void SkillBase::Activate(Transform tr)
{
	if (coolDown_ > 0)
		return;
	//発動できる状態なら
	transform_ = tr;
	this->action();
}

