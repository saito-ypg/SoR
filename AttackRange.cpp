#include "AttackRange.h"

AttackRangeBase::AttackRangeBase(XMFLOAT3 pos):position_(pos)
{
}

AttackRangeCircle::AttackRangeCircle(XMFLOAT3 pos):AttackRangeBase(pos)
{
	radius_ = -1;
}

AttackRangeQuad::AttackRangeQuad(XMFLOAT3 pos) :AttackRangeBase(pos)
{
	width_ = -1;
	length_ = -1;
	rotate_ = -1;
}

AttackRangeCirculerSctor::AttackRangeCirculerSctor(XMFLOAT3 pos) :AttackRangeBase(pos)
{
	radius_ = -1;
	centerAngle_ = -1;
	rotate_ = -1;
}

