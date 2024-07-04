#pragma once
#include<memory>
class MovementStateBase;
class EnemyBase;

/// <summary>
/// 敵の行動パターン(state)の切り替えや管理を行うクラス
/// 敵各種ごとに定義する
/// </summary>
class MediatorBase
{
protected:
	std::unique_ptr<MovementStateBase> curState;
	EnemyBase* base;
public:
	MediatorBase(EnemyBase* enemy);
	virtual ~MediatorBase();
	void Update(const float& dt);

	virtual void changeState() = 0;
};

