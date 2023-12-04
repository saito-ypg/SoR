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
		XMVECTOR circlePos = XMLoadFloat3(&circle.position_);
		XMVECTOR ActorPos = XMLoadFloat3(collider->position_);
		if (XMVectorGetX(XMVector3Length(XMVectorAbs(circlePos - ActorPos))) < circle.radius_ + actor->GetRadius())
		{
			actor->TakeAttacked();
			Debug::Log("あたってるよ", true);
		}
		else Debug::Log("あたってないよ", true);
	}

	
}

void CollisionManager::HitTestBy(CAMPS camp, AttackRangeQuad quad)
{
	for (const auto& [actor, collider] : CollisionList.at((camp + 1) % NUM))
	{

		XMMATRIX matRotY = XMMatrixRotationY(-quad.rotate_);//回転してる四角を、回転の分だけ戻す行列
		XMMATRIX matMove = XMMatrixTranslation(-quad.position_.x, 0, -quad.position_.z);//原点にずらす行列

		XMVECTOR circlePos = XMLoadFloat3(&quad.position_);
		XMVector3TransformCoord(circlePos, matMove * matRotY);//四角を原点にずらしてから回転
		XMVECTOR ActorPos = XMLoadFloat3(collider->position_);
		XMVector3TransformCoord(ActorPos, matMove * matRotY);//円の位置もずらす
		XMFLOAT3 f3Circle, f3Actor;
		XMStoreFloat3(&f3Circle, circlePos);
		XMStoreFloat3(&f3Actor, ActorPos);
		using std::max;
		using std::min;
		float x = max(box.minX, Math.min(sphere.x, box.maxX));
		float y = Math.max(box.minY, Math.min(sphere.y, box.maxY));
		float z = Math.max(box.minZ, Math.min(sphere.z, box.maxZ));

		if ()
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
