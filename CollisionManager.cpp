#include "CollisionManager.h"
#include"GameActor.h"


ActorCollider* CollisionManager::AddPlayerCamp(GameActor* newActor)
{
	ActorCollider* ac = new ActorCollider;	
	playersCampCollision.emplace(newActor, ac);
}

ActorCollider* CollisionManager::AddEnemyCamp(GameActor* newActor)
{
	return nullptr;
}

auto CollisionManager::HitTestByPlayer()
{
}

auto CollisionManager::HitTestByEnemy()
{
}

void CollisionManager::RemoveEnemyCamp(GameActor*)
{
}

void CollisionManager::RemovePlayerCamp(GameActor*)
{
}
