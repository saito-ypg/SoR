#pragma once
#include<vector>
#include"AttackRange.h"
#include"DamageData.h"
#include"Engine/Transform.h"


//プレイヤー用スキルの基礎クラス。各種パラメーターは一旦フレーム単位で指定。
class SkillBase
{
private:

protected:
	Transform transform_;//スキル発動位置

	std::vector<float>sequence{0};//攻撃における各ステップの時間
	float steptime;//各ステップで現在どれだけの時間たったか
	int stepindex;//現在何ステップ目か。sequence


	virtual void action() = 0;//スキル発動した時の動作と処理の実装
	float defaultCastTime_;//スキル使用にかかる総時間
	float castTime_;//スキル使用にあたり動けない時間
	float defaultCoolDown_;//スキルの再使用までの時間
	float coolDown_;//クールタイム残り時間

public:
	struct DamageData damageData_;
	bool isInOperation;
	SkillBase();
	SkillBase(float CT, float CD);//秒単位指定

	virtual void Update();//スキル時間、CD時間等の更新と持続的な判定
	void Activate(Transform tr);//スキル発動（ボタン押したとき）
	virtual void Draw()=0;//スキルエフェクトなど描画
	bool CamMove() { return castTime_ < 0;  }

	static float Sec(float flames) {return flames / 60;}//フレームから秒を出す
	static float flame(float seconds) { return seconds * 60; }//秒からフレームを出す
};

