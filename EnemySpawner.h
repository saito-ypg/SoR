#pragma once


enum class EnemyType {
	Decoy = 0,

	MAX//�ő�l�A����g�����Ƃ͂Ȃ����낤����
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

