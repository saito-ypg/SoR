#pragma once
#include"ActorCollider.h"
#include"AttackRange.h"
#include"DamageData.h"

//プレイヤー陣営/敵陣営
enum CAMPS{PLAYER,ENEMY,NUM};
class GameActor;
struct DamageData;
struct actorAddr {
	GameActor* pActor;//キャラ
	ActorCollider* pCollider;//キャラの当たり判定
	actorAddr() :pActor(nullptr), pCollider(nullptr) {}
	actorAddr(GameActor* pA, ActorCollider* pC) :pActor(pA), pCollider(pC) {}
};

struct RangeData {
	AttackRangeBase* pRange_;
	std::vector<GameActor*>ExclusionsList_{ 0 };//すでにヒットしたものなど入れておく、判定からは除外
	DamageData dmg_;
	std::function<void(RangeData&, float)>updateFunc;//アップデート内で特殊な内容が必要ならここに入れる
	RangeData(AttackRangeBase* pR, DamageData dmg) :RangeData(pR, dmg, nullptr) {}
	RangeData(AttackRangeBase* pR, DamageData dmg, std::function<void(RangeData&, float)>func) :pRange_(pR), dmg_(dmg), updateFunc(func) {}
};


//全てのアクタの当たり判定を管理・判定する名前空間。
//当たり判定の際、高さ(=y軸）は考慮しない
namespace CollisionManager
{
	/// <summary>
	/// シーンのアップデートでこれも呼ぶ
	/// 当たり判定が持続する間判定し続けるとか
	/// </summary>
	void Update(const float&dt);
	
	/// <summary>
	/// 当たり判定リストに追加
	/// </summary>
	/// <param name="newActor">追加するアクタ</param>
	/// <param name="camp">追加したい陣営</param>
	/// <returns></returns>
	void AddCamp(GameActor* newActor,CAMPS camp);


	void RegisterHitRange(CAMPS camp, AttackRangeCircle c, DamageData dmg, std::function<void(RangeData&, float)> func);
	void RegisterHitRange(CAMPS camp, AttackRangeQuad q, DamageData dmg, std::function<void(RangeData&, float)>func);
	void RegisterHitRange(CAMPS camp, AttackRangeCirculerSector s, DamageData dmg, std::function<void(RangeData&, float)>func);
	/// <summary>
	///陣営リストから削除する。倒された際に呼ぶ 
	/// </summary>
	/// <param name="actor">削除したいアクタ</param>
	/// <param name="camp">所属陣営</param>
	void RemoveCamp(GameActor*actor,CAMPS camp);

	void Release();//解放処理
}

