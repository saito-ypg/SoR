#pragma once
#include"EnemyType.h"
class EnemyBase;
class GameObject;
class EnemySpawner
{
private:
	class EnemyFactoty {
	public:
		static EnemyBase* createEnemy(GameObject* pParent, EnemyType type,bool isBoss);
		
	};
	GameActor *pPlayer;
public:
	static EnemyBase* spawnEnemy(GameObject* pParent, EnemyType type);
	static EnemyBase* spawnEnemy(GameObject* pParent, EnemyType type,bool isBoss);
};

