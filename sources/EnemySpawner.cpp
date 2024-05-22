#include"../Engine/GameObject.h"
#include "EnemySpawner.h"
#include"EnemyBase.h"
#include"Decoy.h"
constexpr float SPAWN_DISTANCE = 10.0f;
constexpr int ANGLE360 = 360;
EnemyBase* EnemySpawner::EnemyFactoty::createEnemy(GameObject* pParent, EnemyType type,bool isBoss)
{
	using enum EnemyType;
	EnemyBase* enemy = nullptr;
	switch (type)
	{
	case DECOY:
		 enemy=Instantiate<Decoy>(pParent);
		

	}
	assert(enemy != nullptr);
	enemy->SetPlayer((GameActor*)enemy->FindObject(""));//
}

EnemyBase* EnemySpawner::spawnEnemy(GameObject* pParent, EnemyType type)
{
	return spawnEnemy(pParent, type, false);
}

EnemyBase* EnemySpawner::spawnEnemy(GameObject* pParent, EnemyType type, bool isBoss)
{
	auto enemy = EnemyFactoty::createEnemy(pParent, type, isBoss);
	if (!enemy)
		assert(false);
	XMMATRIX rotmat = XMMatrixRotationY(XMConvertToRadians((float)(rand() % ANGLE360)));
	XMVECTOR vpos = XMVector3TransformCoord(XMVectorSet(0,0, SPAWN_DISTANCE,0), rotmat);
	enemy->SetPosition(vpos);
	return enemy;
}
