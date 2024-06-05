#pragma once
#include"EnemyType.h"
#include<map>
struct EnemyStatus;
class EnemyBase;
class GameObject;
class GameActor;
class EnemySpawner
{
private:
	std::map<std::string, EnemyStatus> datas;
	/// <summary>
	/// 生成した敵のステータスを設定するために、データを読み込み保管する
	/// コンストラクタ内で使用
	/// </summary>
	void loadEnemyParams();

	/// <summary>
	/// 生成のみを行うファクトリークラス
	/// </summary>
	class EnemyFactory {
	public:
		static EnemyBase* createEnemy(GameObject* pParent, EnemyType type,bool isBoss);
		
	};
	GameActor *pPlayer;
public:
	EnemySpawner();
	static EnemyBase* spawnEnemy(GameObject* pParent, EnemyType type,bool isBoss=false);
};

