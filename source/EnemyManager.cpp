#include"EnemyManager.h"
#include"EnemyBase.h"

void EnemyManager::add(EnemyBase* enemy)
{
	Enemylist_.push_back(enemy);
	//�����蔻��̓G���ɓ����
}

bool EnemyManager::Eliminated()
{
	assert(!Enemylist_.empty());//�󂾂����牽�����炨�������͂�
		
	for (const auto& itr : Enemylist_)
	{
		if (itr->getStat() != EnemyBase::DEAD)
			return false;
	}
	return true;//�S���|���Ă���true�Ԃ��ăN���A���Ă���H
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
