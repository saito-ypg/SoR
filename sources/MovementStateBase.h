#pragma once
#include"../Engine/Transform.h"
class GameActor;
class MovementStateBase
{
protected:
	Transform* enemyTransform_;
	
public:
	MovementStateBase(GameActor* pActor);
	virtual void SetTransform(Transform* t);
	virtual ~MovementStateBase();
	virtual void Update(XMFLOAT3 pos);
	virtual void Release();
};

