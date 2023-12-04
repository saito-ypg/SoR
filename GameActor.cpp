#include "GameActor.h"
#include"Engine/Model.h"
void GameActor::AddColliderCamp(GameActor* act, CAMPS camp)
{    
	CollisionManager::AddCamp(act, camp);
}
void GameActor::SimpleDraw()
{
	if (hModels_.empty())
		return;
	int front = hModels_.front();
	Model::SetTransform(front, transform_);
	Model::Draw(front);
}
GameActor::GameActor(GameObject* parent, const std::string& name) : GameObject(parent, name)
{
	isInvincible_ = false;
}

GameActor::~GameActor()
{
}

void GameActor::Update()
{
	//Ç¢ÇÎÇ¢ÇÎçXêVì¸ÇÍÇÈ
	
	ActorUpdate();
}

void GameActor::ActorUpdate()
{
}

void GameActor::TakeAttacked() const
{
}

Transform* GameActor::GetTransformRef()
{
	return &transform_;
}
