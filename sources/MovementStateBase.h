#pragma once
#include"../Engine/Transform.h"
class EnemyBase;
//敵キャラクターの一行動を定義する
class MovementStateBase
{
protected:
	EnemyBase& enemy_;
public:
	MovementStateBase(EnemyBase&pEnemy);
	virtual ~MovementStateBase();
	virtual void Update(const float&dt);
	virtual void Release();
};

