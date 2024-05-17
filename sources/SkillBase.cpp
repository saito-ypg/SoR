#include "SkillBase.h"
#include"CollisionManager.h"
#include"Player.h"
SkillBase::SkillBase() :defaultCastTime_(-1), defaultCoolDown_(-1), castTime_(0.0f), coolDown_(0.0f), stepindex(0), steptime(0.0f),isStepChanged(false),isInOperation_(false),pPlayer_(nullptr)
{
}
SkillBase::SkillBase(const float CT, const float CD, Player *const pPlayer, const std::string iconName) :SkillBase()
{
	defaultCastTime_ = CT;
	defaultCoolDown_ = CD;
	pPlayer_ = pPlayer;
	IconImageName = iconName;
	
}

SkillBase::~SkillBase()
{
	
}

void SkillBase::Update()
{
	if (castTime_ > 0)
		castTime_--;
	if (!isInOperation_) {
			if(coolDown_>0)
			coolDown_--;
		return;
	}

	action();
	steptime--;//���Ԑi�߂�
	if (steptime > 0) {
		isStepChanged = false;
		return;
	}
	stepindex++;//�X�e�b�v���ԏI������玟�̃X�e�b�v��
	isStepChanged = true;
	if (stepindex >= sequence.size())//�X�e�b�v�S���I�������
		isInOperation_ = false;//����I��点��
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
	ResetInheritedSkillMembers();
	isInOperation_ = true;
}

float SkillBase::getCdPercentage() const
{
	if (castTime_ > 0)
		return 1;
	return coolDown_ / defaultCoolDown_; 
}

float SkillBase::getCtPercentage() const
{
	return castTime_ / defaultCastTime_;	
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

void SkillBase::ResetInheritedSkillMembers()
{
}

