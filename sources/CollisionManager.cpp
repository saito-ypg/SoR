
#include<vector>
#include<unordered_map>
#include"../Engine/global.h"
#include"../Engine/Debug.h"
#include "CollisionManager.h"
#include"GameActor.h"
#include"areamodels.h"
#include"DamageData.h"

//各陣営の当たり判定
namespace {
	using namespace CollisionManager;
	struct RangeData {
		AttackRangeBase* pRange_;
		std::vector<GameActor*>ExclusionsList_{0};//すでにヒットしたものなど入れておく、判定からは除外
		DamageData dmg_;
		RangeData(AttackRangeBase* pR, DamageData dmg) :pRange_(pR),dmg_(dmg){}
	};
	std::vector<std::vector<actorAddr>>CollisionList(CAMPS::NUM);
	std::vector<std::vector<RangeData>>RangeTest(CAMPS::NUM);
	/// <summary>
	/// 攻撃が当たった際に呼ばれる。
	/// </summary>
	void UnderAttack(::GameActor* act, DamageData& dmg,AttackRangeBase*range)
	{
		XMFLOAT3 actpos = act->GetPosition();
		XMVECTOR dir = range->getDir(act->GetPosition());
		act->TakeAttacked(dmg,dir);
	}
}

void CollisionManager::Update()
{
	for (int camp=0;camp<CAMPS::NUM;camp++)
	{
		for (auto itr = RangeTest.at(camp).begin(); itr != RangeTest.at(camp).end();)//出ている当たり判定全てに判定
		{
			for (auto& itrActor : CollisionList.at(((camp)+1) % NUM))//相手の陣営の敵と判定取る
			{
				if (std::find(itr->ExclusionsList_.begin(), itr->ExclusionsList_.end(), itrActor.pActor) != itr->ExclusionsList_.end())
					continue;
				if (itr->pRange_->IsHit(itrActor))
				{
					UnderAttack(itrActor.pActor, itr->dmg_,itr->pRange_ );
				}
			}
			itr->dmg_.duration_--;
			itr->pRange_->AreaTransition();
			if (itr->dmg_.duration_ <= 0)
			{
			
				SAFE_DELETE(itr->pRange_);
				itr = RangeTest.at(camp).erase(itr);
			}
			else
				itr++;
		}
	}
}

void CollisionManager::AddCamp(::GameActor* newActor, CAMPS camp)
{
	for (auto& itr : CollisionList.at(camp))
	{
		if (itr.pActor == newActor)//重複しないように
			return;
	}
	ActorCollider* ac = new ActorCollider(&newActor->GetTransformRef()->position_);
	CollisionList.at(camp).emplace_back(newActor, ac);

}
void CollisionManager::RegisterHitRange(CAMPS camp, AttackRangeCircle c, DamageData dmg)
{
	RangeTest.at(camp).emplace_back(RangeData(new AttackRangeCircle(c),dmg));
}

void CollisionManager::RegisterHitRange(CAMPS camp, AttackRangeQuad q, DamageData dmg)
{
	RangeTest.at(camp).emplace_back(RangeData(new AttackRangeQuad(q), dmg));
}

void CollisionManager::RegisterHitRange(CAMPS camp, AttackRangeCirculerSector s, DamageData dmg)
{
	RangeTest.at(camp).emplace_back(RangeData(new AttackRangeCirculerSector(s), dmg));
}



void CollisionManager::RemoveCamp(GameActor*actor,CAMPS camp)
{
	auto& campMap = CollisionList.at(camp);
	for (auto itr=campMap.begin();itr!=campMap.end();)
	{
		if (itr->pActor == actor)
		{
			SAFE_DELETE(itr->pCollider);
			itr = campMap.erase(itr);
			break;
		}
		itr++;
	}

}


void CollisionManager::Release()
{
	for (auto& it : CollisionList)
	{
		for (auto& itin : it)
		{
			SAFE_DELETE(itin.pCollider);
		}
		it.clear();
	}

	for (auto& it : RangeTest)
	{
		for (auto& itin : it)
		{
			SAFE_DELETE(itin.pRange_);
		}
		it.clear();
	}

}
