#include "CollisionManager.h"
#include"GameActor.h"
//�e�w�c�̓����蔻��
namespace {
	std::vector<std::map<GameActor*, ActorCollider*>>CollisionList;
	
	/// <summary>
	/// �U�����󂯂����Ƃ�ʒm���A�eactor��TakeAttacked���Ă�
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
	if (campMap.find(actor) == campMap.end())//�����������݂��Ȃ������牽�����Ȃ��H�t�w�c�ł��H
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
