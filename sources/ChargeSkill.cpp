#include<cmath>
#include "ChargeSkill.h"
#include"../Engine/Model.h"
#include"Player.h"
namespace {
	float INOUTEXPO(float t) {//ŽžŠÔ‚É‘Î‚µˆÊ’u‚ð•Ô‚·
		return t == 0.0f
			? 0.0f 
			: t >= 1.0f
				? 1.0f
				: t < 0.5f
					? (float)(std::pow(2, 20 * t - 10)) / 2
					: (2 - (float)(std::pow(2, -20 * t + 10))) / 2;
	}
	AttackRangeQuad QuadArea;
	XMVECTOR forward = XMVectorZero();
	XMVECTOR lastForceVec = XMVectorZero();
}
ChargeSkill::ChargeSkill(Player* pPlayer):SkillBase(ConvToFrames(1.0f), ConvToFrames(1.0f), pPlayer, "charge.png")
{
	sequence={12,28,6};
	QuadArea.width_ =1.1f;
	QuadArea.length_ =6.0f;
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
	int handle = area(QUAD);
	Transform DrawT = GetPlayerTransform();
	DrawT.scale_ = { QuadArea.width_ ,1,QuadArea.length_ };
	DrawT.rotate_.y = fmodf(deg, 360.0f);
	XMVECTOR vpos = XMLoadFloat3(&DrawT.position_);
	XMVECTOR OffsetCentor = XMVectorSet(0, 0,QuadArea.length_, 0);//‰ñ“]‘O
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
	//ˆÚ“®—Ê‚ðo‚·
	const float& flames = sequence.at(START_ATTACK);
	float nowTime =(float)(-(steptime)+flames+1)/flames;
	XMVECTOR forcevec = forward * INOUTEXPO(nowTime) * QuadArea.length_*2;
	pPlayer_->ForceMove(forcevec-lastForceVec);
	if (isStepChanged)
	{
		DamageData dmg;
		

		RegisterHitRange(QuadArea,dmg);
	}
	lastForceVec = forcevec;
}
void ChargeSkill::endStep(){

}

void ChargeSkill::ResetInheritedSkillMembers()
{
	lastForceVec = XMVectorZero();
}
