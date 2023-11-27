#pragma once
class Transform;
class AttackRangeBase
{
public:
	Transform transform;//中心位置。扇の場合は中心角の位置
	AttackRangeBase();
	virtual ~AttackRangeBase();
};

