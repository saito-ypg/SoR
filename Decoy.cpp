#include "Decoy.h"
#include"Engine/Model.h"
Decoy::Decoy(GameObject* parent) :EnemyBase(parent)
{
	status_ = ActorInfo{ 1,1.1 };
	AddCamp();
}

Decoy::~Decoy()
{
}

void Decoy::Initialize()
{
	hModels_.push_back(Model::Load("Assets\\decoy.fbx"));
}

void Decoy::ActorUpdate()
{
}

void Decoy::Draw()
{
	SimpleDraw();
}

void Decoy::Release()
{
}
