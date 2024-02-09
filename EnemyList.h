#pragma once
#include<list>
#include"EnemyList.h"
#include"GameActor.h"
class EnemyBase;
//敵をまとめて管理するクラス
//スポーンさせるクラスが別にいてほしいな〜
class EnemyList:public GameObject{
private:

public:
	EnemyList(GameObject* parent);
	~EnemyList();
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void Release()override;
	std::list<EnemyBase*> Enemylist;

	void add(EnemyBase*enemy);//listに敵を登録
	

	

}