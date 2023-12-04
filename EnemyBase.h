#pragma once
#include "GameActor.h"

class EnemyBase : public GameActor
{
private:
	
protected:
	void AddCamp() override;
public:
	EnemyBase(GameObject* parent);
	virtual ~EnemyBase();
	
	
};

