#include<cmath>
#include "ChargeSkill.h"
#include"../Engine/Model.h"
#include"Player.h"
namespace {
	float INOUTEXPO(float t) {//時間に対し位置を返す
		return t == 0
			? 0 
			: t >= 1
				? 1
				: t < 0.5 ? std::pow(2, 20 * t - 10) / 2
				: (2 - std::pow(2, -20 * t + 10)) / 2;
	}

	XMVECTOR forward = XMVectorZero();
	XMVECTOR lastForceVec = XMVectorZero();
}
ChargeSkill::ChargeSkill(Player* pPlayer):SkillBase(32,ConvToFrames(1.0f),pPlayer)
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
	//移動量を出す
	//16->0
	//15->1
	const float& flames = sequence.at(START_ATTACK);
	float nowTime =(float)(steptime*-1+flames+1)/flames;
	XMVECTOR forcevec = forward * INOUTEXPO(nowTime) * QuadArea.length_*2;
	pPlayer_->ForceMove(forcevec-lastForceVec);
	lastForceVec = forcevec;
}
void ChargeSkill::endStep(){

}

void ChargeSkill::ResetInheritedSkillMembers()
{
	lastForceVec = XMVectorZero();
}
