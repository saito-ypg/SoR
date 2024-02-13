#pragma once
#include<list>
#include"GameActor.h"
class EnemyBase;
//敵をまとめて管理するクラス
//スポーンさせるクラスが別にいてほしいな～
class EnemyManager :public GameObject {
private:

public:
	EnemyManager(GameObject* parent);
	~EnemyManager();
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void Release()override;
	std::list<EnemyBase*> Enemylist_;

	void add(EnemyBase* enemy);//listに敵を登録。引数にInstantiateとか必要かな




};