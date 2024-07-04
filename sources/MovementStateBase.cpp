#include "MovementStateBase.h"

MovementStateBase::MovementStateBase(GameActor* pActor)
{

}

void MovementStateBase::SetTransform(Transform* t)
{
	enemyTransform_ = t;
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
