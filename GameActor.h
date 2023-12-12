#pragma once
#include<vector>
#include "Engine/GameObject.h"
#include "ActorInfo.h"
#include"CollisionManager.h"

class ActorCollider;
class GameActor :public GameObject{
protected:
    ActorInfo status_;
    bool isInvincible_;//無敵状態か？
    std::vector<int> hModels_;//モデル番号をリストに

    void AddColliderCamp(GameActor *act, CAMPS camp);//当たり判定を登録、継承先で陣営固定する
    virtual void AddCamp()=0;//継承用

    //void LoadModel(string filename);//モデルを読み込み、hModels_に追加。読み込めたらtrue
    void SimpleDraw();//簡易的にモデルを描画する。


public:
    float GetRadius()const{return status_.hitCircleRange_;}
    GameActor(GameObject* parent, const std::string& name); 
    virtual ~GameActor();
    void Update() override final;//info関連の更新はすべてのキャラでやるので、個別の更新はActorUpdateに分離すること
    virtual void ActorUpdate()=0;//継承先で実装

    void TakeAttacked();//オーバーライドするか未定
    Transform* GetTransformRef();
};

