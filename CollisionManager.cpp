#include "CollisionManager.h"
#include"GameActor.h"


ActorCollider* CollisionManager::AddPlayerCollision(GameActor* newActor)
{
	ActorCollider* ac = new ActorCollider;
	playersCampCollision.emplace(ac, newActor);
	newActor.
}

ActorCollider* CollisionManager::AddEnemyCollision(GameActor* newActor)
{
	return nullptr;
}

auto CollisionManager::HitTestPlayer()
{
}

auto CollisionManager::HitTestEnemy()
{
}

void CollisionManager::RemoveEnemyCamp(GameActor*)
{
}

void CollisionManager::RemovePlayerCamp(GameActor*)
{
}
