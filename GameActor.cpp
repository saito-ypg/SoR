#include "GameActor.h"
#include"CollisionManager.h"
GameActor::GameActor(GameObject* parent, const std::string& name) : GameObject(parent, name)
{
}

void GameActor::Update()
{
	//‚¢‚ë‚¢‚ëXV“ü‚ê‚é
	
	ActorUpdate();
}
