#pragma once
#include<list>
#include"EnemyList.h"
class EnemyBase;
//“G‚ğ‚Ü‚Æ‚ß‚ÄŠÇ—‚·‚éƒNƒ‰ƒX
//Œ»’iŠK‚Å‚Í–¢g—p
namespace Enemy
{
	std::list<EnemyBase*> Enemylist;

	void add(EnemyBase*enemy);//list‚É“G‚ğ“o˜^
	

	

}