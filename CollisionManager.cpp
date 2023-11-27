#include "CollisionManager.h"
#include"GameActor.h"

ActorCollider* CollisionManager::AddCamp(GameActor* newActor, CAMPS camp)
{
	ActorCollider* ac = new ActorCollider;
	CollisionList.at(camp).emplace(newActor, ac);
	ac->position_ = &newActor->GetTransformRef()->position_;

}


auto CollisionManager::HitTestBy()
{

}

void CollisionManager::RemoveCamp(GameActor*actor,CAMPS camp)
{
	auto& campMap = CollisionList.at(camp);
	if (campMap.find(actor) == campMap.end())//そもそも存在しなかったら何もしない？逆陣営でやる？
	{
		return;
	}
	delete	campMap.at(actor);
	campMap.erase(actor);
}

void CollisionManager::Release()
{
	for (auto it : CollisionList)
	{
		for (auto itin : it)
		{
			delete itin.second;
		}
		it.clear();
	}
	CollisionList.clear();

	
}
