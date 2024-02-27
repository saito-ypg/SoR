#include<cmath>
#include "AttackRange.h"
#include"CollisionManager.h"
#include"GameActor.h"
#pragma warning(disable:26437)
using namespace AreaModels;
AttackRangeBase::AttackRangeBase() :areatype_(NONE),position_({ 0,0,0 }), Duration(1)
{
}
AttackRangeBase::AttackRangeBase(XMFLOAT3 pos) :AttackRangeBase()
{
	position_ = pos;
}

AttackRangeCircle::AttackRangeCircle() :AttackRangeBase()
{
	radius_ = -1;
	areatype_ = CIRCLE;
}

AttackRangeCircle::AttackRangeCircle(XMFLOAT3 pos) :AttackRangeCircle()
{
	position_ = pos;
}

bool AttackRangeCircle::IsHit(actorAddr& data)
{
	XMFLOAT3 c = position_;
	c.y = 0;
	XMVECTOR circlePos = XMLoadFloat3(&c);
	XMFLOAT3 a = *data.pCollider->position_;
	a.y = 0;
	XMVECTOR ActorPos = XMLoadFloat3(&a);
	return (XMVectorGetX(XMVector3Length(XMVectorAbs(circlePos - ActorPos))) < radius_ + data.pActor->GetRadius());

}

XMVECTOR AttackRangeCircle::getDir(XMFLOAT3 pos)
{
	return  XMVector3Normalize(XMLoadFloat3(&pos) - XMLoadFloat3(&position_));
}


AttackRangeQuad::AttackRangeQuad() :AttackRangeBase()
{
	width_ = -1;
	length_ = -1;
	rotate_ = 0;

	areatype_ = QUAD;
}

AttackRangeQuad::AttackRangeQuad(XMFLOAT3 pos) :AttackRangeQuad()
{
	position_ = pos;
}

bool AttackRangeQuad::IsHit(actorAddr& data)
{
	XMMATRIX matRotY = XMMatrixRotationY(XMConvertToRadians(rotate_));//��]���Ă�l�p���A��]�̕������߂��s��
	XMMATRIX matMove = XMMatrixTranslation(position_.x, position_.y, position_.z);//���_�ɂ��炷�s��
	XMVECTOR quadPos = XMLoadFloat3(&position_);
	quadPos = XMVector3TransformCoord(quadPos, matMove * matRotY);//�l�p�����_�ɂ��炵�Ă����]
	XMFLOAT3 f3Quad;
	XMStoreFloat3(&f3Quad, quadPos);

	XMVECTOR ActorPos = XMLoadFloat3(data.pCollider->position_);
	ActorPos = XMVector3TransformCoord(ActorPos, matMove * matRotY);//�~�̈ʒu�����炷
	XMFLOAT3 f3Actor;
	XMStoreFloat3(&f3Actor, ActorPos);
	using std::max;
	using std::min;
	using std::pow;
	XMFLOAT3 compare = {//�����蔻��̎l�p�̊O���ŁA�~�̒��S�ɍł��߂��n�_�����߂�
		{max(f3Quad.x - width_,min(f3Actor.x, f3Quad.x + width_))}
		,0//Y�͔��肢��Ȃ�
		,{max(f3Quad.z - length_, min(f3Actor.z, f3Quad.z + length_)) } };

	float dist = (float)sqrt(pow(compare.x - f3Actor.x, 2) + pow(compare.z - f3Actor.z, 2));
	float r = (float)pow(data.pActor->GetRadius(), 2);//�����Ə�̍s�s���A��
	return (dist < r);


}

XMVECTOR AttackRangeQuad::getDir(XMFLOAT3 pos)
{
	return XMVector3TransformCoord(XMVECTOR{ 0,0,1,0 }, XMMatrixRotationY(this->rotate_));

}


AttackRangeCirculerSector::AttackRangeCirculerSector() :AttackRangeBase()
{
	radius_ = -1;
	centerAngle_ = -1;
	rotate_ = 0;

	areatype_ = SECTOR;
}
AttackRangeCirculerSector::AttackRangeCirculerSector(XMFLOAT3 pos) :AttackRangeCirculerSector()
{
	position_ = pos;
}

bool AttackRangeCirculerSector::IsHit(actorAddr& data)
{
	XMFLOAT3 s = position_;
	s.y = 0;
	XMVECTOR sectorPos = XMLoadFloat3(&s);
	XMFLOAT3 a = *data.pCollider->position_;
	a.y = 0;
	XMVECTOR ActorPos = XMLoadFloat3(&a);
	if (XMVectorGetX(XMVector3Length(XMVectorAbs(sectorPos - ActorPos))) > radius_ + data.pActor->GetRadius())//�܂��͉~�Ɠ���
	{
		return false;
	}
	float radAngle = XMConvertToRadians(centerAngle_);//�J���
	float radRot = XMConvertToRadians(rotate_);//��̉�]
	XMMATRIX rotM = XMMatrixRotationY(radRot);
	XMVECTOR Front{ 0,0,1,0 };
	XMVECTOR rotFront = XMVector3TransformCoord(Front, rotM);//�����Ő�`�̉�]�
	//�p�x��(a�Eb)/|a||b|
	XMVECTOR sectorToActor = ActorPos - sectorPos;
	float deviation = XMVectorGetX(XMVector3AngleBetweenVectors(rotFront, sectorToActor));//�����Ő�̂ǂ̕ӂɂ��邩�p�x���o����͂�
	if (std::abs(deviation) > radAngle)//���S����̊O�Ȃ�
	{//�ǉ��Ō���
		XMMATRIX angleM = XMMatrixRotationY(radAngle);//�J���
		float a, b;
		a = (std::abs(XMVectorGetX(XMVector3AngleBetweenVectors(XMVector3TransformCoord(rotFront, angleM), sectorToActor))));//�Е��̒[
		b = std::abs(XMVectorGetX(XMVector3AngleBetweenVectors(XMVector3TransformCoord(rotFront, XMMatrixInverse(nullptr, angleM)), sectorToActor)));//�����Е��̒[�B��]�̋t�s��
		float close = std::min(a, b);//���[�����ċ߂��ق���rad

		float vecSin = XMVectorGetX(XMVector3Length(sectorToActor * std::sin(close)));
		if (vecSin > data.pActor->GetRadius())//����ł��͈͊O�Ȃ�
		{//�X���[
			return false;
		}
	}
	return true;

}

XMVECTOR AttackRangeCirculerSector::getDir(XMFLOAT3 pos)
{
	return  XMVector3Normalize(XMLoadFloat3(&pos) - XMLoadFloat3(&position_));
}



