#include"../Engine/GameObject.h"
#include "EnemySpawner.h"
#include"EnemyBase.h"
#include"Decoy.h"

EnemyBase* EnemySpawner::EnemyFactoty::createEnemy(GameObject* pParent, EnemyType type,bool isBoss)
{
	using enum EnemyType;
	switch (type)
	{
	case DECOY:
		return pParent->Instantiate<Decoy>(pParent);
		

	}
	return nullptr;
}

EnemyBase* EnemySpawner::spawnEnemy(GameObject* pParent, EnemyType type)
{
	return spawnEnemy(pParent, type, false);
}

EnemyBase* EnemySpawner::spawnEnemy(GameObject* pParent, EnemyType type, bool isBoss)
{
	auto enemy = EnemyFactoty::createEnemy(pParent, type, isBoss);
	if (!enemy)
		assert(false);
	return enemy;
}
