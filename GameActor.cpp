#include "GameActor.h"
#include"CollisionManager.h"
GameActor::GameActor(GameObject* parent, const std::string& name) : GameObject(parent, name)
{
}

void GameActor::Update()
{
	//いろいろ更新入れる
	
	ActorUpdate();
}

Transform* GameActor::GetTransformRef()
{
	return &transform_;
}
