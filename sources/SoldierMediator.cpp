#include "SoldierMediator.h"
#include<map>
#include<typeindex>
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
	states nextType;
	switch (curType) {
	case IDLE:
		nextType = MOVE;
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