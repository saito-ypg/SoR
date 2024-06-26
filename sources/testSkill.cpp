#include "testSkill.h"
#include"../Engine/Model.h"
#include"Player.h"
namespace {
	DamageData dmg;
	AttackRangeCircle circle;
}
testSkill::testSkill(Player* pPlayer):SkillBase(ConvToFrames(0.5f),3,pPlayer,"spinicon.png")
{
	sequence = { 1,5,1 };
	circle.radius_ = 2;
	dmg.damage_ = 20;
	dmg.knockback_ = 4;
	dmg.duration_ = 1;
}

testSkill::~testSkill()
{
}

void testSkill::action()
{
	SwitchActionByStep();
}

void testSkill::Draw()
{
}

void testSkill::Release()
{
}

void testSkill::DrawRangeDisplay(float deg)
{
	int handle = area(CIRCLE);
	Transform DrawT =GetPlayerTransform();
	const float r = circle.radius_;
	DrawT.scale_ = {r ,r ,r };
	Model::SetTransform(handle, DrawT);
	Model::Draw(handle);
}

void testSkill::invokedStep() {


}
void testSkill::startStep() {

	if (isStepChanged)
	{
		circle.position_ = this->beginTransform_.position_;
		
		RegisterHitRange(circle, dmg);
	}
}
void testSkill::endStep() {


}