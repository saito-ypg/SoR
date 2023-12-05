#include "CollisionManager.h"
#include"GameActor.h"
#include<map>
#include<vector>
#include<unordered_map>
#include"Engine/Debug.h"
#include<cmath>
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
		XMFLOAT3 c = circle.position_;
		c.y = 0;
		XMVECTOR circlePos = XMLoadFloat3(&c);
		XMFLOAT3 a = *collider->position_;
		a.y = 0;
		XMVECTOR ActorPos = XMLoadFloat3(&a);
		if (XMVectorGetX(XMVector3Length(XMVectorAbs(circlePos - ActorPos))) < circle.radius_ + actor->GetRadius())
		{

			const_cast<GameActor*>(actor)->TakeAttacked();
			Debug::Log("�������Ă��", true);
		}
		else Debug::Log("�������ĂȂ���", true);
	}

	
}

void CollisionManager::HitTestBy(CAMPS camp, AttackRangeQuad quad)
{
	for (const auto& [actor, collider] : CollisionList.at((camp + 1) % NUM))
	{
		//const_cast<GameActor*>(actor);//�b��I��const�O���Bmap��߂邩�����ovolatile�ɂ��邩�H
		XMMATRIX matRotY = XMMatrixRotationY(XMConvertToRadians(-quad.rotate_));//��]���Ă�l�p���A��]�̕������߂��s��
		XMMATRIX matMove = XMMatrixTranslation(-quad.position_.x, 0, -quad.position_.z);//���_�ɂ��炷�s��

		XMVECTOR quadPos = XMLoadFloat3(&quad.position_);
		quadPos=XMVector3TransformCoord(quadPos, matMove * matRotY);//�l�p�����_�ɂ��炵�Ă����]
		XMVECTOR ActorPos = XMLoadFloat3(collider->position_);
		ActorPos=XMVector3TransformCoord(ActorPos, matMove * matRotY);//�~�̈ʒu�����炷
		XMFLOAT3 f3Quad, f3Actor;
		XMStoreFloat3(&f3Quad, quadPos);
		XMStoreFloat3(&f3Actor, ActorPos);
		using std::max;
		using std::min;
		using std::pow;
		XMFLOAT3 compare = {//�����蔻��̎l�p�̊O���ŁA�~�̒��S�ɍł��߂��n�_�𓱏o
		 {max(f3Quad.x- quad.width_,min(f3Actor.x, f3Quad.x+quad.width_))} 
		,0//Y�͔��肢��Ȃ�
		,{max(f3Quad.z-quad.length_, min(f3Actor.z, f3Quad.z+quad.length_)) }
		};
		float dist =sqrt( pow((compare.x *f3Actor.x),2) + pow((compare.z * f3Actor.z),2));
		if (dist <actor->GetRadius()*2)//Line63�`�����܂Ńl�b�g�L���Q�l�B���W�b�N����������ĂȂ��B
		{
			Debug::Log("�������Ă��", true);
		}
		else Debug::Log("�������ĂȂ���", true);
	}
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
