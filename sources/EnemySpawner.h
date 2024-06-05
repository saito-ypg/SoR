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
	/// ���������G�̃X�e�[�^�X��ݒ肷�邽�߂ɁA�f�[�^��ǂݍ��ݕۊǂ���
	/// �R���X�g���N�^���Ŏg�p
	/// </summary>
	void loadEnemyParams();

	/// <summary>
	/// �����݂̂��s���t�@�N�g���[�N���X
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

