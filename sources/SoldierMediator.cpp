#include "SoldierMediator.h"
#include<map>
#include<typeindex>
#include"EnemyBase.h"
#include"IdleState.h"
#include"SoldierStates.h"
namespace {
	enum class states {
		IDLE,
		MOVE,

	};
	using enum states;
	const std::map<std::type_index, states> stateMap{
		{typeid(IdleState),IDLE },
		{typeid(SoldierStateMove),MOVE}
	};
}
SoldierMediator::SoldierMediator(EnemyBase& enemy):MediatorBase(enemy)
{
}

SoldierMediator::~SoldierMediator()
{
}


void SoldierMediator::DetermineNextState()
{
	auto curType = stateMap.at(getCurStateType());
	states nextType=curType;
	switch (curType) {
	case IDLE:
		auto basePos = base_.GetPosition();
		auto targetPos = base_.GetTarget();

		XMVECTOR diff= XMLoadFloat3(&basePos) - XMLoadFloat3(&targetPos);
		if (XMVectorGetX(XMVector3Length(diff)) > END_MOVE_THRESHOULD) {//現在の距離が移動ステートの移動終了距離よりも離れていたら
			nextType = MOVE;
		}
		break;
	case MOVE:
		nextType = IDLE;
		break;
	default:
		nextType = IDLE;
	}
	if (curType != nextType) {
		switch (nextType) {
		case IDLE:
			ChangeState<IdleState>(); break;
		case MOVE:
			ChangeState<SoldierStateMove>(); break;
			
		}
	}
}