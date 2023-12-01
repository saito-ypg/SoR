#include "CollisionManager.h"
#include"GameActor.h"
#include<map>
#include<vector>
#include<unordered_map>
//Šew‰c‚Ì“–‚½‚è”»’è
namespace {
	std::vector<std::unordered_map<const GameActor*,const ActorCollider*>>CollisionList;
	
	/// <summary>
	/// UŒ‚‚ğó‚¯‚½‚±‚Æ‚ğ’Ê’m‚µAŠeactor‚ÌTakeAttacked‚ğŒÄ‚Ô
	/// </summary>
	void NotifyReceivedAttack()
	{

	}
}

void CollisionManager::AddCamp(GameActor* newActor, CAMPS camp)
{
	ActorCollider* ac = new ActorCollider(&newActor->GetTransformRef()->position_);
	CollisionList.at(camp).emplace(newActor, ac);
	//ac->position_ =;

}

void CollisionManager::HitTestBy(CAMPS camp, AttackRangeCircle circle)
{
	for (const auto& [actor,collider] : CollisionList.at((camp + 1) % NUM))
	{
		XMVECTOR circlePos = XMLoadFloat3(&circle.position_);
		XMVECTOR ActorPos = XMLoadFloat3(collider->position_);
		float cLength = XMVectorGetX(XMVector3Length(circlePos));
		float aLength = XMVectorGetX(XMVector3Length(ActorPos));
		if (XMVectorGetX(XMVector3Length(circlePos - ActorPos)) < cLength + aLength)
		{
			int a = 0;
			actor->TakeAttacked();
		}
	}
	auto c = CollisionList.at(camp + 1);
	auto p = c.begin()->first;
	
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
	if (campMap.find(actor) == campMap.end())//‚»‚à‚»‚à‘¶İ‚µ‚È‚©‚Á‚½‚ç‰½‚à‚µ‚È‚¢H‹tw‰c‚Å‚â‚éH
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
