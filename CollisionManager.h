#pragma once
#include<vector>
#include"ActorCollider.h"
#include<map>
class GameActor;
namespace CollisionManager
{
	std::map<ActorCollider*, GameActor*> enemiesCampCollision;
	std::map<ActorCollider*, GameActor*> playersCampCollision;
	
	//プレイヤー陣営の当たり判定リストに追加する。
	[[nodiscard]] ActorCollider* AddPlayerCollision(GameActor* newActor);
	//敵陣営の当たり判定リストに追加する。
	[[nodiscard]] ActorCollider* AddEnemyCollision(GameActor* newActor);
	auto HitTestPlayer(/*攻撃側当たり判定クラス*/);//リスト全部見て当たってるものを返すor別メンバに入れとく。各形状でオーバーロード
	auto HitTestEnemy();

	void RemoveEnemyCamp(GameActor*);
	void RemovePlayerCamp(GameActor*);

}

