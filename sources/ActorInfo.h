#pragma once
class ActorInfo
{
public:
	float hp_;
	float maxHp_;
	float hitCircleRange_;//半径
	ActorInfo() :hp_(0), maxHp_(0), hitCircleRange_(0) {};
	/// <summary>
	/// アクターの基礎情報
	/// </summary>
	/// <param name="maxHp">最大HP</param>
	/// <param name="range">当たり判定の円の半径</param>
	ActorInfo(float maxHp, float range):hp_(maxHp),maxHp_(maxHp),hitCircleRange_(range){}
};

