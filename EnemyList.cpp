#include"EnemyList.h"
#include"EnemyBase.h"

void Enemy::add(EnemyBase* enemy)
{
	Enemylist.push_back(enemy);
	//当たり判定の敵側に入れる
}
