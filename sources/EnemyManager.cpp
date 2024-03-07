#include"EnemyManager.h"
#include"EnemyBase.h"

void EnemyManager::add(EnemyBase* enemy)
{
	Enemylist_.push_back(enemy);
	//“–‚½‚è”»’è‚Ì“G‘¤‚É“ü‚ê‚é
}

bool EnemyManager::Eliminated()
{
	assert(!Enemylist_.empty());//‹ó‚¾‚Á‚½‚ç‰½‚©‚µ‚ç‚¨‚©‚µ‚¢‚Í‚¸
		
	for (const auto& itr : Enemylist_)
	{
		if (itr->getStat() != EnemyBase::DEAD)
			return false;
	}
	return true;//‘Sˆõ“|‚µ‚Ä‚½‚çtrue•Ô‚µ‚ÄƒNƒŠƒA‚Á‚Ä‚·‚éH
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
