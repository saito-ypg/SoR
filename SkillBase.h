#pragma once
#include<vector>
#include"AttackRange.h"
#include"DamageData.h"
#include"Engine/Transform.h"


//プレイヤー用スキルの基礎クラス。各種パラメーターは一旦秒単位で指定
class SkillBase
{
private:

protected:
	Transform transform_;//スキル発動位置
	//float steptime;//各ステップ
	std::vector<float>sequence;//各ステップにかかる時間入れとく
	//ビリヤードの時のstartみたいにシーケンス入れたい。それに応じて攻撃出したり動かしたり

	virtual void action() = 0;//スキル発動した時の動作と処理の実装
	float defaultCastTime_;//スキル使用にかかる総時間
	float castTime_;//スキル使用にあたり動けない時間
	float defaultCoolDown_;//スキルの再使用までの時間
	float coolDown_;//クールタイム残り時間

public:
	struct DamageData damageData_;

	SkillBase();
	SkillBase(float CT, float CD);

	virtual void Update();//スキル時間、CD時間等の更新と持続的な判定
	void Activate(Transform tr);//スキル発動（ボタン押したとき）
	virtual void Draw()=0;//スキルエフェクトなど描画

};

