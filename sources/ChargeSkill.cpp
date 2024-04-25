#include<cmath>
#include "ChargeSkill.h"
#include"../Engine/Model.h"
#include"Player.h"
namespace {
	float INOUTEXPO(float t) {//ŽžŠÔ‚É‘Î‚µˆÊ’u‚ð•Ô‚·
		return t == 0
			? 0
			: t == 1
			? 1
			: t < 0.5 ? std::pow(2, 20 * t - 10) / 2
			: (2 - std::pow(2, -20 * t + 10)) / 2;
	}
}
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
	

}
void ChargeSkill::endStep(){

}
