#pragma once
#include"../Engine/Transform.h"
class MovementStateBase
{
protected:
	Transform* enemyTransform_;
public:
	MovementStateBase();
	virtual void SetTransform(Transform* t);
	virtual ~MovementStateBase();
	virtual void Update(XMFLOAT3 pos);
	virtual void Release();
};

