#pragma once
#include<vector>
#include"ActorCollider.h"
#include<map>
class GameActor;
//プレイヤー陣営/敵陣営
enum CAMPS{PLAYER,ENEMY};

//全てのアクタの当たり判定を管理・判定する名前空間。クラスのほうがいい？
namespace CollisionManager
{	
	//各陣営の当たり判定
	std::vector<std::map<GameActor*, ActorCollider*>>CollisionList;

	/// <summary>
	/// 当たり判定リストに追加
	/// </summary>
	/// <param name="newActor">追加するアクタ</param>
	/// <param name="camp">追加したい陣営</param>
	/// <returns></returns>
	[[nodiscard]] ActorCollider* AddCamp(GameActor* newActor,CAMPS camp);
	//プレイヤーの攻撃に当たっている敵を、返すor別メンバに入れとく。各形状でオーバーロード
	auto HitTestBy(/*攻撃側当たり判定クラス*/);
	
	/// <summary>
	///陣営リストから削除する。倒された際に呼ぶ 
	/// </summary>
	/// <param name="actor">削除したいアクタ</param>
	/// <param name="camp">所属陣営</param>
	void RemoveCamp(GameActor*actor,CAMPS camp);

	/// <summary>
	/// 攻撃を受けたことを通知し、各actorのTakeAttackedを呼ぶ
	/// </summary>
	void NotifyReceivedAttack();

	//void Update();//←いる？
	void Release();//解放処理
}

