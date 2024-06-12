#pragma once
#include "GameActor.h"
#include"EnemyType.h"
struct EnemyStatus {
	float hp;
	float radius;
};

class EnemyBase : public GameActor 
{
	
public:
	enum SPAWINIG_STATE { WAIT, IN_SPAWN, DEAD };
private:
	
protected:
	void AddCamp() override;
	void RemoveCamp() override;
	void dyingProcess()override;

	//スキル等を知る必要ないためPlayer型にはしない
	GameActor* pPlayer;
	SPAWINIG_STATE eStat_;//管理用
public:
	//EnemyBase(GameObject* parent);
	EnemyBase(GameObject* parent, EnemyType type, bool isboss = false);
	virtual ~EnemyBase();

	void SetPlayer(GameActor* p) { pPlayer = p; assert(pPlayer != nullptr); }
	void setConfig(EnemyStatus status);
	SPAWINIG_STATE getStat() const { return eStat_; }
	
	
	
};

