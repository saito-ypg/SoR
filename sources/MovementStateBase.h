#pragma once
#include"../Engine/Transform.h"
class EnemyBase;
//�G�L�����N�^�[�̈�s�����`����
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
	bool CanTransitionOut() const;//���̃X�e�[�g�𗣂�邱�Ƃ��\�ł��邩
};

