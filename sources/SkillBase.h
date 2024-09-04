#pragma once
#include<vector>
#include<string>
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
	/// <summary>
	/// 派生先からは引数付きのものを呼ぶ。これは基礎的な初期化のみを行う
	/// </summary>
	SkillBase();
protected:
	Transform beginTransform_;//スキル発動時のトランスフォームを格納しておく。発動時以外は基本いじらない。プレイヤーのものとは区別する
	std::vector<float>sequence{0};//攻撃における各ステップ時間、ミリ秒
	float steptime;//各ステップでの残り時間
	int stepindex;//現在何ステップ目か。sequence
	bool isStepChanged;
	enum base_steps {//基本的なステップ
		INVOKED = 0,//発動直後、予備動作とか
		START_ATTACK,//攻撃判定開始
		END_ATTACK,//攻撃判定終了
	};
	/// <summary>
	/// UIクラス用、画像に使う名前
	/// </summary>
    std::string IconImageName;

	/// <summary>
	/// スキル発動中の動作と処理の実装
	/// </summary>
	virtual void action() = 0;
	
	/// <summary>
	/// 各ステップの処理を呼び分ける
	/// </summary>
	void SwitchActionByStep();
	
	/// <summary>
	/// 攻撃前ステップの実装
	/// </summary>
	virtual void invokedStep()=0;
	
	/// <summary>
	/// 攻撃開始ステップの実装
	/// </summary>
	virtual void startStep()=0;
	
	/// <summary>
	/// 攻撃終了後ステップの実装 
	/// </summary>
	virtual void endStep()=0;


	float defaultCastTime_;//スキル使用後動けない総時間
	float castTime_;//動けるようになるまでの残り時間
	float defaultCoolDown_;//スキルの再使用までの時間
	float coolDown_;//クールタイム残り時間
	bool isInOperation_;//スキル使用中か
	Player* pPlayer_;//プレイヤーのステータス変えたりしたい時に使うポインタ

	void RegisterHitRange(AttackRangeCircle c,DamageData &dmg);
	void RegisterHitRange(AttackRangeQuad q, DamageData &dmg);
	void RegisterHitRange(AttackRangeCirculerSector s, DamageData &dmg);
	Transform GetPlayerTransform();

	/// <summary>
	/// 必要なら継承先でこれをオーバーライドし、固有のメンバなどを初期化する
	/// </summary>
	virtual void ResetInheritedSkillMembers();
public:
	

	/// <summary>
	/// 引数はフレーム単位
	/// </summary>
	/// <param name="CT">使用にあたる時間</param>
	/// <param name="CD">再使用時間</param>
	/// <param name="pPlayer">プレイヤーのポインタ</param>
	SkillBase(const float CT, const float CD, Player *const pPlayer, const std::string iconName);

	virtual ~SkillBase();
	virtual void Update(const float&playerDt);//スキル時間、CD時間等の更新。プレイヤーから更新秒数を受け取る（プレイヤーの時間に対応させて)
	void Activate();//スキル発動（ボタン押したとき）
	virtual void Draw()=0;//スキルエフェクトなど描画
	virtual void DrawRangeDisplay(float deg)=0;//攻撃前に範囲を表示する 引数->角度
	virtual void Release() = 0;
	bool CanUse() const{ return coolDown_ <= 0; }
	bool CanMove() const{ return castTime_ <= 0; }
	float getCdPercentage() const;//playerInterface用。
	float getCtPercentage() const;//playerInterface用。
	bool IsInOperation()const { return isInOperation_; }
	static float ConvFrameToMs(float frames) {return frames*1000 / 60;}//60fps基準でフレームからミリ秒に変換

	std::string getIconName() const { return IconImageName; };
};

