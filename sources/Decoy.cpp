#include"../Engine/Model.h"
#include "Decoy.h"

Decoy::Decoy(GameObject* parent) :EnemyBase(parent)
{
	status_ = ActorInfo{ 50,1.1f };
	transform_.position_ = { 0,0,0 };
	AddCamp();
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
