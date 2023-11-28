#include "GameActor.h"
#include"CollisionManager.h"
GameActor::GameActor(GameObject* parent, const std::string& name) : GameObject(parent, name)
{
	isInvincible_ = false;
}

GameActor::~GameActor()
{
}

void GameActor::Update()
{
	//いろいろ更新入れる
	
	ActorUpdate();
}

void GameActor::ActorUpdate()
{
}

void GameActor::TakeAttacked()
{
}

Transform* GameActor::GetTransformRef()
{
	return &transform_;
}
