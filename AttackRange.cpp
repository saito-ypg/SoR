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
	XMMATRIX matRotY = XMMatrixRotationY(XMConvertToRadians(rotate_));//回転してる四角を、回転の分だけ戻す行列
	XMMATRIX matMove = XMMatrixTranslation(position_.x, position_.y, position_.z);//原点にずらす行列
	XMVECTOR quadPos = XMLoadFloat3(&position_);
	quadPos = XMVector3TransformCoord(quadPos, matMove * matRotY);//四角を原点にずらしてから回転
	XMFLOAT3 f3Quad;
	XMStoreFloat3(&f3Quad, quadPos);

	XMVECTOR ActorPos = XMLoadFloat3(data.pCollider->position_);
	ActorPos = XMVector3TransformCoord(ActorPos, matMove * matRotY);//円の位置もずらす
	XMFLOAT3 f3Actor;
	XMStoreFloat3(&f3Actor, ActorPos);
	using std::max;
	using std::min;
	using std::pow;
	XMFLOAT3 compare = {//当たり判定の四角の外周で、円の中心に最も近い地点を求める
		{max(f3Quad.x - width_,min(f3Actor.x, f3Quad.x + width_))}
		,0//Yは判定いらない
		,{max(f3Quad.z - length_, min(f3Actor.z, f3Quad.z + length_)) } };

	float dist = (float)sqrt(pow(compare.x - f3Actor.x, 2) + pow(compare.z - f3Actor.z, 2));
	float r = (float)pow(data.pActor->GetRadius(), 2);//此処と上の行不安アル
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
	if (XMVectorGetX(XMVector3Length(XMVectorAbs(sectorPos - ActorPos))) > radius_ + data.pActor->GetRadius())//まずは円と同じ
	{
		return false;
	}
	float radAngle = XMConvertToRadians(centerAngle_);//開き具合
	float radRot = XMConvertToRadians(rotate_);//扇の回転
	XMMATRIX rotM = XMMatrixRotationY(radRot);
	XMVECTOR Front{ 0,0,1,0 };
	XMVECTOR rotFront = XMVector3TransformCoord(Front, rotM);//ここで扇形の回転具合
	//角度→(a・b)/|a||b|
	XMVECTOR sectorToActor = ActorPos - sectorPos;
	float deviation = XMVectorGetX(XMVector3AngleBetweenVectors(rotFront, sectorToActor));//ここで扇のどの辺にいるか角度が出せるはず
	if (std::abs(deviation) > radAngle)//中心が扇の外なら
	{//追加で検証
		XMMATRIX angleM = XMMatrixRotationY(radAngle);//開き具合
		float a, b;
		a = (std::abs(XMVectorGetX(XMVector3AngleBetweenVectors(XMVector3TransformCoord(rotFront, angleM), sectorToActor))));//片方の端
		b = std::abs(XMVectorGetX(XMVector3AngleBetweenVectors(XMVector3TransformCoord(rotFront, XMMatrixInverse(nullptr, angleM)), sectorToActor)));//もう片方の端。回転の逆行列
		float close = std::min(a, b);//両端を見て近いほうのrad

		float vecSin = XMVectorGetX(XMVector3Length(sectorToActor * std::sin(close)));
		if (vecSin > data.pActor->GetRadius())//それでも範囲外なら
		{//スルー
			return false;
		}
	}
	return true;

}

XMVECTOR AttackRangeCirculerSector::getDir(XMFLOAT3 pos)
{
	return  XMVector3Normalize(XMLoadFloat3(&pos) - XMLoadFloat3(&position_));
}



