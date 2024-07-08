#include "EnemyBase.h"
#include"MovementStateBase.h"
EnemyBase::EnemyBase(GameObject* parent, bool isboss):GameActor(parent, "Enemy")
{
	eStat_ = WAIT;
	pPlayer_ = nullptr;
	pMediator_ = nullptr;
	//curMovement = nullptr;
	if (isboss)
	{
		transform_.scale_ = { 1.5,1.5,1.5 };
	}
	isBoss_ = isboss;
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::SetMediator(std::unique_ptr<MediatorBase> mediator)
{
	pMediator_ =std::move(mediator); 
	pMediator_->setEnemy(this);
}

void EnemyBase::setConfig(const EnemyStatus & status)
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


void EnemyBase::mediatorUpdate(const float& dt)
{
	if (pMediator_)
	{
		pMediator_->Update(dt);
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

