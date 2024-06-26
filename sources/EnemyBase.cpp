#include "EnemyBase.h"
#include"MovementStateBase.h"
EnemyBase::EnemyBase(GameObject* parent, bool isboss):GameActor(parent, "Enemy")
{
	eStat_ = WAIT;
	pPlayer = nullptr;
	curMovement = nullptr;
	if (isboss)
	{
		transform_.scale_ = { 1.5,1.5,1.5 };
	}
	isBoss_ = isboss;
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::setConfig(EnemyStatus status)
{
	if (isBoss_) {
		status_.maxHp_ = status.hp * 2;
		status_.hp_ = status.hp * 2;
		status_.hitCircleRange_ = status.radius * 2;
	}
	else {
		status_.maxHp_ = status.hp;
		status_.hp_ = status.hp;
		status_.hitCircleRange_ = status.radius;
	}
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

