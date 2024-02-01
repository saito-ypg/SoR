#include "testSkill.h"

testSkill::testSkill():SkillBase(0.5f,1.0f)
{
	sequence = {1,5,1};
	
}

testSkill::~testSkill()
{
}


void testSkill::action()
{
	switch (stepindex)
	{
	case INVOKED:
//		__debugbreak();
		break;
	case START_ATTACK:
		if (steptime == sequence.at(START_ATTACK))
		{
			AttackRangeCircle circle;
			circle.Duration = 1;
			circle.radius_ = 2;
			circle.position_ = this->transform_.position_;
			DamageData dmg;
			dmg.damage_ = 20;
			dmg.knockback_ = 1;
			RegisterHitRange(circle, dmg);
		}
//		__debugbreak();
		break;

	case END_ATTACK:
//		__debugbreak();
		break;


	}
}

void testSkill::Draw()
{
}

void testSkill::Release()
{
}
