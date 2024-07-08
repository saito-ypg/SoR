#include "MediatorBase.h"
#include"EnemyBase.h"

MediatorBase::MediatorBase() :base_(nullptr),isTransition_(false)
{
	curState_ = std::make_unique<IdleState>();
}

MediatorBase::~MediatorBase()
{
}

void MediatorBase::Update(const float& dt)
{
	curState_->Update(dt);
	if (isTransition_) {
		DetermineNextState();
		isTransition_ = false;
	}
}

void MediatorBase::setEnemy(EnemyBase* enemy)
{
	base_ = enemy;
}
