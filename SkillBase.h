#pragma once
#include<vector>
#include"AttackRange.h"
#include"DamageData.h"
#include"Engine/Transform.h"


//プレイヤー用スキルの基礎クラス。各種パラメーターは一旦フレーム単位で指定。
//各派生先のactionの中でstep毎に処理変える(switch-case)。必要なら専用のenum作る。
class SkillBase
{
private:

protected:
	Transform transform_;//スキル発動位置
	std::vector<float>sequence{0};//攻撃における各ステップの時間
	float steptime;//各ステップで現在どれだけの時間たったか
	int stepindex;//現在何ステップ目か。sequence

	enum base_steps {//基本的なステップ
		INVOKED = 0,//発動直後、予備動作とか
		START_ATTACK,//攻撃判定開始
		END_ATTACK,//攻撃判定終了
	};
	
	virtual void action() = 0;//スキル発動中の動作と処理の実装
	float defaultCastTime_;//スキル使用後動けない総時間
	float castTime_;//動けるようになるまでの残り時間
	float defaultCoolDown_;//スキルの再使用までの時間
	float coolDown_;//クールタイム残り時間
	bool isInOperation;
	
	struct attack {
		AttackRangeBase range;
		float Duration;
		DamageData damageData_;
	};
public:
	

	SkillBase();
	SkillBase(float CT, float CD);//秒単位指定

	virtual void Update();//スキル時間、CD時間等の更新。持続的な判定?
	void Activate(Transform tr);//スキル発動（ボタン押したとき）
	virtual void Draw()=0;//スキルエフェクトなど描画
	bool CanUse() { return coolDown_ <= 0; }
	bool CanMove() { return castTime_ <= 0;  }

	static float Sec(float flames) {return flames / 60;}//フレームから秒に変換
	static float frame(float seconds) { return seconds * 60; }//秒からフレームに変換
};

