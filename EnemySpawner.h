#pragma once


enum class EnemyType {
	Decoy = 0,

	MAX//最大値、これ使うことはないだろうけど
};
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

