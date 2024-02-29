#include"EnemyManager.h"
#include"EnemyBase.h"

void EnemyManager::add(EnemyBase* enemy)
{
	Enemylist_.push_back(enemy);
	//当たり判定の敵側に入れる
}

bool EnemyManager::Eliminated()
{
	assert(!Enemylist_.empty());//空だったら何かしらおかしいはず
		
	for (const auto& itr : Enemylist_)
	{
		if (itr->getStat() != EnemyBase::DEAD)
			return false;
	}
	return true;//全員倒してたらtrue返してクリアってする？
}

EnemyManager::EnemyManager(GameObject* parent)
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Initialize()
{
}

void EnemyManager::Update(const float& dt)
{
	for (auto& itr : Enemylist_)
	{
		itr->UpdateSub(dt);
	}
}

void EnemyManager::Draw()
{
	for (auto& itr : Enemylist_)
	{
		itr->DrawSub();
	}
}

void EnemyManager::Release()
{
	for (auto& itr : Enemylist_)
	{
		itr->KillMe();
	}
}
