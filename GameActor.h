#pragma once
#include<vector>
#include "Engine/GameObject.h"
#include "ActorInfo.h"
#include"CollisionManager.h"
#include"DamageData.h"
class ActorCollider; 
const float defTime = 25.0f;
class GameActor :public GameObject{
private:
    struct {
        float Time;//動く残り時間
        float Velocity;//強さ
        XMVECTOR Dir;//方向正規化
    } knockBack;
   
    protected:
    
    ActorInfo status_;
    bool isInvincible_;//無敵状態か？
    bool isDead_;//HP0以下になったらこれ変える、gameobjectとは別？
    std::vector<int> hModels_;//モデル番号をリストに

    void AddColliderCamp(GameActor *act, CAMPS camp);//当たり判定を登録、継承先で陣営固定する
    virtual void AddCamp()=0;//継承用
    void RemoveColliderCamp(GameActor* act, CAMPS camp);;//当たり判定消去
    virtual void RemoveCamp()= 0;//継承用
    
    bool CanMove();//妨害要素によって動けない状態にあるか
    //void LoadModel(string filename);//モデルを読み込み、hModels_に追加。読み込めたらtrue
    
    void SimpleDraw();//簡易的にモデルを描画する。draw内で呼ぶ
    void DrawCollision();//テスト用、当たり判定を描画。draw内で呼ぶ
    int hCircle_;
    int hQuad_;
    int hSector_;
    void DrawHP();//HPを描画する。
public:
    float GetRadius()const{return status_.hitCircleRange_;}
    GameActor(GameObject* parent, const std::string& name); 
    virtual ~GameActor();
    void Update(const float& dt) override final;//info関連の更新はすべてのキャラでやるので、個別の更新はActorUpdateに分離すること
    virtual void ActorUpdate(const float& dt)=0;//継承先で実装
    void Draw() override final;//個別の描画はActorDrawに分離すること
    virtual void ActorDraw() = 0;
    void TakeAttacked(DamageData &dmg,XMVECTOR &dir);//オーバーライドするか未定
    Transform* GetTransformRef();
    void ForceMove(XMVECTOR move);
};

