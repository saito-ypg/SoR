#pragma once
#include"../Engine/Transform.h"
class EnemyBase;
//�G�L�����N�^�[�̈�s�����`����
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

