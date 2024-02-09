#pragma once
#include<list>
#include"EnemyList.h"
#include"GameActor.h"
class EnemyBase;
//“G‚ğ‚Ü‚Æ‚ß‚ÄŠÇ—‚·‚éƒNƒ‰ƒX
//ƒXƒ|[ƒ“‚³‚¹‚éƒNƒ‰ƒX‚ª•Ê‚É‚¢‚Ä‚Ù‚µ‚¢‚È`
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

	void add(EnemyBase*enemy);//list‚É“G‚ğ“o˜^
	

	

}