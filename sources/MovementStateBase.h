#pragma once
#include"../Engine/Transform.h"
class EnemyBase;
//敵キャラクターの一行動を定義する
class MovementStateBase
{
protected:
	bool canTransition_;
	EnemyBase& enemy_;

public:
	MovementStateBase(EnemyBase&pEnemy);
	virtual ~MovementStateBase();
	virtual void Update(const float&dt);
	virtual void Release();
	bool CanTransitionOut() const;//このステートを離れることも可能であるか
};

