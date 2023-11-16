#pragma once
#include "GameActor.h"
class EnemyBase : public GameActor
{
private:



public:
	EnemyBase(GameObject* parent, string);
	virtual ~EnemyBase();
	
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	
};

