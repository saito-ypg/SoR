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
	hModels_.push_back(Model::Load("Charactors/decoy.fbx"));
}

void Decoy::ActorUpdate(const float& dt)
{
}

void Decoy::ActorDraw()
{
	SimpleDraw();
}

void Decoy::Release()
{
	RemoveCamp();
}
