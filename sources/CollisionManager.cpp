
#include<vector>
#include<unordered_map>
#include"Engine/global.h"
#include"Engine/Debug.h"
#include "CollisionManager.h"
#include"GameActor.h"
#include"areamodels.h"
#include"DamageData.h"

//�e�w�c�̓����蔻��
namespace {
	using namespace CollisionManager;
	struct RangeData {
		AttackRangeBase* pRange_;
		std::vector<GameActor*>ExclusionsList_{0};//���łɃq�b�g�������̂ȂǓ���Ă����A���肩��͏��O
		DamageData dmg_;
		std::function<void(float)>updateFunc;//�A�b�v�f�[�g���œ���ȓ��e���K�v�Ȃ炱���ɓ����
		RangeData(AttackRangeBase* pR, DamageData dmg) :RangeData(pR,dmg,nullptr){}
		RangeData(AttackRangeBase* pR, DamageData dmg,std::function<void(float)>func) :pRange_(pR), dmg_(dmg),updateFunc(func){}
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

void CollisionManager::Update(const float &dt)
{
	for (int camp=0;camp<CAMPS::NUM;camp++)//�w�c2�̃��[�v
	{
		for (auto itr = RangeTest.at(camp).begin(); itr != RangeTest.at(camp).end();)//���ꂼ��̐w�c���ׂẴ��[�v�A
		{

			for (auto& itrActor : CollisionList.at(((camp)+1) % NUM))//����̐w�c�̓G�Ɣ�����
			{
				if (std::find(itr->ExclusionsList_.begin(), itr->ExclusionsList_.end(), itrActor.pActor) != itr->ExclusionsList_.end())
					continue;//���O���X�g�ς݂Ȃ�X���[
				if (itr->pRange_->IsHit(itrActor))
				{
					UnderAttack(itrActor.pActor, itr->dmg_, itr->pRange_);
				}
			}

			itr->dmg_.duration_ -= dt;
			
			if (itr->dmg_.duration_ <= 0)
			{
				SAFE_DELETE(itr->pRange_);
				itr = RangeTest.at(camp).erase(itr);
			}
			else {
				if (auto& f = itr->updateFunc) {//�֐��I�u�W�F�N�g���������Ă�����X�V
					f(dt);
				}
				itr++;
			}
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
void CollisionManager::RegisterHitRange(CAMPS camp, AttackRangeCircle c, DamageData dmg, std::function<void(float)>func)
{
	RangeTest.at(camp).emplace_back(RangeData(new AttackRangeCircle(c),dmg,func));
}

void CollisionManager::RegisterHitRange(CAMPS camp, AttackRangeQuad q, DamageData dmg, std::function<void(float)>func)
{
	RangeTest.at(camp).emplace_back(RangeData(new AttackRangeQuad(q), dmg,func ));
}

void CollisionManager::RegisterHitRange(CAMPS camp, AttackRangeCirculerSector s, DamageData dmg, std::function<void(float)>func)
{
	RangeTest.at(camp).emplace_back(RangeData(new AttackRangeCirculerSector(s), dmg,func));
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
