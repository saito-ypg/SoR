#pragma once
#include "AttackRange.h"
#include"DamageData.h"
//プレイヤー用スキルの元
class SkillBase
{
public:
	struct DamageData damageData_;

	const float defaultCastTime_;//スキル使用にかかる総時間
	float castTime_;//スキル使用時間
	const float defaultCoolDown_;//スキルの再使用までの時間
	float coolDown_;//クールタイム残り時間

	SkillBase(float CT,float CD):defaultCastTime_(CT),defaultCoolDown_(CD){}
	virtual void action() = 0;//スキル発動した時の動きとかを実装
	void update();

};

