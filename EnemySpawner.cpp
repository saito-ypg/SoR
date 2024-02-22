#include "EnemySpawner.h"
#include"Engine/GameObject.h"
#include"EnemyBase.h"
#include"Decoy.h"

EnemyBase* EnemySpawner::EnemyFactoty::createEnemy(GameObject* pParent, EnemyType type)
{
	using enum EnemyType;
	switch (type)
	{
	case Decoy:
		return GameObject::Instantiate<Decoy>(pParent);

	}
}

EnemyBase* EnemySpawner::spawnEnemy(GameObject* pParent, EnemyType type)
{
	auto enemy = EnemyFactoty::createEnemy(pParent,type);
}
