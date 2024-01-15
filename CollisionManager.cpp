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
	/// �U�������������ۂɌĂ΂��B
	/// </summary>
	void UnderAttack(const GameActor* a)
	{
		const_cast<GameActor*>(a)->TakeAttacked();//�b��I��const�L���X�g�B
	}
}

void CollisionManager::Update()
{
}

void CollisionManager::AddCamp(GameActor* newActor, CAMPS camp)
{
	ActorCollider* ac = new ActorCollider(&newActor->GetTransformRef()->position_);
	CollisionList.at(camp).emplace(newActor, ac);

}

void CollisionManager::HitTestBy(CAMPS camp, AttackRangeCircle &circle)
{
	XMFLOAT3 c = circle.position_;
	c.y = 0;
	XMVECTOR circlePos = XMLoadFloat3(&c);
	for (const auto& [actor,collider] : CollisionList.at((camp + 1) % NUM))
	{
		XMFLOAT3 a = *collider->position_;
		a.y = 0;
		XMVECTOR ActorPos = XMLoadFloat3(&a);
		if (XMVectorGetX(XMVector3Length(XMVectorAbs(circlePos - ActorPos))) < circle.radius_ + actor->GetRadius())
		{
			UnderAttack(actor);
			Debug::Log("�Z��������", true);
		}
	}
}

void CollisionManager::HitTestBy(CAMPS camp, AttackRangeQuad &quad)
{

	XMMATRIX matRotY = XMMatrixRotationY(XMConvertToRadians(-quad.rotate_));//��]���Ă�l�p���A��]�̕������߂��s��
	XMMATRIX matMove = XMMatrixTranslation(-quad.position_.x, -quad.position_.y, -quad.position_.z);//���_�ɂ��炷�s��
	XMVECTOR quadPos = XMLoadFloat3(&quad.position_);
	quadPos = XMVector3TransformCoord(quadPos, matMove * matRotY);//�l�p�����_�ɂ��炵�Ă����]
	XMFLOAT3 f3Quad;
	XMStoreFloat3(&f3Quad, quadPos);
	for (const auto& [actor, collider] : CollisionList.at((camp + 1) % NUM))
	{
		XMVECTOR ActorPos = XMLoadFloat3(collider->position_);
		ActorPos=XMVector3TransformCoord(ActorPos, matMove * matRotY);//�~�̈ʒu�����炷
		XMFLOAT3 f3Actor;
		XMStoreFloat3(&f3Actor, ActorPos);
		using std::max;
		using std::min;
		using std::pow;
		XMFLOAT3 compare = {//�����蔻��̎l�p�̊O���ŁA�~�̒��S�ɍł��߂��n�_�����߂�
			{max(f3Quad.x- quad.width_,min(f3Actor.x, f3Quad.x+quad.width_))} 
			,0//Y�͔��肢��Ȃ�
			,{max(f3Quad.z-quad.length_, min(f3Actor.z, f3Quad.z+quad.length_)) }};

		float dist = sqrt(pow(compare.x - f3Actor.x, 2) + pow(compare.z - f3Actor.z, 2));
		float r = pow(actor->GetRadius(), 2);//�����Ə�̍s�s���A��
		if (dist <r)
		{
			UnderAttack(actor);
			Debug::Log("����������", true);
		}
	}
}

void CollisionManager::HitTestBy(CAMPS camp, AttackRangeCirculerSector& sector)
{
	XMFLOAT3 s = sector.position_;
	s.y = 0;
	XMVECTOR sectorPos = XMLoadFloat3(&s);
	for (const auto& [actor, collider] : CollisionList.at((camp + 1) % NUM))
	{
		
		XMFLOAT3 a = *collider->position_;
		a.y = 0;
		XMVECTOR ActorPos = XMLoadFloat3(&a);
		if (XMVectorGetX(XMVector3Length(XMVectorAbs(sectorPos - ActorPos))) > sector.radius_ + actor->GetRadius())//�܂��͉~�Ɠ���
		{
			continue;
		}
		float radAngle = XMConvertToRadians(sector.centerAngle_);//�J���
		float radRot = XMConvertToRadians(sector.rotate_);//��̉�]
		XMMATRIX rotM = XMMatrixRotationY(radRot);
		XMVECTOR Front{ 0,0,1,0 };
		XMVECTOR rotFront = XMVector3TransformCoord(Front, rotM);//�����Ő�`�̉�]�
		//�p�x��(a�Eb)/|a||b|
		XMVECTOR sectorToActor = ActorPos - sectorPos;
		float deviation = XMVectorGetX(XMVector3AngleBetweenVectors(rotFront, sectorToActor));//�����Ő�̂ǂ̕ӂɂ��邩�p�x���o����͂�
		if (std::abs(deviation)> radAngle)//���S����̊O�Ȃ�
		{//�ǉ��Ō���
			XMMATRIX angleM = XMMatrixRotationY(radAngle);//�J���
			float a, b;
			a = (std::abs(XMVectorGetX(XMVector3AngleBetweenVectors(XMVector3TransformCoord(rotFront, angleM), sectorToActor))));//�Е��̒[
			b= std::abs(XMVectorGetX(XMVector3AngleBetweenVectors(XMVector3TransformCoord(rotFront, XMMatrixInverse(nullptr, angleM)), sectorToActor)));//�����Е��̒[�B��]�̋t�s��
			float close = std::min(a, b);//���[�����ċ߂��ق���rad
				
			float sinx = XMVectorGetX(XMVector3Length(sectorToActor * std::sin(close)));
			if(sinx>actor->GetRadius())//����ł��O�ɂ���Ȃ�
			{//�O��
				continue;
			}
		}
		//continue�𓥂܂Ȃ������炱���ɗ���͂�
		UnderAttack(actor);
		Debug::Log("�������", true);
	}
}



void CollisionManager::RemoveCamp(GameActor*actor,CAMPS camp)
{
	auto& campMap = CollisionList.at(camp);
	if (campMap.find(actor) == campMap.end())//�����������݂��Ȃ������牽�����Ȃ��H
	{
		return;
	}
	delete	campMap.at(actor);
	campMap.erase(actor);
}


void CollisionManager::Release()
{
	for (auto& it : CollisionList)
	{
		for (auto& itin : it)
		{
			delete itin.second;
		}
		it.clear();
	}
	CollisionList.clear();

	
}
