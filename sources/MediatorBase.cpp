#include "MediatorBase.h"
#include"EnemyBase.h"
#include"IdleState.h"
MediatorBase::MediatorBase(EnemyBase& enemy) :base_(enemy)
{
	curState_ = std::make_unique<IdleState>(enemy);
}

MediatorBase::~MediatorBase()
{
}

void MediatorBase::Update(const float& dt)
{
	curState_->Update(dt);
	if (curState_->CanTransitionOut()) {//‚±‚±‚ÌğŒAtrue‚È‚ç–ˆ‰ñ”»’f“ü‚Á‚¿‚á‚¤‚©‚çˆê’èŠÔ‹ó‚¯‚½‚Ù‚¤‚ª‚¢‚¢‚©‚àH
		DetermineNextState();
	}
}

const std::type_info& MediatorBase::getCurStateType() const
{
	return typeid(*curState_);
}
