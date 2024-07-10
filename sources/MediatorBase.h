#pragma once
#include<memory>
#include"MovementStateBase.h"

class EnemyBase;
/// <summary>
/// 敵の行動パターン(state)の切り替えや管理を行うクラス
/// 敵各種ごとに定義する
/// </summary>
class MediatorBase
{
protected:
	std::unique_ptr<MovementStateBase> curState_;
	EnemyBase& base_ ;
	bool isTransition_;

	virtual void DetermineNextState() = 0;
	virtual void changeState() = 0;

public:
	MediatorBase(EnemyBase& enemy);
	virtual ~MediatorBase();
	void Update(const float& dt);
	//void setEnemy(EnemyBase*enemy);

};

