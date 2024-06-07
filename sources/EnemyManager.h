#pragma once
#include<list>
#include"GameActor.h"
#include<utility>
class EnemyBase;
//“G‚ğ‚Ü‚Æ‚ß‚ÄŠÇ—‚·‚éƒNƒ‰ƒX
class EnemyManager {
private:
	std::vector<EnemyBase*> Enemylist_;
public:
	EnemyManager(GameObject* parent);
	~EnemyManager();
	void Initialize();
	void Update(const float& dt);
	void Draw();
	void Release();
	

	void add(EnemyBase* enemy);//list‚É“G‚ğ“o˜^Bˆø”‚ÉInstantiate‚Æ‚©•K—v‚©‚È
	bool Eliminated();
	void clearEnemy();

};