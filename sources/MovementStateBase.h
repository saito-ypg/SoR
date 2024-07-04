#pragma once
#include"../Engine/Transform.h"
class GameActor;
//敵キャラクターの一行動を定義する
class MovementStateBase
{
protected:
	Transform* enemyTransform_;
	
public:
	MovementStateBase(GameActor* pActor);
	virtual void SetTransform(Transform* t);
	virtual ~MovementStateBase();
	virtual void Update(const float&dt);
	virtual void Release();
};

