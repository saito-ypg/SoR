#pragma once
#include<list>
#include"EnemyList.h"
#include"GameActor.h"
class EnemyBase;
//�G���܂Ƃ߂ĊǗ�����N���X
//�X�|�[��������N���X���ʂɂ��Ăق����ȁ`
class EnemyList:public GameObject{
private:

public:
	EnemyList(GameObject* parent);
	~EnemyList();
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void Release()override;
	std::list<EnemyBase*> Enemylist;

	void add(EnemyBase*enemy);//list�ɓG��o�^
	

	

}