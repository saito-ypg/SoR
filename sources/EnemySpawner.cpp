#include"../Engine/GameObject.h"
#include "EnemySpawner.h"
#include"EnemyBase.h"
#include"Decoy.h"
constexpr float spawnDistance = 10.0f;
EnemyBase* EnemySpawner::EnemyFactoty::createEnemy(GameObject* pParent, EnemyType type,bool isBoss)
{
	using enum EnemyType;
	switch (type)
	{
	case DECOY:
		return Instantiate<Decoy>(pParent);
		

	}
	return nullptr;
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
	XMMATRIX rotmat = XMMatrixRotationY(XMConvertToRadians(rand() % 360));
	XMVECTOR vpos = XMVector3TransformCoord(XMVectorSet(0,0,15,0), rotmat);
	enemy->SetPosition(vpos);
	return enemy;
}
