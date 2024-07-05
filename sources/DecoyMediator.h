#pragma once
#include "MediatorBase.h"
#include"MediatorFactory.h"
class DecoyMediator :public MediatorBase
{
private:
	void changeState()override;
	void DetermineNextState() override;
public:
	DecoyMediator();
	virtual ~DecoyMediator();
};

class DecoyMediatorFactory :public MediatorFactory {
	std::unique_ptr<MediatorBase> createMediator() override
	{
		return std::make_unique<DecoyMediator>();
	}
};

