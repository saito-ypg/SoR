#pragma once
#include<list>
#include"GameActor.h"
#include<utility>
class EnemyBase;
//敵をまとめて管理するクラス
//スポーンさせるクラスが別にいてほしいな～
class EnemyManager {
private:

public:
	EnemyManager(GameObject* parent);
	~EnemyManager();
	void Initialize();
	void Update(const float& dt);
	void Draw();
	void Release();
	std::vector<EnemyBase*> Enemylist_;

	void add(EnemyBase* enemy);//listに敵を登録。引数にInstantiateとか必要かな




};