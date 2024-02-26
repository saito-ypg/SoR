#pragma once



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

