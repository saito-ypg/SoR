#pragma once


enum class EnemyType {
	Decoy = 0,

	MAX//Å‘å’lA‚±‚êg‚¤‚±‚Æ‚Í‚È‚¢‚¾‚ë‚¤‚¯‚Ç
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

