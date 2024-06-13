#include "EnemyBase.h"
#include"MovementStateBase.h"
EnemyBase::EnemyBase(GameObject* parent,EnemyType type, bool isboss):GameActor(parent, "Enemy")
{
	eStat_ = WAIT;
	pPlayer = nullptr;
	if (isboss)
	{
		transform_.scale_ = { 1.5,1.5,1.5 };
	}
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::setConfig(EnemyStatus status)
{
	status_.maxHp_ = status.hp;
	status_.hp_ = status.hp;
	status_.hitCircleRange_ = status.radius;
}


void EnemyBase::AddCamp()
{
	AddColliderCamp((GameActor*)this, ENEMY);
}

void EnemyBase::RemoveCamp()
{
	RemoveColliderCamp((GameActor*)this, ENEMY);
}

void EnemyBase::dyingProcess()
{
	RemoveCamp();
	eStat_ = DEAD;
}

