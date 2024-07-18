#include "SoldierStates.h"
#include"EnemyBase.h"
#include"../Engine/Input.h"
#include<string>
namespace {
	constexpr float END_MOVE_THRESHOULD=4.0f;
	constexpr float MOVING_VELOCITY = 3.0f;
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
	XMVECTOR distPos = vTargetPos - vMyPos;
	enemy_.ForceMove(XMVector3Normalize(distPos) * (MOVING_VELOCITY/60));
	if (Input::IsKeyDown(DIK_LALT)||XMVectorGetX(XMVector3Length(distPos))<=END_MOVE_THRESHOULD) {
		canTransition_ = true;
	}
	else {
		canTransition_ = false;
	}
	OutputDebugString(std::string("Target X:" + std::to_string(targetPos.x) + ", Z:" + std::to_string(targetPos.z) + "\n").c_str());

}

void SoldierStateMove::Release()
{
}
