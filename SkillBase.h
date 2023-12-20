#pragma once
#include<vector>
#include"AttackRange.h"
#include"DamageData.h"

//プレイヤー用スキルの元
class SkillBase
{
public:

	float steptime;//各ステップ
public:
	struct DamageData damageData_;

	const float defaultCastTime_;//スキル使用にかかる総時間
	float castTime_;//スキル使用時間
	const float defaultCoolDown_;//スキルの再使用までの時間
	float coolDown_;//クールタイム残り時間

	//ビリヤードの時のstartみたいにシーケンス入れたい。それに応じて攻撃出したり動かしたり
	std::vector<float>sequence;//各ステップにかかる時間入れとく
	SkillBase(float CT, float CD) :defaultCastTime_(CT), defaultCoolDown_(CD), castTime_(0.0f), coolDown_(0.0f) {}
	virtual void update();//スキル時間、CD時間等の更新と持続的な判定
	virtual void action() = 0;//スキル発動した時の動きとかを実装

};

