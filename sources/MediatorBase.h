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
	std::unique_ptr<MovementStateBase> curState_;//���݂̃X�e�[�g
	EnemyBase& base_ ;
	int SkipDeterminingMs;//�������f��ɑJ�ڂ��Ȃ������炱�̃J�E���g��0�ȉ��ɂȂ�܂Ŏ��̔��f�������Ȃ�Ȃ�
	/// <summary>
	/// ���̃X�e�[�g�̑J�ڐ�𔻒f����B
	/// ���������X�e�[�g�Ȃ炻�̂܂܁A�ς���Ă���Ȃ�ChangeState���Ă�
	/// </summary>
	virtual void DetermineNextState() = 0;

	/// <summary>
	/// ���̃X�e�[�g���C���X�^���X������
	/// </summary>
	template<class T>
	void ChangeState() {
		static_assert(std::is_base_of_v<MovementStateBase, T>, "�X�e�[�g�N���X���p�����Ă��܂���");
		static_assert(!std::is_abstract_v<T>, "���ۃN���X�ł��I");
		curState_ = std::make_unique<T>(base_);
	}

public:
	MediatorBase(EnemyBase& enemy);
	virtual ~MediatorBase();
	void Update(const float& dt);
	const std::type_info& getCurStateType()const;
};

