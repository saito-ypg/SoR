#pragma once
class ActorInfo
{
public:
	float hp_;
	float maxHp_;
	float hitCircleRange_;
	ActorInfo() :hp_(0), maxHp_(0), hitCircleRange_(0) {};
	ActorInfo(float maxHp, float range):hp_(maxHp),maxHp_(maxHp),hitCircleRange_(range){}
};

