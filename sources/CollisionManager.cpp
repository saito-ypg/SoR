#include<map>
#include<vector>
#include<unordered_map>
#include"../Engine/global.h"
#include"../Engine/Debug.h"
#include "CollisionManager.h"
#include"GameActor.h"

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
			itr->pRange_->Duration--;
			if (itr->pRange_->Duration <= 0)
			{
				//�Ȃ񂩑���Ȃ��Ȃ����H
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
		if (itr.pActor == newActor)//�d�����Ȃ��悤��
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
			Debug::Log("�Z��������", true);
		}
	}*/
}

void CollisionManager::HitTestBy(CAMPS camp, AttackRangeQuad &quad)
{

	//XMMATRIX matRotY = XMMatrixRotationY(XMConvertToRadians(-quad.rotate_));//��]���Ă�l�p���A��]�̕������߂��s��
	//XMMATRIX matMove = XMMatrixTranslation(-quad.position_.x, -quad.position_.y, -quad.position_.z);//���_�ɂ��炷�s��
	//XMVECTOR quadPos = XMLoadFloat3(&quad.position_);
	//quadPos = XMVector3TransformCoord(quadPos, matMove * matRotY);//�l�p�����_�ɂ��炵�Ă����]
	//XMFLOAT3 f3Quad;
	//XMStoreFloat3(&f3Quad, quadPos);
	//for (const auto& [actor, collider] : CollisionList.at((camp + 1) % NUM))
	//{
	//	XMVECTOR ActorPos = XMLoadFloat3(collider->position_);
	//	ActorPos=XMVector3TransformCoord(ActorPos, matMove * matRotY);//�~�̈ʒu�����炷
	//	XMFLOAT3 f3Actor;
	//	XMStoreFloat3(&f3Actor, ActorPos);
	//	using std::max;
	//	using std::min;
	//	using std::pow;
	//	XMFLOAT3 compare = {//�����蔻��̎l�p�̊O���ŁA�~�̒��S�ɍł��߂��n�_�����߂�
	//		{max(f3Quad.x- quad.width_,min(f3Actor.x, f3Quad.x+quad.width_))} 
	//		,0//Y�͔��肢��Ȃ�
	//		,{max(f3Quad.z-quad.length_, min(f3Actor.z, f3Quad.z+quad.length_)) }};

	//	float dist = (float)sqrt(pow(compare.x - f3Actor.x, 2) + pow(compare.z - f3Actor.z, 2));
	//	float r = (float)pow(actor->GetRadius(), 2);//�����Ə�̍s�s���A��
	//	if (dist <r)
	//	{
	//		UnderAttack(actor);
	//		Debug::Log("����������", true);
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
	//	if (XMVectorGetX(XMVector3Length(XMVectorAbs(sectorPos - ActorPos))) > sector.radius_ + actor->GetRadius())//�܂��͉~�Ɠ���
	//	{
	//		continue;
	//	}
	//	float radAngle = XMConvertToRadians(sector.centerAngle_);//�J���
	//	float radRot = XMConvertToRadians(sector.rotate_);//��̉�]
	//	XMMATRIX rotM = XMMatrixRotationY(radRot);
	//	XMVECTOR Front{ 0,0,1,0 };
	//	XMVECTOR rotFront = XMVector3TransformCoord(Front, rotM);//�����Ő�`�̉�]�
	//	//�p�x��(a�Eb)/|a||b|
	//	XMVECTOR sectorToActor = ActorPos - sectorPos;
	//	float deviation = XMVectorGetX(XMVector3AngleBetweenVectors(rotFront, sectorToActor));//�����Ő�̂ǂ̕ӂɂ��邩�p�x���o����͂�
	//	if (std::abs(deviation)> radAngle)//���S����̊O�Ȃ�
	//	{//�ǉ��Ō���
	//		XMMATRIX angleM = XMMatrixRotationY(radAngle);//�J���
	//		float a, b;
	//		a = (std::abs(XMVectorGetX(XMVector3AngleBetweenVectors(XMVector3TransformCoord(rotFront, angleM), sectorToActor))));//�Е��̒[
	//		b= std::abs(XMVectorGetX(XMVector3AngleBetweenVectors(XMVector3TransformCoord(rotFront, XMMatrixInverse(nullptr, angleM)), sectorToActor)));//�����Е��̒[�B��]�̋t�s��
	//		float close = std::min(a, b);//���[�����ċ߂��ق���rad
	//			
	//		float vecSin = XMVectorGetX(XMVector3Length(sectorToActor * std::sin(close)));
	//		if(vecSin>actor->GetRadius())//����ł��͈͊O�Ȃ�
	//		{//�X���[
	//			continue;
	//		}
	//	}
	//	//continue�𓥂܂Ȃ������炱���ɗ���͂�
	//	UnderAttack(actor);
	//	Debug::Log("�������", true);
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
