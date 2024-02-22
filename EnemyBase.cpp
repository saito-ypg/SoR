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

EnemyBase::EnemyBase(GameObject* parent, bool isboss):EnemyBase(parent)
{
	if (isboss)
	{
		transform_.scale_ = { 1.5,1.5,1.5 };
	}
}

EnemyBase::~EnemyBase()
{
}

