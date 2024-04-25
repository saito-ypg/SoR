#include "SkillBase.h"
#include"CollisionManager.h"
#include"Player.h"
SkillBase::SkillBase() :defaultCastTime_(-1), defaultCoolDown_(-1), castTime_(0.0f), coolDown_(0.0f), stepindex(0), steptime(0.0f), isInOperation(false),pPlayer_(nullptr)
{
}
SkillBase::SkillBase(float CT, float CD, Player* pPlayer) :SkillBase()
{
	defaultCastTime_ = frame(CT);
	defaultCoolDown_ = frame(CD);
	pPlayer_ = pPlayer;
	
}

SkillBase::~SkillBase()
{
	
}

void SkillBase::Update()
{
	if (!isInOperation) {
		if (castTime_ > 0)
			castTime_--;
		else
			if(coolDown_>0)
			coolDown_--;
		return;
	}

	action();
	steptime--;//時間進める
	if (steptime > 0)
		return;

	stepindex++;//ステップ進める
	if (stepindex >= sequence.size())//ステップ全部終わったら
		isInOperation = false;//動作終わらせる
	else
		steptime = sequence.at(stepindex);

}

void SkillBase::Activate()
{
	beginTransform_ = *pPlayer_->GetTransformRef();
	castTime_ = defaultCastTime_;
	coolDown_ = defaultCoolDown_;
	stepindex = 0;
	steptime = sequence.front();
	isInOperation = true;
}

void SkillBase::SwitchActionByStep()
{
	switch (stepindex)
	{
	case INVOKED:
		invokedStep();
		break;
	case START_ATTACK:
		startStep();
		break;
	case END_ATTACK:
		endStep();
		break;
	}
}

void SkillBase::RegisterHitRange(AttackRangeCircle c, DamageData &dmg)
{
	CollisionManager::RegisterHitRange(PLAYER, c,dmg);
}

void SkillBase::RegisterHitRange(AttackRangeQuad q, DamageData &dmg)
{
	CollisionManager::RegisterHitRange(PLAYER, q, dmg);
}

void SkillBase::RegisterHitRange(AttackRangeCirculerSector s, DamageData &dmg)
{
	CollisionManager::RegisterHitRange(PLAYER, s, dmg);
}

Transform SkillBase::GetPlayerTransform()
{
	return *(pPlayer_->GetTransformRef());
}

