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

		break;
	case START_ATTACK:
		break;

	case END_ATTACK:

		break;


	}
}

void testSkill::Draw()
{
}
