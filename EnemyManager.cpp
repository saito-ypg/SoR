#include"EnemyManager.h"
#include"EnemyBase.h"

void EnemyManager::add(EnemyBase* enemy)
{
	Enemylist_.push_back(enemy);
	//�����蔻��̓G���ɓ����
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
