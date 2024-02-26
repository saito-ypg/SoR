#pragma once
#include"EnemyType.h"
class EnemyBase;
class GameObject;
class EnemySpawner
{
private:
	class EnemyFactoty {
	public:
		static EnemyBase* createEnemy(GameObject* pParent, EnemyType type);
		
	};

public:
	EnemyBase* spawnEnemy(GameObject*pParent, EnemyType type);
};

