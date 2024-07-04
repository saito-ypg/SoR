#pragma once
#include"../Engine/Transform.h"
class GameActor;
//�G�L�����N�^�[�̈�s�����`����
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

