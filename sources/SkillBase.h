#pragma once
#include<vector>
#include"../Engine/Transform.h"
#include"areamodels.h"
#include"AttackRange.h"
#include"DamageData.h"

using namespace AreaModels;
class Player;
///プレイヤー用スキルの基礎クラス。各種パラメーターは一旦フレーム単位で指定。
///各派生先のactionの中でstep毎に処理変える(switch-case)。必要なら専用のenum作る。
/// コンストラクタでCastTime・CoolDownの指定
/// sequenceのフレーム数指定を行うこと
class SkillBase
{
private:
	SkillBase();//派生先からは引数付きのものを呼ぶ。これは基礎的な初期化のみを行う
protected:
	Transform transform_;//スキル発動時のトランスフォームを格納しておく。発動時以外は基本いじらない。プレイヤーのものとは区別する
	std::vector<float>sequence{0};//攻撃における各ステップフレーム数
	float steptime;//各ステップで現在どれだけの時間たったか
	int stepindex;//現在何ステップ目か。sequence

	enum base_steps {//基本的なステップ
		INVOKED = 0,//発動直後、予備動作とか
		START_ATTACK,//攻撃判定開始
		END_ATTACK,//攻撃判定終了
	};
	
	virtual void action() = 0;//スキル発動中の動作と処理の実装
	void SwitchActionByStep();//各ステップの処理を呼び分ける
	virtual void invokedStep()=0;//攻撃前ステップの実装
	virtual void startStep()=0;//攻撃開始ステップの実装
	virtual void endStep()=0;//攻撃終了後ステップの実装

	float defaultCastTime_;//スキル使用後動けない総時間
	float castTime_;//動けるようになるまでの残り時間
	float defaultCoolDown_;//スキルの再使用までの時間
	float coolDown_;//クールタイム残り時間
	bool isInOperation;//スキル使用中か
	Player* pPlayer_;//プレイヤーのステータス変えたりしたい時に使うポインタ
	void RegisterHitRange(AttackRangeCircle c,DamageData &dmg);
	void RegisterHitRange(AttackRangeQuad q, DamageData &dmg);
	void RegisterHitRange(AttackRangeCirculerSector s, DamageData &dmg);
	Transform GetPlayerTransform();
public:
	


	SkillBase(float CT, float CD, Player* pPlayer);//秒数指定→フレームに変換してる。派生先からこれを呼ぶ

	virtual ~SkillBase();
	virtual void Update();//スキル時間、CD時間等の更新。持続的な判定?
	void Activate();//スキル発動（ボタン押したとき）
	virtual void Draw()=0;//スキルエフェクトなど描画
	virtual void DrawRangeDisplay()=0;//攻撃前に範囲を表示する 引数→ワールド座標
	virtual void Release() = 0;
	bool CanUse() const{ return coolDown_ <= 0; }
	bool CanMove() const{ 
		return castTime_ <= 0; 
	}

	static float Sec(float flames) {return flames / 60;}//フレームから秒に変換
	static float frame(float seconds) { return seconds * 60; }//秒からフレームに変換
};

