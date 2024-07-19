#include "IdleState.h"
#include"../Engine/Input.h"
IdleState::IdleState(EnemyBase&enemy) :MovementStateBase(enemy)
{

}

IdleState::~IdleState()
{
}

void IdleState::Update(const float& dt)
{
	canTransition_ = true;
}
