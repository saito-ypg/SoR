#pragma once
#include<list>
#include"GameActor.h"
class EnemyBase;
//�G���܂Ƃ߂ĊǗ�����N���X
//�X�|�[��������N���X���ʂɂ��Ăق����ȁ`
class EnemyManager :public GameObject {
private:

public:
	EnemyManager(GameObject* parent);
	~EnemyManager();
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void Release()override;
	std::list<EnemyBase*> Enemylist_;

	void add(EnemyBase* enemy);//list�ɓG��o�^�B������Instantiate�Ƃ��K�v����




};