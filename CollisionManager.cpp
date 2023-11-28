#include "CollisionManager.h"
#include"GameActor.h"
//各陣営の当たり判定
namespace {
	std::vector<std::map<const GameActor*,const ActorCollider*>>CollisionList;
	
	/// <summary>
	/// 攻撃を受けたことを通知し、各actorのTakeAttackedを呼ぶ
	/// </summary>
	void NotifyReceivedAttack()
	{

	}
}

void CollisionManager::AddCamp(GameActor* newActor, CAMPS camp)
{
	ActorCollider* ac = new ActorCollider;
	CollisionList.at(camp).emplace(newActor, ac);
	ac->position_ = &newActor->GetTransformRef()->position_;

}

void CollisionManager::HitTestBy(CAMPS camp, AttackRangeCircle circle)
{
	for (auto i : CollisionList.at((camp + 1) % NUM))
	{
		XMVECTOR p = XMLoadFloat3(i.second->position_);
		i.
	}
}

void CollisionManager::HitTestBy(CAMPS camp, AttackRangeQuad quad)
{
}

void CollisionManager::HitTestBy(CAMPS camp, AttackRangeCirculerSctor sector)
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
