#pragma once
#include<list>
#include"EnemyList.h"
class EnemyBase;
//敵をまとめて管理するクラス
//現段階では未使用
namespace Enemy
{
	std::list<EnemyBase*> Enemylist;

	void add(EnemyBase*enemy);//listに敵を登録
	

	

}