#pragma once
#include<memory>
class MovementStateBase;
class EnemyBase;

/// <summary>
/// �G�̍s���p�^�[��(state)�̐؂�ւ���Ǘ����s���N���X
/// �G�e�킲�Ƃɒ�`����
/// </summary>
class MediatorBase
{
protected:
	std::unique_ptr<MovementStateBase> curState;
	EnemyBase* base;
public:
	MediatorBase(EnemyBase* enemy);
	virtual ~MediatorBase();
	void Update(const float& dt);

	virtual void changeState() = 0;
};

