#include "ChargeSkill.h"

ChargeSkill::ChargeSkill(Player* pPlayer):SkillBase(1.5f,4.0f,pPlayer)
{
	sequence={12,16,6};
	QuadArea.width_ =1.1f;
	QuadArea.length_ =4.0f;
}

ChargeSkill::~ChargeSkill()
{
}

void ChargeSkill::action()
{
	SwitchActionByStep();

}

void ChargeSkill::Draw()
{
}

void ChargeSkill::DrawRangeDisplay()
{
}

void ChargeSkill::Release()
{
}

void ChargeSkill::invokedStep(){

}
void ChargeSkill::startStep(){

}
void ChargeSkill::endStep(){

}
