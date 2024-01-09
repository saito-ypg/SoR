#include "AttackRange.h"
AttackRangeBase::AttackRangeBase(XMFLOAT3 pos):position_(pos),areatype_(NONE),a_(-1),b_(-1),c_(0)
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
	rotate_ = 0;
}

AttackRangeCirculerSector::AttackRangeCirculerSector(XMFLOAT3 pos) :AttackRangeBase(pos)
{
	radius_ = -1;
	centerAngle_ = -1;
	rotate_ = 0;
}

