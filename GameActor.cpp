#include "GameActor.h"
#include"CollisionManager.h"
GameActor::GameActor(GameObject* parent, const std::string& name) : GameObject(parent, name)
{
}

void GameActor::Update()
{
	//���낢��X�V�����
	
	ActorUpdate();
}
