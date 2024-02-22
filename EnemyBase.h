#pragma once
#include "GameActor.h"

class EnemyBase : public GameActor 
{
public:
	enum STATE { WAIT, IN_SPAWN, DEAD };
private:
	
protected:
	void AddCamp() override;
	void RemoveCamp() override;
	
	STATE eStat_;//ä«óùóp
public:
	STATE getStat() { return eStat_; }
	EnemyBase(GameObject* parent);
	EnemyBase(GameObject* parent, bool isboss);
	virtual ~EnemyBase();
	
	
};

