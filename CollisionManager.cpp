#include "CollisionManager.h"
#include"GameActor.h"
#include<map>
#include<vector>
#include<unordered_map>
#include"Engine/Debug.h"
//�e�w�c�̓����蔻��
namespace {
	std::vector<std::unordered_map<const GameActor*, const ActorCollider*>>CollisionList(CAMPS::NUM);
	
	/// <summary>
	/// �U�����󂯂����Ƃ�ʒm���A�eactor��TakeAttacked���Ă�
	/// </summary>
	void NotifyReceivedAttack()
	{

	}
}

void CollisionManager::AddCamp(GameActor* newActor, CAMPS camp)
{
	ActorCollider* ac = new ActorCollider(&newActor->GetTransformRef()->position_);
	CollisionList.at(camp).emplace(newActor, ac);

}

void CollisionManager::HitTestBy(CAMPS camp, AttackRangeCircle circle)
{
	for (const auto& [actor,collider] : CollisionList.at((camp + 1) % NUM))
	{
		XMVECTOR circlePos = XMLoadFloat3(&circle.position_);
		XMVECTOR ActorPos = XMLoadFloat3(collider->position_);
		/*float cLength = XMVectorGetX(XMVector3Length(circlePos));
		float aLength = XMVectorGetX(XMVector3Length(ActorPos));*/
		if (XMVectorGetX(XMVector3Length(XMVectorAbs(circlePos - ActorPos))) < circle.radius_ + actor->GetRadius())
		{
			//			actor->TakeAttacked();
			Debug::Log("�������Ă��", true);
		}
		else Debug::Log("�������ĂȂ���", true);
	}

	
}

void CollisionManager::HitTestBy(CAMPS camp, AttackRangeQuad quad)
{
}

void CollisionManager::HitTestBy(CAMPS camp, AttackRangeCirculerSector sector)
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
