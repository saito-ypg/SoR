#pragma once
#include"../Engine/Transform.h"
class EnemyBase;
//�G�L�����N�^�[�̈�s�����`����
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

