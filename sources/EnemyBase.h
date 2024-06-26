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
	bool isBoss_;
	GameActor* pPlayer;
	SPAWINIG_STATE eStat_;//管理用

	MovementStateBase* curMovement;

	//enemyの行動パターンの切り替え・ステートパターン
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
	EnemyBase(GameObject* parent, bool isboss = false);
	virtual ~EnemyBase();

	void SetPlayer(GameActor* p) { pPlayer = p; assert(pPlayer != nullptr); }

	//敵のデータを設定する
	void setConfig(EnemyStatus status);
	SPAWINIG_STATE getStat() const { return eStat_; }
	
	
};

//敵キャラ専用Instantiate ボス化情報を含む
//基本的にはGameObjectのものに則ったもの
template <class E, typename = std::enable_if_t<std::is_base_of_v<EnemyBase, E>>>
E* InstantiateEnemy(GameObject* pParent, bool isBoss)
{
	E* pNewObject = new E(pParent, isBoss);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->Initialize();
	return pNewObject;
}