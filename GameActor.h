#pragma once
#include "Engine/GameObject.h"
#include "ActorInfo.h"
class ActorCollider;
class GameActor :public GameObject{
protected:
    ActorInfo status_;
    bool isInvincible_;//無敵状態か？

public:
    float GetRadius(){return status_.hitCircleRange_;}
    GameActor(GameObject* parent, const std::string& name); 
    virtual ~GameActor();
    void Update() override final;//info関連の更新はすべてのキャラでやるので、個別の更新はActorUpdateに分離すること
    virtual void ActorUpdate()=0;//継承先で実装
    void TakeAttacked() const;//オーバーライドするか未定
    Transform* GetTransformRef();
};

