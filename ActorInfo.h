#pragma once
class ActorInfo
{
public:
	int hp_;
	float hitCircleRange_;
	ActorInfo() { hp_ = 0; hitCircleRange_ = 0; }
	ActorInfo(int hp, float range):hp_(hp),hitCircleRange_(range){}
};

