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
	/// ���������G�̃X�e�[�^�X��ݒ肷�邽�߂ɁA�f�[�^��ǂݍ��ݕۊǂ���
	/// �R���X�g���N�^���Ŏg�p
	/// </summary>
	void loadEnemyParams();

public:
	EnemySpawner(GameActor *pPlayer);
	EnemyBase* spawnEnemy(GameObject* pParent, EnemyType type,bool isBoss=false);
};

