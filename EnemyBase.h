#pragma once
#include "GameActor.h"
class EnemyBase : public GameActor
{
private:



public:
	EnemyBase(GameObject* parent);
	virtual ~EnemyBase();
	
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual	void Release() override;
	
};

