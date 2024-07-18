#include "SoldierStates.h"
#include"EnemyBase.h"
#include"../Engine/Input.h"
#include<string>
namespace {
	constexpr float END_MOVE_THRESHOULD=4.0f;
	constexpr float MOVING_VELOCITY = 3.0f;
	const XMVECTOR FORWARD_VECTOR = XMVECTOR{ 0,0,1,0 };
}
SoldierStateMove::SoldierStateMove(EnemyBase& base) :MovementStateBase(base)
{
}

SoldierStateMove::~SoldierStateMove()
{
}

void SoldierStateMove::Update(const float& dt)
{
	auto targetPos = enemy_.GetTarget();
	XMVECTOR vTargetPos = XMLoadFloat3(&targetPos);
	XMFLOAT3 myPos = enemy_.GetPosition();
	XMVECTOR vMyPos = XMLoadFloat3(&myPos);
	XMVECTOR diffV = vTargetPos - vMyPos;
	XMVECTOR nDiff = XMVector3Normalize(diffV);
	enemy_.ForceMove( nDiff* (MOVING_VELOCITY/60));
	float dot = XMVectorGetX( XMVector3Dot(FORWARD_VECTOR, nDiff));
	float rot =XMConvertToDegrees( acos(dot));
	if (XMVectorGetX(XMVector3Cross(FORWARD_VECTOR,nDiff)) < 0) {
		rot -=180;
	}
	enemy_.SetRotateY(rot);
	if (Input::IsKeyDown(DIK_LALT)||XMVectorGetX(XMVector3Length(diffV))<=END_MOVE_THRESHOULD) {
		canTransition_ = true;
	}else {
		canTransition_ = false;
	}
	OutputDebugString(std::string("Target X:" + std::to_string(targetPos.x) + ", Z:" + std::to_string(targetPos.z) + "\n").c_str());

}

void SoldierStateMove::Release()
{
}
