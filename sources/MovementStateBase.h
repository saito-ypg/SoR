#pragma once
#include"../Engine/Transform.h"
class EnemyBase;
//敵キャラクターの一行動を定義する
class MovementStateBase
{
protected:
	Transform* enemyTransform_;
	EnemyBase& enemy_;
public:
	MovementStateBase(EnemyBase&pEnemy);
	virtual void SetTransform(Transform* t);
	virtual ~MovementStateBase();
	virtual void Update(const float&dt);
	virtual void Release();
};

