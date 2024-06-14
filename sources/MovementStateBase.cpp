#include "MovementStateBase.h"

MovementStateBase::MovementStateBase()
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

void MovementStateBase::Update(XMFLOAT3 pos)
{
}

void MovementStateBase::Release()
{
}
