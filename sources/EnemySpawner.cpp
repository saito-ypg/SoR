#include"../Engine/GameObject.h"
#include "EnemySpawner.h"
#include"EnemyBase.h"
#include"Decoy.h"
#include"SoldierEnemy.h"
constexpr float SPAWN_DISTANCE = 10.0f;
constexpr int ANGLE360 = 360;
EnemyBase* EnemySpawner::EnemyFactory::createEnemy(GameObject* pParent, EnemyType type,bool isBoss)
{
	using enum EnemyType;
	EnemyBase* enemy = nullptr;
	switch (type)
	{
	case DECOY:
		 enemy=Instantiate<Decoy>(pParent);
		 break;
	case SOLDIER:
		enemy = Instantiate<SoldierEnemy>(pParent);
		break;
	}
	assert(enemy != nullptr);
	return enemy;
}


void EnemySpawner::loadEnemyParams()
{
}

EnemySpawner::EnemySpawner()
{
	loadEnemyParams;
}

EnemyBase* EnemySpawner::spawnEnemy(GameObject* pParent, EnemyType type, bool isBoss)
{
	auto enemy = EnemyFactory::createEnemy(pParent, type, isBoss);
	if (!enemy)
		assert(false);
	enemy->SetPlayer((GameActor*)enemy->FindObject("Player"));//プレイヤーを認知させる

	XMMATRIX rotmat = XMMatrixRotationY(XMConvertToRadians((float)(rand() % ANGLE360)));
	XMVECTOR vpos = XMVector3TransformCoord(XMVectorSet(0,0, SPAWN_DISTANCE,0), rotmat);
	enemy->SetPosition(vpos);
	return enemy;
}
