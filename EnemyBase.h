#pragma once
#include "GameActor.h"

class EnemyBase : public GameActor
{
private:
	
protected:
	void AddCamp() override;
	void RemoveCamp() override;
public:
	EnemyBase(GameObject* parent);
	virtual ~EnemyBase();
	
	
};

