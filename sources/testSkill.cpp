#include "testSkill.h"
#include"../Engine/Model.h"
testSkill::testSkill():SkillBase(0.5f,1.0f)
{
	sequence = { 1,5,1 };
	circle.radius_ = 2;
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
		if (steptime == sequence.at(START_ATTACK))
		{

			circle.position_ = this->transform_.position_;
			DamageData dmg;
			dmg.damage_ = 20;
			dmg.knockback_ = 4;
			dmg.duration_ = 1;
			RegisterHitRange(circle, dmg);
		}
		break;
	case END_ATTACK:
		break;


	}
}

void testSkill::Draw()
{
}

void testSkill::Release()
{
}

void testSkill::DrawRangeDisplay(Transform tr)
{
	int handle = area(CIRCLE);
	Transform DrawT = tr;
	const float r = circle.radius_;
	DrawT.scale_ = {r ,r ,r };
	Model::SetTransform(handle, DrawT);
	Model::Draw(handle);
}
