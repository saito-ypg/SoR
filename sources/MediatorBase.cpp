#include "MediatorBase.h"
#include"MovementStateBase.h"
#include"EnemyBase.h"
MediatorBase::MediatorBase(EnemyBase* enemy) :base(nullptr),curState(nullptr)
{
}

MediatorBase::~MediatorBase()
{
}

void MediatorBase::Update(const float& dt)
{
	curState.
}
