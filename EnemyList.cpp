#include"EnemyList.h"
#include"EnemyBase.h"

void Enemy::add(EnemyBase* enemy)
{
	Enemylist.push_back(enemy);
	//当たり判定の敵側に入れる
}

EnemyList::EnemyList(GameObject* parent)
{
}

EnemyList::~EnemyList()
{
}

void EnemyList::Initialize()
{
}

void EnemyList::Update()
{
}

void EnemyList::Draw()
{
}

void EnemyList::Release()
{
}

void EnemyList::add(EnemyBase* enemy)
{
}
