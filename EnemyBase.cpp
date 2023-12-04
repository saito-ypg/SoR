#include "EnemyBase.h"

void EnemyBase::AddCamp()
{
	AddColliderCamp((GameActor*)this, ENEMY);
}

EnemyBase::EnemyBase(GameObject* parent):GameActor(parent,"Enemy")
{
}

EnemyBase::~EnemyBase()
{
}

