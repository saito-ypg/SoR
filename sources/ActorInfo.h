#pragma once
class ActorInfo
{
public:
	float hp_;
	float maxHp_;
	float hitCircleRange_;//¼a
	ActorInfo() :hp_(0), maxHp_(0), hitCircleRange_(0) {};
	/// <summary>
	/// AN^[Ìîbîñ
	/// </summary>
	/// <param name="maxHp">ÅåHP</param>
	/// <param name="range">½è»èÌ~Ì¼a</param>
	ActorInfo(float maxHp, float range):hp_(maxHp),maxHp_(maxHp),hitCircleRange_(range){}
};

