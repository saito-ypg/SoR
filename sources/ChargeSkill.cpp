
#include "ChargeSkill.h"
#include<cmath>
#include"Engine/Model.h"
#include"Engine/Ease.h"
#include"Engine/Debug.h"
#include"Player.h"
namespace {
	AttackRangeQuad QuadArea;
	XMVECTOR forward = XMVectorZero();

}
ChargeSkill::ChargeSkill(Player* pPlayer):SkillBase(1000, 1, pPlayer, "charge.png")
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
	XMVECTOR OffsetCentor = XMVectorSet(0, 0,QuadArea.length_, 0);//回転前
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
	//移動量を出す
	const float& flames = sequence.at(START_ATTACK);
	const float nowTime =static_cast<float>(-(steptime)+flames+1)/flames;
	const XMVECTOR forceVec = forward * static_cast<float>(EASE::easing(InOutExpo,nowTime) )* QuadArea.length_ * 2;
	pPlayer_->ForceMove(forceVec-lastForceVec);
	if (isStepChanged)
	{
		AttackRangeQuad registration(QuadArea);//コピー
		registration.position_ = this->beginTransform_.position_;
		registration.length_ = 1.0f;
		registration.rotate_ = this->beginTransform_.rotate_.y;
		DamageData dmg(1, ConvFrameToMs(28), 6);

		//RegisterHitRange(AttackRangeQuad(registration), dmg, [&](RangeData& range, float dt) {
		//	const auto& maxDur = range.dmg_.maxDuration_;
		//	const auto& dur = range.dmg_.duration_;
		//	const float easeVal = static_cast<float>(EASE::easing(InOutExpo, static_cast<float>((maxDur - dur) / maxDur)));
		//	auto quad=dynamic_cast<AttackRangeQuad*>(range.pRange_);
		//	// 初期位置
		//	XMFLOAT3 beginPosition = beginTransform_.position_ ;
		//	// 回転角度をラジアンに変換
		//	float rotationRad = XMConvertToRadians(registration.rotate_);
		//	// 移動距離
		//	float distance = QuadArea.length_ * easeVal;

		//	// 新しい位置を計算
		//	XMVECTOR direction = XMVectorSet(cos(rotationRad),0.0f, sin(rotationRad),  0.0f);
		//	XMVECTOR beginPosVec = XMLoadFloat3(&beginPosition);
		//	XMVECTOR newPosVec = XMVectorAdd(beginPosVec, XMVectorScale(direction, distance));

		//	// 新しい位置を XMFLOAT3 に保存
		//	XMStoreFloat3(&quad->position_, newPosVec);
		//	//Debug::Log("X="+)
		//});
	}
	lastForceVec = forceVec;
}
void ChargeSkill::endStep(){

}

void ChargeSkill::ResetInheritedSkillMembers()
{
	lastForceVec = XMVectorZero();
}
