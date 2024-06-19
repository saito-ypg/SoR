#include "SoldierEnemy.h"
#include"../Engine/Model.h"
SoldierEnemy::SoldierEnemy(GameObject* parent,bool isBoss):EnemyBase(parent,isBoss)
{
}

SoldierEnemy::~SoldierEnemy()
{
}

void SoldierEnemy::dyingDraw()
{
}

void SoldierEnemy::Initialize()
{
	hBody_ = Model::Load("Charactors/soldier.fbx");
	assert(hBody_ >= 0);
}

void SoldierEnemy::ActorUpdate(const float& dt)
{
}

void SoldierEnemy::ActorDraw()
{
}

void SoldierEnemy::Release()
{
}
