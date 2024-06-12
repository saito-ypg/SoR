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

	//�X�L������m��K�v�Ȃ�����Player�^�ɂ͂��Ȃ�
	GameActor* pPlayer;
	SPAWINIG_STATE eStat_;//�Ǘ��p
public:
	//EnemyBase(GameObject* parent);
	EnemyBase(GameObject* parent, EnemyType type, bool isboss = false);
	virtual ~EnemyBase();

	void SetPlayer(GameActor* p) { pPlayer = p; assert(pPlayer != nullptr); }
	void setConfig(EnemyStatus status);
	SPAWINIG_STATE getStat() const { return eStat_; }
	
	
	
};

