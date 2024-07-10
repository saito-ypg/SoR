#pragma once

#include<memory>
#include "GameActor.h"
#include"EnemyType.h"
#include"MediatorBase.h"
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
//スキル等を知る必要ないためPlayer型にはしない
	bool isBoss_;
	GameActor* pPlayer_;
	SPAWINIG_STATE eStat_;//管理用


	std::unique_ptr<MediatorBase> pMediator_; //このクラスを通し各行動ステートの管理

	///ステートと情報をやり取りし敵に行動させる
	///もしmediatorがnullなら行動しないキャラとなる
	void mediatorUpdate(const float&dt);
	void AddCamp() override;
	void RemoveCamp() override;
	void dyingProcess()override;

	
public:
	//EnemyBase(GameObject* parent);
	EnemyBase(GameObject* parent, bool isboss = false);
	virtual ~EnemyBase();


	void SetPlayer(GameActor* p) { pPlayer_ = p; assert(pPlayer_ != nullptr); }
	void SetMediator(std::unique_ptr<MediatorBase>mediator);//ステートを管理するメディエーターを設定
	//敵のデータを設定する
	void setConfig(const EnemyStatus & status);
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