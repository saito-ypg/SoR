#include "testSkill.h"

testSkill::testSkill():SkillBase(1.6f,5.0f)
{
	sequence = {20,40,20};
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
