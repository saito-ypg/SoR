#include"../Engine/Model.h"
#include "Decoy.h"

Decoy::Decoy(GameObject* parent, bool isBoss) :EnemyBase(parent,isBoss)
{

}

Decoy::~Decoy()
{
}

void Decoy::dyingDraw()
{
	transform_.rotate_.x = -90;
}

void Decoy::Initialize()
{
	hBody_=Model::Load("Charactors/decoy.fbx");
	assert(hBody_ >= 0);
}

void Decoy::ActorUpdate(const float& dt)
{
}

void Decoy::ActorDraw()
{
	DrawBody();
}

void Decoy::Release()
{
	RemoveCamp();
}
