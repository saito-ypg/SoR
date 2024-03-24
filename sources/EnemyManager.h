#pragma once
#include<list>
#include"GameActor.h"
#include<utility>
class EnemyBase;
//敵をまとめて管理するクラス
//スポーンさせるクラスが別にいてほしいな～
class EnemyManager {
private:
	std::vector<EnemyBase*> Enemylist_;
public:
	EnemyManager(GameObject* parent);
	~EnemyManager();
	void Initialize();
	void Update(const float& dt);
	void Draw();
	void Release();
	

	void add(EnemyBase* enemy);//listに敵を登録。引数にInstantiateとか必要かな
	bool Eliminated();

};