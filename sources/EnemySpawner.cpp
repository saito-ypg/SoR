#include<map>
#include<fstream>
#include"../Engine/GameObject.h"
#include "EnemySpawner.h"
#include"EnemyBase.h"
#include"MediatorFactoryRegistry.h"
#include"MediatorFactory.h"
#include"RegistrationFactory.h"
#include"Decoy.h"
#include"SoldierEnemy.h"

#include"../libraries/json.hpp"
constexpr float SPAWN_DISTANCE = 10.0f;
constexpr int ANGLE360 = 360;

namespace {
	std::map<EnemyType, EnemyStatus> data;
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
			enemy =InstantiateEnemy<Decoy>(pParent,isBoss);
			break;
		case SOLDIER:
			enemy =InstantiateEnemy<SoldierEnemy>(pParent,isBoss);
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

	json jsonData;
	f >> jsonData;
	for (const auto& itr : jsonData) {
		const auto &param = itr.at(chr).at(params);
		data.emplace(static_cast <EnemyType> (itr.at(id)), EnemyStatus{ param.at(hp), param.at(r) });
	}

}

EnemySpawner::EnemySpawner(GameActor* pPlayer)
{
	pPlayer_ = pPlayer;
	assert(pPlayer);
	if(data.empty())
	{
		loadEnemyParams();
	}
	RegistrationFactory::RegisterAllFactory();	
}
EnemySpawner::~EnemySpawner()
{
}
EnemyBase* EnemySpawner::spawnEnemy(GameObject* pParent, EnemyType type, bool isBoss) const
{
	auto newEnemy = ::createEnemy(pParent, type, isBoss);
	if (!newEnemy)
	{
		assert(false);
	}
	newEnemy->SetPlayer(pPlayer_);//プレイヤーを認知させる
	newEnemy->setConfig(data.at(type));

	auto factory = MediatorFactoryRegistry::getFactory(type);
	if (factory) {
		newEnemy->SetMediator(factory->createMediator(*newEnemy));
	}
	CollisionManager::AddCamp(newEnemy, ENEMY);
	XMMATRIX rotmat = XMMatrixRotationY(XMConvertToRadians((float)(rand() % ANGLE360)));
	XMVECTOR vpos = XMVector3TransformCoord(XMVectorSet(0,0, SPAWN_DISTANCE,0), rotmat);
	newEnemy->SetPosition(vpos);
	return newEnemy;
}
