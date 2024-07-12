#include "MovementStateBase.h"
#include"EnemyBase.h"
MovementStateBase::MovementStateBase(EnemyBase& enemy) :enemy_(enemy)
{

}

MovementStateBase::~MovementStateBase()
{
	Release();
}

void MovementStateBase::Update(const float& dt)
{
}

void MovementStateBase::Release()
{
}

bool MovementStateBase::CanTransitionOut() const
{
	return canTransition_;
}

