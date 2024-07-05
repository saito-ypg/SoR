#include "MediatorBase.h"
#include"EnemyBase.h"

MediatorBase::MediatorBase() :base_(nullptr),curState_(nullptr),isTransition_(false)
{
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
