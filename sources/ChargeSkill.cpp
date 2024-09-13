#include<cmath>
#include "ChargeSkill.h"
#include"Engine/Model.h"
#include"Player.h"
#include"Engine/Ease.h"
namespace {
	AttackRangeQuad QuadArea;
	XMVECTOR forward = XMVectorZero();

}
ChargeSkill::ChargeSkill(Player* pPlayer):SkillBase(1000, 2800, pPlayer, "charge.png")
{
	sequence={ConvFrameToMs(12),ConvFrameToMs(28),ConvFrameToMs(6)};
	QuadArea.width_ =1.1f;
	QuadArea.length_ =6.0f;
	lastForceVec = XMVectorZero();
}

ChargeSkill::~ChargeSkill()
{
}

void ChargeSkill::action()
{
	forward = XMVector3TransformCoord(XMVectorSet(0, 0, 1, 0), XMMatrixRotationY(XMConvertToRadians(beginTransform_.rotate_.y)));
	SwitchActionByStep();
}

void ChargeSkill::Draw()
{
}

void ChargeSkill::DrawRangeDisplay(float deg)
{
	const int handle = area(QUAD);
	Transform DrawT = GetPlayerTransform();
	DrawT.scale_ = { QuadArea.width_ ,1,QuadArea.length_ };
	DrawT.rotate_.y = fmodf(deg, 360.0f);
	const XMVECTOR vpos = XMLoadFloat3(&DrawT.position_);
	XMVECTOR OffsetCentor = XMVectorSet(0, 0,QuadArea.length_, 0);//âÒì]ëO
	OffsetCentor = XMVector3TransformCoord(OffsetCentor,XMMatrixRotationY(XMConvertToRadians(DrawT.rotate_.y)));
	XMStoreFloat3(&DrawT.position_, vpos+OffsetCentor);
	Model::SetTransform(handle, DrawT);
	Model::Draw(handle);
}

void ChargeSkill::Release()
{
}

void ChargeSkill::invokedStep(){

}
void ChargeSkill::startStep(){
	using enum EASE::easeType;
	//à⁄ìÆó ÇèoÇ∑
	const float& flames = sequence.at(START_ATTACK);
	const float nowTime =static_cast<float>(-(steptime)+flames+1)/flames;
	const XMVECTOR forceVec = forward * static_cast<float>(EASE::easing(InOutExpo,nowTime) )* QuadArea.length_ * 2;
	pPlayer_->ForceMove(forceVec-lastForceVec);
	if (isStepChanged)
	{
		DamageData dmg;
		dmg.damage_ = 123;
		dmg.duration_ = ConvFrameToMs(28);
		dmg.knockback_ = 6;
		RegisterHitRange(QuadArea, dmg, [](AttackRangeBase* range,float dt){
			
			});
	}
	lastForceVec = forceVec;
}
void ChargeSkill::endStep(){

}

void ChargeSkill::ResetInheritedSkillMembers()
{
	lastForceVec = XMVectorZero();
}
