#pragma once
#include "GameActor.h"

class EnemyBase : public GameActor 
{
private:
	
protected:
	void AddCamp() override;
	void RemoveCamp() override;
	
	enum STATE { WAIT, IN_SPAWN }eStat_;//ä«óùóp
public:
	STATE getStat() { return eStat_; }
	EnemyBase(GameObject* parent);
	virtual ~EnemyBase();
	
	
};

