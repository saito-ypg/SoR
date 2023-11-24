#pragma once
#include<vector>
#include"ActorCollider.h"
#include<map>
class GameActor;
namespace CollisionManager
{
	std::map<GameActor* ,ActorCollider*> enemiesCampCollision;
	std::map<GameActor* ,ActorCollider*> playersCampCollision;
	
	//プレイヤー陣営の当たり判定リストに追加する。
	[[nodiscard]] ActorCollider* AddPlayerCamp(GameActor* newActor);

	//敵陣営の当たり判定リストに追加する。
	[[nodiscard]] ActorCollider* AddEnemyCamp(GameActor* newActor);
	//プレイヤーの攻撃に当たっている敵を、返すor別メンバに入れとく。各形状でオーバーロード
	auto HitTestByPlayer(/*攻撃側当たり判定クラス*/);
	//敵の攻撃に当たっているプレイヤーもしくは...
	auto HitTestByEnemy();

	void RemoveEnemyCamp(GameActor*);
	void RemovePlayerCamp(GameActor*);

}

