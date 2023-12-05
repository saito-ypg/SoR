#include "CollisionManager.h"
#include"GameActor.h"
#include<map>
#include<vector>
#include<unordered_map>
#include"Engine/Debug.h"
#include<cmath>
//各陣営の当たり判定
namespace {
	std::vector<std::unordered_map<const GameActor*, const ActorCollider*>>CollisionList(CAMPS::NUM);
	
	/// <summary>
	/// 攻撃を受けたことを通知し、各actorのTakeAttackedを呼ぶ
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
		XMFLOAT3 c = circle.position_;
		c.y = 0;
		XMVECTOR circlePos = XMLoadFloat3(&c);
		XMFLOAT3 a = *collider->position_;
		a.y = 0;
		XMVECTOR ActorPos = XMLoadFloat3(&a);
		if (XMVectorGetX(XMVector3Length(XMVectorAbs(circlePos - ActorPos))) < circle.radius_ + actor->GetRadius())
		{

			const_cast<GameActor*>(actor)->TakeAttacked();
			Debug::Log("あたってるよ", true);
		}
		else Debug::Log("あたってないよ", true);
	}

	
}

void CollisionManager::HitTestBy(CAMPS camp, AttackRangeQuad quad)
{
	for (const auto& [actor, collider] : CollisionList.at((camp + 1) % NUM))
	{
		//const_cast<GameActor*>(actor);//暫定的にconst外し。mapやめるかメンバvolatileにするか？
		XMMATRIX matRotY = XMMatrixRotationY(XMConvertToRadians(-quad.rotate_));//回転してる四角を、回転の分だけ戻す行列
		XMMATRIX matMove = XMMatrixTranslation(-quad.position_.x, 0, -quad.position_.z);//原点にずらす行列

		XMVECTOR quadPos = XMLoadFloat3(&quad.position_);
		quadPos=XMVector3TransformCoord(quadPos, matMove * matRotY);//四角を原点にずらしてから回転
		XMVECTOR ActorPos = XMLoadFloat3(collider->position_);
		ActorPos=XMVector3TransformCoord(ActorPos, matMove * matRotY);//円の位置もずらす
		XMFLOAT3 f3Quad, f3Actor;
		XMStoreFloat3(&f3Quad, quadPos);
		XMStoreFloat3(&f3Actor, ActorPos);
		using std::max;
		using std::min;
		using std::pow;
		XMFLOAT3 compare = {//当たり判定の四角の外周で、円の中心に最も近い地点を導出
		 {max(f3Quad.x- quad.width_,min(f3Actor.x, f3Quad.x+quad.width_))} 
		,0//Yは判定いらない
		,{max(f3Quad.z-quad.length_, min(f3Actor.z, f3Quad.z+quad.length_)) }
		};
		float dist =sqrt( pow((compare.x *f3Actor.x),2) + pow((compare.z * f3Actor.z),2));
		if (dist <actor->GetRadius()*2)//Line63～ここまでネット記事参考。ロジック理解しきれてない。
		{
			Debug::Log("あたってるよ", true);
		}
		else Debug::Log("あたってないよ", true);
	}
}

void CollisionManager::HitTestBy(CAMPS camp, AttackRangeCirculerSector sector)
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
