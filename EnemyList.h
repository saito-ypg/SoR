#pragma once
#include<list>
#include"EnemyList.h"
class EnemyBase;
//�G���܂Ƃ߂ĊǗ�����N���X
//���i�K�ł͖��g�p
namespace Enemy
{
	std::list<EnemyBase*> Enemylist;

	void add(EnemyBase*enemy);//list�ɓG��o�^
	

	

}