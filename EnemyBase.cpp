#include "EnemyBase.h"

void EnemyBase::AddCamp()
{
	AddColliderCamp((GameActor*)this, ENEMY);
}

void EnemyBase::RemoveCamp()
{
	RemoveColliderCamp((GameActor*)this, ENEMY);
}

EnemyBase::EnemyBase(GameObject* parent):GameActor(parent,"Enemy")
{
	eStat_ = WAIT;
}

EnemyBase::~EnemyBase()
{
}

