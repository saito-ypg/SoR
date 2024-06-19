#pragma once
#include<vector>
#include "../Engine/GameObject.h"
#include "ActorInfo.h"
#include"CollisionManager.h"
#include"DamageData.h"
using namespace AreaModels;
class ActorCollider; 
const float defTime = 35.0f;
class GameActor :public GameObject{
private:
    struct {
        float Time;//動く残り時間
        float Velocity;//強さ
        XMVECTOR Dir;//方向
    } knockBack;
   
protected:
    
    ActorInfo status_;
    bool isInvincible_;//無敵状態か？
    bool isdying;//HP0以下になったらこれ変える、回復しても死んだまま
    bool  IsDying_()const { return isdying; }
    int hBody_;//基本となるモデルの描画
    std::vector<int> hModels_;//Body以外の補助的なモデル番号を配列に

    //当たり判定を登録、継承先で陣営固定する
    void AddColliderCamp(GameActor *act, CAMPS camp);
    //継承用
    virtual void AddCamp()=0;
    //当たり判定消去
    void RemoveColliderCamp(GameActor* act, CAMPS camp);
    //継承用
    virtual void RemoveCamp()= 0;

    //妨害要素によって動けない状態にあるか?(未実装)
    bool CanMoveWithEffects();

    //モデル本体を描画する。ActorDraw内で呼ぶ
    void DrawBody();
    //テスト用、当たり判定を描画。draw内で呼ぶ
    void DrawCollision();
    //HPを描画する
    void DrawHP() const;

    //死亡時処理。ないならないでよし
    virtual void dyingProcess();
    //死亡時描画。倒れるアニメーションとか
    virtual void dyingDraw();
public:
    float GetRadius()const{return status_.hitCircleRange_;}
    GameActor(GameObject* parent, const std::string& name); 
    virtual ~GameActor();

    //actorで共通の描画を行うため、個別の更新はActorUpdateに分離すること
    void Update(const float& dt) override final;
    //継承先で実装。個別の更新
    virtual void ActorUpdate(const float& dt)=0;
    //actorで共通の描画を行うため、個別の描画はActorDrawに分離すること
    void Draw() override final;
    //継承先で実装。個別の共有
    virtual void ActorDraw() = 0;
    //オーバーライドするか未定
    void TakeAttacked(DamageData &dmg,XMVECTOR &dir);
    Transform* GetTransformRef();
    //moveの分だけ移動させる
    void ForceMove(XMVECTOR translateBy);
};

