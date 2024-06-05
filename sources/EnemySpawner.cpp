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
struct EnemyStatus{
	int hp;
	float radius;
};

namespace {
	std::map<EnemyType, EnemyStatus> datas;
	/// <summary>
	/// �����݂̂��s���t�@�N�g���[�֐�
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
{//��ŃL�[���萔�ɂ��悤
	using json = nlohmann::json;
	std::ifstream f("../Assets/data/enemy_status.json");
	if (f.fail())
	{
		MessageBox(nullptr, "�G���t�@�C�����ǂݍ��߂܂���ł����B", "�G���[", S_OK);
		return;
	}

	json jsondata;
	f >> jsondata;
	std::string s = jsondata.dump();
	for (const auto& itr : jsondata) {
		const auto &param = itr.at("character").at("params");
		datas.emplace((EnemyType)(itr.at("id")), EnemyStatus{ param.at("maxHp"), param.at("radius") });
	}

}

EnemySpawner::EnemySpawner(GameActor* pPlayer)
{
	pPlayer_ = pPlayer;
	assert(pPlayer);
	if(datas.empty())
		loadEnemyParams();
}

EnemyBase* EnemySpawner::spawnEnemy(GameObject* pParent, EnemyType type, bool isBoss)
{
	auto enemy = ::createEnemy(pParent, type, isBoss);
	if (!enemy)
	{
		assert(false);
	}
	enemy->SetPlayer(pPlayer_);//�v���C���[��F�m������
	XMMATRIX rotmat = XMMatrixRotationY(XMConvertToRadians((float)(rand() % ANGLE360)));
	XMVECTOR vpos = XMVector3TransformCoord(XMVectorSet(0,0, SPAWN_DISTANCE,0), rotmat);
	enemy->SetPosition(vpos);
	return enemy;
}
