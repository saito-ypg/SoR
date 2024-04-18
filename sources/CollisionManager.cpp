#include<map>
#include<vector>
#include<unordered_map>
#include"../Engine/global.h"
#include"../Engine/Debug.h"
#include "CollisionManager.h"
#include"GameActor.h"
#include"areamodels.h"
#include"DamageData.h"

//�e�w�c�̓����蔻��
namespace {
	using namespace CollisionManager;
	struct RangeData {
		AttackRangeBase* pRange_;
		std::vector<GameActor*>ExclutionList_{0};//���łɃq�b�g�������̂ȂǓ���Ă����A���肩��͏��O
		DamageData dmg_;
		RangeData(AttackRangeBase* pR, DamageData dmg) :pRange_(pR),dmg_(dmg){}
	};
	std::vector<std::vector<actorAddr>>CollisionList(CAMPS::NUM);
	std::vector<std::vector<RangeData>>RangeTest(CAMPS::NUM);
	/// <summary>
	/// �U�������������ۂɌĂ΂��B
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
		for (auto itr = RangeTest.at(camp).begin(); itr != RangeTest.at(camp).end();)//�o�Ă��铖���蔻��S�Ăɔ���
		{
			for (auto& itrActor : CollisionList.at(((camp)+1) % NUM))//����̐w�c�̓G�Ɣ�����
			{
				if (std::find(itr->ExclutionList_.begin(), itr->ExclutionList_.end(), itrActor.pActor) != itr->ExclutionList_.end())
					continue;
				if (itr->pRange_->IsHit(itrActor))
				{
					UnderAttack(itrActor.pActor, itr->dmg_,itr->pRange_ );
				}
			}
			itr->dmg_.duration_--;
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
		if (itr.pActor == newActor)//�d�����Ȃ��悤��
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
