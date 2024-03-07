#include<map>
#include<vector>
#include<unordered_map>
#include"../Engine/global.h"
#include"../Engine/Debug.h"
#include "CollisionManager.h"
#include"GameActor.h"

#include"DamageData.h"

//各陣営の当たり判定
namespace {
	using namespace CollisionManager;
	struct RangeData {
		AttackRangeBase* pRange_;
		std::vector<GameActor*>ExclutionList_{0};//すでにヒットしたものなど入れておく、判定からは除外
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
				if (std::find(itr->ExclutionList_.begin(), itr->ExclutionList_.end(), itrActor.pActor) != itr->ExclutionList_.end())
					continue;
				if (itr->pRange_->IsHit(itrActor))
				{
					UnderAttack(itrActor.pActor, itr->dmg_,itr->pRange_ );
				}
			}
			itr->pRange_->Duration--;
			if (itr->pRange_->Duration <= 0)
			{
				//なんか足りなくないか？
				delete itr->pRange_;
				itr->pRange_ = nullptr;
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

void CollisionManager::HitTestBy(CAMPS camp, AttackRangeCircle &circle)
{/*
	XMFLOAT3 c = circle.position_;
	c.y = 0;
	XMVECTOR circlePos = XMLoadFloat3(&c);
	for (auto& [actor, collider] : CollisionList.at((camp + 1) % NUM))
	{
		XMFLOAT3 a = *collider->position_;
		a.y = 0;
		XMVECTOR ActorPos = XMLoadFloat3(&a);
		if (XMVectorGetX(XMVector3Length(XMVectorAbs(circlePos - ActorPos))) < circle.radius_ + actor->GetRadius())
		{
			UnderAttack(actor);
			Debug::Log("〇あたった", true);
		}
	}*/
}

void CollisionManager::HitTestBy(CAMPS camp, AttackRangeQuad &quad)
{

	//XMMATRIX matRotY = XMMatrixRotationY(XMConvertToRadians(-quad.rotate_));//回転してる四角を、回転の分だけ戻す行列
	//XMMATRIX matMove = XMMatrixTranslation(-quad.position_.x, -quad.position_.y, -quad.position_.z);//原点にずらす行列
	//XMVECTOR quadPos = XMLoadFloat3(&quad.position_);
	//quadPos = XMVector3TransformCoord(quadPos, matMove * matRotY);//四角を原点にずらしてから回転
	//XMFLOAT3 f3Quad;
	//XMStoreFloat3(&f3Quad, quadPos);
	//for (const auto& [actor, collider] : CollisionList.at((camp + 1) % NUM))
	//{
	//	XMVECTOR ActorPos = XMLoadFloat3(collider->position_);
	//	ActorPos=XMVector3TransformCoord(ActorPos, matMove * matRotY);//円の位置もずらす
	//	XMFLOAT3 f3Actor;
	//	XMStoreFloat3(&f3Actor, ActorPos);
	//	using std::max;
	//	using std::min;
	//	using std::pow;
	//	XMFLOAT3 compare = {//当たり判定の四角の外周で、円の中心に最も近い地点を求める
	//		{max(f3Quad.x- quad.width_,min(f3Actor.x, f3Quad.x+quad.width_))} 
	//		,0//Yは判定いらない
	//		,{max(f3Quad.z-quad.length_, min(f3Actor.z, f3Quad.z+quad.length_)) }};

	//	float dist = (float)sqrt(pow(compare.x - f3Actor.x, 2) + pow(compare.z - f3Actor.z, 2));
	//	float r = (float)pow(actor->GetRadius(), 2);//此処と上の行不安アル
	//	if (dist <r)
	//	{
	//		UnderAttack(actor);
	//		Debug::Log("□あたった", true);
	//	}
	//}
}

void CollisionManager::HitTestBy(CAMPS camp, AttackRangeCirculerSector& sector)
{
	//XMFLOAT3 s = sector.position_;
	//s.y = 0;
	//XMVECTOR sectorPos = XMLoadFloat3(&s);
	//for (const auto& [actor, collider] : CollisionList.at((camp + 1) % NUM))
	//{
	//	
	//	XMFLOAT3 a = *collider->position_;
	//	a.y = 0;
	//	XMVECTOR ActorPos = XMLoadFloat3(&a);
	//	if (XMVectorGetX(XMVector3Length(XMVectorAbs(sectorPos - ActorPos))) > sector.radius_ + actor->GetRadius())//まずは円と同じ
	//	{
	//		continue;
	//	}
	//	float radAngle = XMConvertToRadians(sector.centerAngle_);//開き具合
	//	float radRot = XMConvertToRadians(sector.rotate_);//扇の回転
	//	XMMATRIX rotM = XMMatrixRotationY(radRot);
	//	XMVECTOR Front{ 0,0,1,0 };
	//	XMVECTOR rotFront = XMVector3TransformCoord(Front, rotM);//ここで扇形の回転具合
	//	//角度→(a・b)/|a||b|
	//	XMVECTOR sectorToActor = ActorPos - sectorPos;
	//	float deviation = XMVectorGetX(XMVector3AngleBetweenVectors(rotFront, sectorToActor));//ここで扇のどの辺にいるか角度が出せるはず
	//	if (std::abs(deviation)> radAngle)//中心が扇の外なら
	//	{//追加で検証
	//		XMMATRIX angleM = XMMatrixRotationY(radAngle);//開き具合
	//		float a, b;
	//		a = (std::abs(XMVectorGetX(XMVector3AngleBetweenVectors(XMVector3TransformCoord(rotFront, angleM), sectorToActor))));//片方の端
	//		b= std::abs(XMVectorGetX(XMVector3AngleBetweenVectors(XMVector3TransformCoord(rotFront, XMMatrixInverse(nullptr, angleM)), sectorToActor)));//もう片方の端。回転の逆行列
	//		float close = std::min(a, b);//両端を見て近いほうのrad
	//			
	//		float vecSin = XMVectorGetX(XMVector3Length(sectorToActor * std::sin(close)));
	//		if(vecSin>actor->GetRadius())//それでも範囲外なら
	//		{//スルー
	//			continue;
	//		}
	//	}
	//	//continueを踏まなかったらここに来るはず
	//	UnderAttack(actor);
	//	Debug::Log("扇あたった", true);
	//}
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
	CollisionList.clear();

	
}
