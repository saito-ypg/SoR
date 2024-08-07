#include "MediatorBase.h"
#include"EnemyBase.h"
#include"IdleState.h"
MediatorBase::MediatorBase(EnemyBase& enemy) :base_(enemy)
{
	curState_ = std::make_unique<IdleState>(enemy);
	SkipDeterminingMs = 0;
}

MediatorBase::~MediatorBase()
{
}

void MediatorBase::Update(const float& dt)
{
	curState_->Update(dt);
	if (SkipDeterminingMs<=0&& curState_->CanTransitionOut()) {//ここの条件、trueなら毎回判断入っちゃうから一定時間空けたほうがいいかも？
		DetermineNextState();
		SkipDeterminingMs = rand() % 4000 + 1000;//ミリ秒単位,適当
	}
	else {
		SkipDeterminingMs -= static_cast<int>(dt);
	}
}

const std::type_info& MediatorBase::getCurStateType() const
{
	return typeid(*curState_);
}
