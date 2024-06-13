#pragma once
#include "GameActor.h"
#include"EnemyType.h"
struct EnemyStatus {
	float hp;
	float radius;
};
class MovementStateBase;
class EnemyBase : public GameActor 
{
	
public:
	enum SPAWINIG_STATE { WAIT, IN_SPAWN, DEAD };
private:
	



protected:
//スキル等を知る必要ないためPlayer型にはしない
	GameActor* pPlayer;
	SPAWINIG_STATE eStat_;//管理用

	MovementStateBase* curMovement;
	template<class st, typename = std::enable_if_t<std::is_base_of_v<MovementStateBase, st>>>
	void TransitionClass() {
		if (curMovement) {
			delete curMovement;
			curMovement = nullptr;
		}
		curMovement = new st();
		curMovement.SetTransform(this->GetTransformRef());
	}
	
	void AddCamp() override;
	void RemoveCamp() override;
	void dyingProcess()override;

	
public:
	//EnemyBase(GameObject* parent);
	EnemyBase(GameObject* parent, EnemyType type, bool isboss = false);
	virtual ~EnemyBase();

	void SetPlayer(GameActor* p) { pPlayer = p; assert(pPlayer != nullptr); }
	void setConfig(EnemyStatus status);
	SPAWINIG_STATE getStat() const { return eStat_; }
	
	
	
};

