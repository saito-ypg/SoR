#pragma once
#include<vector>
#include"AttackRange.h"
#include"DamageData.h"



//プレイヤー用スキルの元
class SkillBase
{
private:

protected:
	
	//float steptime;//各ステップ
	//std::vector<float>sequence;//各ステップにかかる時間入れとく

	//ビリヤードの時のstartみたいにシーケンス入れたい。それに応じて攻撃出したり動かしたり
	virtual void action() = 0;//スキル発動した時の動作と処理の実装
public:
	struct DamageData damageData_;

	float defaultCastTime_;//スキル使用にかかる総時間
	float castTime_;//スキル使用にかかる時間
	float defaultCoolDown_;//スキルの再使用までの時間
	float coolDown_;//クールタイム残り時間

	SkillBase();
	SkillBase(float CT, float CD);

	virtual void Update();//スキル時間、CD時間等の更新と持続的な判定
	void Activate();//スキル発動（ボタン押したとき）


};

