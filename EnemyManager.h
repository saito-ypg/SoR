#pragma once
#include<list>
#include"GameActor.h"
#include<utility>
class EnemyBase;
//�G���܂Ƃ߂ĊǗ�����N���X
//�X�|�[��������N���X���ʂɂ��Ăق����ȁ`
class EnemyManager {
private:

public:
	EnemyManager(GameObject* parent);
	~EnemyManager();
	void Initialize();
	void Update(const float& dt);
	void Draw();
	void Release();
	std::vector<EnemyBase*> Enemylist_;

	void add(EnemyBase* enemy);//list�ɓG��o�^�B������Instantiate�Ƃ��K�v����




};