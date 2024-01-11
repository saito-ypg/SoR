#pragma once
//#include "Engine/GameObject.h"
#include"GameActor.h"
#include"PlayerSkillsInclude.h"
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

 //スキル登録
    std::vector<SkillBase*>skills{ 4 };
    void ActivateSkill(int number);

    //入れたベクトルをスクリーン座標からワールド座標に変換して返す
    XMVECTOR getMouseTargetPos(XMFLOAT3 mouse);
    
    void calculateForMove(XMVECTOR target_);

    void move();
    
    void AddCamp()override;

    //test
    AttackRangeQuad testQuad;
    AttackRangeCircle testCircle;
    AttackRangeCirculerSector testSector;
protected:

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
    void ActorDraw() override;

    //開放
    void Release() override;

};