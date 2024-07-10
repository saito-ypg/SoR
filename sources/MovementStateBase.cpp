#include "MovementStateBase.h"
#include"EnemyBase.h"
MovementStateBase::MovementStateBase(EnemyBase& enemy) :enemy_(enemy)
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

