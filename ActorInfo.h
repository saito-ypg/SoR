#pragma once
class ActorInfo
{
public:
	int hp_;
	int maxHp_;
	float hitCircleRange_;
	ActorInfo() :hp_(0), maxHp_(0), hitCircleRange_(0) {};
	ActorInfo(int maxHp, float range):hp_(maxHp),maxHp_(maxHp),hitCircleRange_(range){}
};

