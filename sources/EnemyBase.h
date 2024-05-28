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
	void dyingProcess()override;

	//スキル等を知る必要ないためPlayerにはしない
	GameActor* pPlayer;
	STATE eStat_;//管理用
public:
	EnemyBase(GameObject* parent);
	EnemyBase(GameObject* parent, bool isboss);
	virtual ~EnemyBase();

	void SetPlayer(GameActor* p) { pPlayer = p; assert(pPlayer != nullptr); }
	STATE getStat() const { return eStat_; }
	
	
	
};

