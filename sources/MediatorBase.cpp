#include "MediatorBase.h"
#include"EnemyBase.h"
#include"IdleState.h"
MediatorBase::MediatorBase(EnemyBase& enemy) :base_(enemy)
{
	curState_ = std::make_unique<IdleState>(enemy);
}

MediatorBase::~MediatorBase()
{
}

void MediatorBase::Update(const float& dt)
{
	curState_->Update(dt);
	SkipDeterminingMs -= dt;
	if (SkipDeterminingMs<=0&& curState_->CanTransitionOut()) {//�����̏����Atrue�Ȃ疈�񔻒f�������Ⴄ�����莞�ԋ󂯂��ق������������H
		DetermineNextState();
		SkipDeterminingMs = rand() % 4000 + 1000;//�~���b�P��,�K��
	}
}

const std::type_info& MediatorBase::getCurStateType() const
{
	return typeid(*curState_);
}
