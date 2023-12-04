#pragma once
//#include "Engine/GameObject.h"
#include"GameActor.h"
constexpr float MOVE_VELOCITY = 10.0f /60;
class Player : public GameActor
{//Pimplとかいう概念、よさそう
    int hModel_;
    //移動方向の単位ベクトルを格納
    XMVECTOR moveDirection_;
    //移動ベクトル
    XMVECTOR vMove_;
    //移動にかかるフレーム数を入れる。移動中断したら0に
    float moveTime_;
    //入れたベクトルをスクリーン座標からワールド座標に変換して返す
    XMVECTOR getMouseTargetPos(XMFLOAT3 mouse);
    
    void calculateForMove(XMVECTOR target_);

    void move();
protected:
    void AddCamp()override;
public:
    //コンストラクタ
    Player(GameObject* parent);

    //デストラクタ
    virtual ~Player();

    //初期化
    void Initialize() override;

    //個別更新
    void ActorUpdate() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

};