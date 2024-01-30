#pragma once
#include"ActorCollider.h"
#include"AttackRange.h"

//プレイヤー陣営/敵陣営
enum CAMPS{PLAYER,ENEMY,NUM};
class GameActor;
//全てのアクタの当たり判定を管理・判定する名前空間。クラスのほうがいい？
//当たり判定の際、高さ(=y軸）は考慮しない
namespace CollisionManager
{
	struct actorAddr {
		GameActor* pActor;//キャラ
		ActorCollider* pCollider;//キャラの当たり判定
		actorAddr() :pActor(nullptr), pCollider(nullptr) {}
		actorAddr(GameActor* pA, ActorCollider* pC) :pActor(pA), pCollider(pC) {}
	};
	struct RangeData {
		AttackRangeBase* pRange;
		float duration;//持続時間、フレーム単位
	};
	/// <summary>
	/// シーンのアップデートでこれも呼ぶ
	/// 当たり判定が持続する間判定し続けるとか
	/// </summary>
	void Update();
	
	/// <summary>
	/// 当たり判定リストに追加
	/// </summary>
	/// <param name="newActor">追加するアクタ</param>
	/// <param name="camp">追加したい陣営</param>
	/// <returns></returns>
	void AddCamp(GameActor* newActor,CAMPS camp);

	/// <summary>
	/// 円形の攻撃に当たっているか判定する
	/// </summary>
	/// <param name="camp">攻撃者陣営</param>
	/// <param name="circle">円形攻撃エリア</param>
	void HitTestBy(CAMPS camp,AttackRangeCircle& circle);

	/// <summary>
	/// 矩形の攻撃に当たっているか判定
	/// </summary>
	/// <param name="camp">攻撃者陣営</param>
	/// <param name="quad">矩形攻撃エリア</param>
	void HitTestBy(CAMPS camp, AttackRangeQuad& quad);

	/// <summary>
	/// 扇形の攻撃に当たっているか判定
	/// </summary>
	/// <param name="camp">攻撃者陣営</param>
	/// <param name="quad">扇形攻撃エリア</param>
	void HitTestBy(CAMPS camp, AttackRangeCirculerSector& sector);

	
	/// <summary>
	///陣営リストから削除する。倒された際に呼ぶ 
	/// </summary>
	/// <param name="actor">削除したいアクタ</param>
	/// <param name="camp">所属陣営</param>
	void RemoveCamp(GameActor*actor,CAMPS camp);

	void Release();//解放処理
}

