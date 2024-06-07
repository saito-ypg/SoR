#include<map>
#include<fstream>
#include"../Engine/GameObject.h"
#include "EnemySpawner.h"
#include"EnemyBase.h"
#include"Decoy.h"
#include"SoldierEnemy.h"
#include"../libraries/json.hpp"
constexpr float SPAWN_DISTANCE = 10.0f;
constexpr int ANGLE360 = 360;

namespace {
	std::map<EnemyType, EnemyStatus> datas;
	/// <summary>
	/// 生成のみを行うファクトリー関数
	/// </summary>
	EnemyBase* createEnemy(GameObject* pParent, EnemyType type, bool isBoss)
	{
		using enum EnemyType;
		EnemyBase* enemy = nullptr;
		switch (type)
		{
		case DECOY:
			enemy = Instantiate<Decoy>(pParent);
			break;
		case SOLDIER:
			enemy = Instantiate<SoldierEnemy>(pParent);
			break;
		}
		assert(enemy != nullptr);
		return enemy;
	}

}



void EnemySpawner::loadEnemyParams()
{	//キー名typo対策の定数に
	constexpr auto chr = "character", params = "params", id = "id", hp = "maxHp", r = "radius";
	using json = nlohmann::json;
	std::ifstream f("../Assets/data/enemy_status.json");
	if (f.fail())
	{
		MessageBox(nullptr, "敵情報ファイルが読み込めませんでした。", "エラー", S_OK);
		return;
	}

	json jsondata;
	f >> jsondata;
	std::string s = jsondata.dump();
	for (const auto& itr : jsondata) {
		const auto &param = itr.at(chr).at(params);
		datas.emplace((EnemyType)(itr.at(id)), EnemyStatus{ param.at(hp), param.at(r) });
	}

}

EnemySpawner::EnemySpawner(GameActor* pPlayer)
{
	pPlayer_ = pPlayer;
	assert(pPlayer);
	if(datas.empty())
		loadEnemyParams();
}

EnemyBase* EnemySpawner::spawnEnemy(GameObject* pParent, EnemyType type, bool isBoss) const
{
	auto enemy = ::createEnemy(pParent, type, isBoss);
	if (!enemy)
	{
		assert(false);
	}
	enemy->SetPlayer(pPlayer_);//プレイヤーを認知させる
	enemy->setConfig(datas.at(type));
	XMMATRIX rotmat = XMMatrixRotationY(XMConvertToRadians((float)(rand() % ANGLE360)));
	XMVECTOR vpos = XMVector3TransformCoord(XMVectorSet(0,0, SPAWN_DISTANCE,0), rotmat);
	enemy->SetPosition(vpos);
	return enemy;
}
