#pragma once
#include<memory>
#include"MovementStateBase.h"

class EnemyBase;
/// <summary>
/// �G�̍s���p�^�[��(state)�̐؂�ւ���Ǘ����s���N���X
/// �G�e�킲�Ƃɒ�`����
/// </summary>
class MediatorBase
{
protected:
	std::unique_ptr<MovementStateBase> curState_;
	EnemyBase& base_ ;
	bool isTransition_;

	virtual void DetermineNextState() = 0;
	virtual void changeState() = 0;

public:
	MediatorBase(EnemyBase& enemy);
	virtual ~MediatorBase();
	void Update(const float& dt);
	//void setEnemy(EnemyBase*enemy);

};

