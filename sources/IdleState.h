#pragma once
#include "MovementStateBase.h"
class IdleState :public MovementStateBase {
public:
	IdleState(EnemyBase& enemy);
	~IdleState();
	void Update(const float& dt)override;
};