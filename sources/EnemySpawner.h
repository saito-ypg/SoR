#pragma once
#include"EnemyType.h"

class EnemyBase;
class GameObject;
class GameActor;
class EnemySpawner
{
private:
	GameActor*pPlayer_;

	/// <summary>
	/// 生成した敵のステータスを設定するために、データを読み込み保管する
	/// コンストラクタ内で使用
	/// </summary>
	void loadEnemyParams();

public:
	EnemySpawner(GameActor *pPlayer);
	EnemyBase* spawnEnemy(GameObject* pParent, EnemyType type,bool isBoss=false);
};

