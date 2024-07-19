#pragma once
#include "MediatorBase.h"
#include"MediatorFactory.h"
class DecoyMediator :public MediatorBase
{
private:
	void DetermineNextState() override;
public:
	DecoyMediator(EnemyBase& enemy);
	~DecoyMediator();
};

class DecoyMediatorFactory :public MediatorFactory 
{
public:
	std::unique_ptr<MediatorBase> createMediator(EnemyBase& enemy) override
	{
		return std::make_unique<DecoyMediator>(enemy);
	}
};

