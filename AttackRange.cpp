#include "AttackRange.h"
AttackRangeBase::AttackRangeBase():areatype_(NONE),a_(-1),b_(-1),c_(0)
{
}
AttackRangeBase::AttackRangeBase(XMFLOAT3 pos):AttackRangeBase()
{
	position_ = pos;
}

AttackRangeCircle::AttackRangeCircle():AttackRangeBase()
{
	radius_ = -1;
	areatype_ = CIRCLE;
}

AttackRangeCircle::AttackRangeCircle(XMFLOAT3 pos):AttackRangeCircle()
{
	position_ = pos;
}

AttackRangeQuad::AttackRangeQuad():AttackRangeBase()
{
	width_ = -1;
	length_ = -1;
	rotate_ = 0;

	areatype_ =QUAD;
}

AttackRangeQuad::AttackRangeQuad(XMFLOAT3 pos) :AttackRangeQuad()
{
	position_ = pos;
}


AttackRangeCirculerSector::AttackRangeCirculerSector():AttackRangeBase()
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


